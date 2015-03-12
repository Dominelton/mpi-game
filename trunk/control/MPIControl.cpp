/* 
 * File:   MPIControl.cpp
 * Author: wander
 * 
 * Created on March 11, 2015, 9:00 PM
 */

#include "MPIControl.h"

MPIControl::MPIControl() {
}

MPIControl::MPIControl(bool isServer) {
    
    if(isServer){
        this->intercomm = this->startServer();
    }else{
        this->intercomm = this->startClient();
    }
}

MPIControl::MPIControl(const MPIControl& orig) {
}

MPIControl::~MPIControl() {
}

MPI::Intercomm MPIControl::startServer(){
    const char* port_name = openPort();
    return acceptConnection(port_name);
}

MPI::Intercomm MPIControl::startClient(){
    const char* port_name = readPortNameFromFile();    
    return connectToServer(port_name);
}

void MPIControl::writePortNameToFile(const char* portName){
    std::ofstream portNameFile;
    portNameFile.open ("../portName.txt");
    portNameFile << portName;
    portNameFile.close();
}

const char* MPIControl::readPortNameFromFile(){
  std::string line;
  std::ifstream portNameFile ("../portName.txt");
  if (portNameFile.is_open()){
    if (std::getline (portNameFile, line)){
        return line.c_str();
    }
    portNameFile.close();
  }
}

const char* MPIControl::openPort(){
    char port_name[MPI_MAX_PORT_NAME];
    MPI::Open_port(MPI_INFO_NULL, port_name);
    writePortNameToFile(port_name);
    std::cout << "Server started\n";
    return port_name;
}

MPI::Intercomm MPIControl::acceptConnection(const char* port_name){
    MPI::Intercomm intercom = MPI::COMM_WORLD.Accept(port_name, MPI_INFO_NULL, 0);
    std::cout << "Server connected.\n";
    return intercom;
}

MPI::Intercomm MPIControl::connectToServer(const char* port_name){
    MPI::Intercomm intercom = MPI::COMM_WORLD.Connect(port_name, MPI_INFO_NULL, 0);
    int rank = intercom.Get_rank();
    std::cout << "Client rank " << rank << " connected! \n"; 
    return intercom;
}

void MPIControl::sendNPCs(std::vector<NPC*> NPCs){
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    
    writer.StartObject();
            
    writer.String("NPCs");
    writer.StartArray();
    for(int i=0; i< (NPCs.size()) ; i++){
        NPCs[i]->serialize(writer);
    }
    writer.EndArray();

    writer.EndObject();
    
    std::string message = buffer.GetString();
    intercomm.Send(message.c_str(), message.length(), MPI_CHAR, 0, 1);
}

std::vector<NPC*> MPIControl::receiveNPCs(){
    MPI::Status status;
    intercomm.Probe(0, 1, status);
    int messageSize = status.Get_count(MPI::CHAR);
    char *buffer = new char[messageSize];
    intercomm.Recv(buffer, messageSize, MPI::CHAR, 0, 1, status);

    std::string message(buffer, messageSize);

    rapidjson::Document document;
    document.Parse(message.c_str());
    rapidjson::Value& valueNPCs = document["NPCs"];
    std::vector<NPC*> NPCs;
    for(int i=0; i< valueNPCs.Size(); i++){
        NPC* npc = new NPC();
        npc->deserialize(valueNPCs[i]);
        std::cout << "NPC received: " << npc->getId() << "\n";
        NPCs.push_back(npc);
    }
    return NPCs;
}
