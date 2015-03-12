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
    MPI::Intercomm intercom = MPI::COMM_WORLD.Accept(port_name, MPI_INFO_NULL, DEFAULT_PROCESS_RANK);
    std::cout << "Server connected.\n";
    return intercom;
}

MPI::Intercomm MPIControl::connectToServer(const char* port_name){
    MPI::Intercomm intercom = MPI::COMM_WORLD.Connect(port_name, MPI_INFO_NULL, DEFAULT_PROCESS_RANK);
    int rank = intercom.Get_rank();
    std::cout << "Client rank " << rank << " connected! \n"; 
    return intercom;
}

void MPIControl::sendNPCs(std::vector<NPC*> NPCs){
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    
    serializeNPCs(NPCs, writer);
    
    std::string message = buffer.GetString();
    sendMPIStringMessage(message, NPCS_MESSAGE_ID);    
}

std::vector<NPC*> MPIControl::receiveNPCs(){
    rapidjson::Document document;
    std::string message = this->receiveMPIStringMessage(NPCS_MESSAGE_ID);
    document.Parse(message.c_str());
    return this->deserializeNPCs(document);
}

void MPIControl::serializeNPCs(std::vector<NPC*> NPCs, rapidjson::Writer<rapidjson::StringBuffer>& writer){
    writer.StartObject();
            
    writer.String("NPCs");
    writer.StartArray();
    for(int i=0; i< (NPCs.size()) ; i++){
        NPCs[i]->serialize(writer);
    }
    writer.EndArray();

    writer.EndObject();
} 

std::vector<NPC*> MPIControl::deserializeNPCs(rapidjson::Document& document){
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


void MPIControl::sendMPIStringMessage(std::string message, int messageId){
    this->intercomm.Send(message.c_str(), message.length(), MPI_CHAR, DEFAULT_PROCESS_RANK, messageId);
}

std::string MPIControl::receiveMPIStringMessage(int messageId){
    MPI::Status status;
    this->intercomm.Probe(DEFAULT_PROCESS_RANK, messageId, status);
    int messageSize = status.Get_count(MPI::CHAR);
    char *buffer = new char[messageSize];
    this->intercomm.Recv(buffer, messageSize, MPI_CHAR, DEFAULT_PROCESS_RANK, messageId, status);
    std::string message(buffer, messageSize);
    return message;
}
