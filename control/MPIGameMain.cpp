#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "GameLoop.h"
#include <iostream>
#include <fstream>

bool isServer(int argc, char** argv);

//server functions
const char* openPort();
MPI::Intercomm acceptConnection(const char* port_name);
void sendMessageToAllClients(MPI::Intercomm intercom);
void printRankAndSize(MPI::Intercomm intercom);

//client functions
void getPortName(char* port_name);
char* receiveBroadcastedPortName();
void broadcastPortName(char* port_name);
void receiveMessageFromTheServer(MPI::Intercomm intercom);
MPI::Intercomm connectToServer(char* port_name);


void startServer();
void startClient();
void startGameLoop();


int main(int argc, char** argv) {
    MPI::Init(argc, argv);
    
//    if(isServer(argc, argv)){
//        startServer();
//    }else{
//        startClient();
//    }

    startGameLoop();
    
    MPI::Finalize();

    return 0;
}

void startServer(){
    const char* port_name = openPort();
    MPI::Intercomm intercom = acceptConnection(port_name);
    printRankAndSize(intercom);
    sendMessageToAllClients(intercom);
}

void startClient(){
    char port_name[MPI_MAX_PORT_NAME];
    getPortName(port_name);    
    MPI::Intercomm intercom = connectToServer(port_name);
    receiveMessageFromTheServer(intercom);
    printRankAndSize(intercom);
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
    std::cout << "The port name is: " << port_name << "\n";
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

MPI::Intercomm connectToServer(char* port_name){
    MPI::Intercomm intercom = MPI::COMM_WORLD.Connect(port_name, MPI_INFO_NULL, 0);
    int rank = intercom.Get_rank();
    std::cout << "Client rank " << rank << " connected! \n"; 
    return intercom;
}

void getPortName(char* port_name){
    int rank = MPI::COMM_WORLD.Get_rank();
    
    if(rank == 0){
        std::cout << "\nCLIENT RANK 0 AWATING PORT NAME INPUT:"; 
        gets(port_name);
        broadcastPortName(port_name);
    }else{
        port_name = receiveBroadcastedPortName();
    }    
}

void broadcastPortName(char* port_name){
    int size = MPI::COMM_WORLD.Get_size();
    if(size<=1){
        return;
    }
    char* buffer[1];
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
    printf("PROCESS RANK %d AWAITING PORT NAME FROM RANK 0\n", rank);
    MPI::COMM_WORLD.Recv(buffer, 1, MPI_CHAR, 0, 66);
    printf("PROCESS RANK %d RECEIVED PORT NAME FROM RANK 0\n", rank);
    return buffer[0];
}