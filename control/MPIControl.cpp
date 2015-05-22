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
    char* port_name; //= readPortNameFromFile();    
    gets(port_name);
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
    //writePortNameToFile(port_name);
    std::cout << "PortName: " << port_name << "\n";
    std::cout << "***MPI*** - Server started\n";
    return port_name;
}

MPI::Intercomm MPIControl::acceptConnection(const char* port_name){
    MPI::Intercomm intercom = MPI::COMM_WORLD.Accept(port_name, MPI_INFO_NULL, DEFAULT_PROCESS_RANK);
    std::cout << "***MPI*** - Server connected.\n";
    return intercom;
}

MPI::Intercomm MPIControl::connectToServer(const char* port_name){
    MPI::Intercomm intercom = MPI::COMM_WORLD.Connect(port_name, MPI_INFO_NULL, DEFAULT_PROCESS_RANK);
    int rank = intercom.Get_rank();
    std::cout << "***MPI*** - Client rank " << rank << " connected! \n"; 
    return intercom;
}

void MPIControl::sendLoopTime(long int sec, long int nsec){
    sendMPILongMessage(sec, LOOPTIME_SEC_MESSAGE_ID);
    sendMPILongMessage(nsec, LOOPTIME_NSEC_MESSAGE_ID);
}

long int MPIControl::receiveLoopTimeSec(){
    return this->receiveMPILongMessage(LOOPTIME_SEC_MESSAGE_ID);
}

long int MPIControl::receiveLoopTimeNSec(){
    return this->receiveMPILongMessage(LOOPTIME_NSEC_MESSAGE_ID);
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

void MPIControl::sendMPILongMessage(long int message, int messageId){
    this->intercomm.Send(&message, 1, MPI_LONG, DEFAULT_PROCESS_RANK, messageId);
}

long int MPIControl::receiveMPILongMessage(int messageId){
    MPI::Status status;
    this->intercomm.Probe(DEFAULT_PROCESS_RANK, messageId, status);
    int messageSize = status.Get_count(MPI::LONG);
    long int number;
    this->intercomm.Recv(&number, messageSize, MPI_LONG, DEFAULT_PROCESS_RANK, messageId, status);
    
    return number;
}