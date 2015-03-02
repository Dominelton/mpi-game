#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "GameLoop.h"
#include <iostream>
#include <fstream>

const char* openPort();
MPI::Intercomm acceptConnection(const char* port_name);
void sendMessageToAllClients(MPI::Intercomm intercom);
void printRankAndSize(MPI::Intercomm intercom);
/*
 *
 */
int main(int argc, char** argv) {
    /*MPI::Init(argc, argv);
    
    const char* port_name = openPort();
    MPI::Intercomm intercom = acceptConnection(port_name);
    
    MPI::Finalize();*/
    
    std::ofstream debugNPC( "../debugNPC.txt" );
    std::streambuf *coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(debugNPC.rdbuf());
    
    GameLoop game;
    game.doLoop();
    
    std::cout.rdbuf(coutbuf);
    debugNPC.close();
    
    return 0;
}

const char* openPort(){
    char port_name[MPI_MAX_PORT_NAME];
    MPI::Open_port(MPI_INFO_NULL, port_name);
    printf("The port name is: %s\n", port_name);
    return port_name;
}

MPI::Intercomm acceptConnection(const char* port_name){
    MPI::Intercomm intercom = MPI::COMM_WORLD.Accept(port_name, MPI_INFO_NULL, 0);
    printf("server connected\n");
    return intercom;
}

