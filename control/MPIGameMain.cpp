#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "GameLoop.h"
#include <iostream>
#include <fstream>


#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <cstdio>


bool isServer(int argc, char** argv);

//server functions
const char* openPort();
void writePortNameToFile(const char* portName);
const char* readPortNameFromFile();
MPI::Intercomm acceptConnection(const char* port_name);
void sendMessageToAllClients(MPI::Intercomm intercom);
void printRankAndSize(MPI::Intercomm intercom);

//client functions
const char* getPortName();
char* receiveBroadcastedPortName();
void broadcastPortName(const char* port_name);
void receiveMessageFromTheServer(MPI::Intercomm intercom);
MPI::Intercomm connectToServer(const char* port_name);

MPI::Intercomm startServer();
MPI::Intercomm startClient();
void startGameLoop();




int main(int argc, char** argv) {
    MPI::Init(argc, argv);
    
//    startGameLoop();
    
    MPI::Intercomm intercomm;
    
    
    if(isServer(argc, argv)){
        intercomm = startServer();
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        GameLoop* game = new GameLoop();
        game->doLoop();
        Action* action = game->getNPCS()[0]->getAction();

        action->serialize(writer);
        std::string message = buffer.GetString();
        std::cout << "Server sent message:\n " << message << "\n";
        
        intercomm.Send(message.c_str(), message.length(), MPI_CHAR, 0, 1);
    }else{
        intercomm = startClient();
        
        MPI::Status status;
        intercomm.Probe(0, 1, status);
        int messageSize = status.Get_count(MPI::CHAR);
        char *buffer = new char[messageSize];
        intercomm.Recv(buffer, messageSize, MPI::CHAR, 0, 1, status);
        
        std::string message(buffer, messageSize);
        
        rapidjson::Document document;
        document.Parse(message.c_str());
        Action* action = new Action();
        action->deserialize(document);
        std::cout << "Client received message: " << message << "\n";
        std::cout << "Client received action type " << action->getActionType() << "\n";
        std::cout << "Client received waiting time " << action->getWaitingTime() << "\n";
        std::cout << "Client received Movement's current state " << action->getMovement()->getCurrentState() << "\n";
        std::cout << "Client received Movement's destination's X " << action->getMovement()->getDestination()->getX() << "\n";
        std::cout << "Client received Movement's destination's Y " << action->getMovement()->getDestination()->getY() << "\n";
    }
    
    MPI::Finalize();

    return 0;
}

MPI::Intercomm startServer(){
    const char* port_name = openPort();
    return acceptConnection(port_name);
    //printRankAndSize(intercom);
    //sendMessageToAllClients(intercom);
}

void writePortNameToFile(const char* portName){
    std::ofstream portNameFile;
    portNameFile.open ("../portName.txt");
    portNameFile << portName;
    portNameFile.close();
}

const char* readPortNameFromFile(){
  std::string line;
  std::ifstream portNameFile ("../portName.txt");
  if (portNameFile.is_open()){
    if (std::getline (portNameFile, line)){
        return line.c_str();
    }
    portNameFile.close();
  }
}


MPI::Intercomm startClient(){
    //char port_name[MPI_MAX_PORT_NAME];
    const char* port_name = getPortName();    
    return connectToServer(port_name);
    //receiveMessageFromTheServer(intercom);
    //printRankAndSize(intercom);
}

void startGameLoop(){
    std::ofstream debugNPC( "../debugNPC.txt" );
    std::streambuf *coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(debugNPC.rdbuf());
    
    GameLoop game;
    game.doLoop();

    std::cout.rdbuf(coutbuf);
    debugNPC.close();
}

bool isServer(int argc, char** argv){
    std::vector<std::string> args;
    std::copy(argv + 1, argv + argc, std::back_inserter(args));
    
    bool server = false;
    for(int i=0; i<args.size(); i++){
        if(args[i] == "type=S"){
            server = true;
        }
    }
    return server;
}

const char* openPort(){
    char port_name[MPI_MAX_PORT_NAME];
    MPI::Open_port(MPI_INFO_NULL, port_name);
    writePortNameToFile(port_name);
    std::cout << "Server started\n";
    return port_name;
}

MPI::Intercomm acceptConnection(const char* port_name){
    MPI::Intercomm intercom = MPI::COMM_WORLD.Accept(port_name, MPI_INFO_NULL, 0);
    std::cout << "Server connected.\n";
    return intercom;
}

void sendMessageToAllClients(MPI::Intercomm intercom){
    int buffer[10];
    int i;
    int j;
    int size = intercom.Get_remote_size();
    int rank = intercom.Get_rank();
    for(j=0; j<size; j++){
        for (i=0; i<10; i++){
            buffer[i] = rand() % 100;;
        }
        intercom.Send(buffer, 10, MPI_INT, j, 123);
        std::cout << "Server rank" <<  rank << " sending message to client rank " << j <<"\n";
    }
    
}

void printRankAndSize(MPI::Intercomm intercom){
    int size = intercom.Get_remote_size();
    int rank = intercom.Get_rank();
    
    std::cout << "Hello, world. This is Server.  I am rank " << rank << ". There are " << size << " clients connected\n";
}

void receiveMessageFromTheServer(MPI::Intercomm intercom){
    int buffer[10];
    int i;
    int rank = intercom.Get_rank();
    std::cout << "Client rank " << rank << " is waiting for a message from the server\n";
    intercom.Recv(buffer, 10, MPI_INT, 0, 123);
    std::cout << "Client rank " << rank << " received the message from the server:\n";    
    for (i=0; i<10; i++){
        std::cout << "Buffer " << i << " : " << buffer[i] << "\n";
    }
}

MPI::Intercomm connectToServer(const char* port_name){
    MPI::Intercomm intercom = MPI::COMM_WORLD.Connect(port_name, MPI_INFO_NULL, 0);
    int rank = intercom.Get_rank();
    std::cout << "Client rank " << rank << " connected! \n"; 
    return intercom;
}

const char* getPortName(){
    int rank = MPI::COMM_WORLD.Get_rank();
    const char* port_name;
    if(rank == 0){
        port_name = readPortNameFromFile();
        broadcastPortName(port_name);
    }else{
        port_name = receiveBroadcastedPortName();
    }   
    return port_name;
}

void broadcastPortName(const char* port_name){
    int size = MPI::COMM_WORLD.Get_size();
    if(size<=1){
        return;
    }
    const char* buffer[1];
    buffer[0] = port_name;

    int j;
    for(j=1; j<size; j++){
       std::cout << "PROCESS RANK 0 SENDING PORT NAME TO RANK " << j << "\n"; 
       MPI::COMM_WORLD.Send(buffer, 1, MPI_CHAR, j, 66);;     
    }
}

char* receiveBroadcastedPortName(){
    int rank = MPI::COMM_WORLD.Get_rank();
    char* buffer[1];
    printf("PROCESS RANK %d WAITING FOR THE PORT NAME FROM RANK 0\n", rank);
    MPI::COMM_WORLD.Recv(buffer, 1, MPI_CHAR, 0, 66);
    printf("PROCESS RANK %d RECEIVED PORT NAME FROM RANK 0\n", rank);
    return buffer[0];
}