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
void startGameLoop(bool);



int main(int argc, char** argv) {
    
    MPIGameConfig::loadConfigFromFile("config.txt");
    
    if (MPIGameConfig::DISTRIBUTE_PROCESSING){
        
        MPI::Init(argc, argv);
        
        startGameLoop(isServer(argc, argv));
        
        MPI::Finalize();
    }
    else{
        startGameLoop(false);
    }
    
    return 0;
}

void startGameLoop(bool isServer){
    std::ofstream debugNPC( "../standardDebugFile.txt" );
    std::streambuf *coutbuf = std::cout.rdbuf();
    
    if (MPIGameConfig::DEBUG_FILE_ENABLED){
        std::cout.rdbuf(debugNPC.rdbuf());
    }
    
    GameLoop* game;
    if (MPIGameConfig::DISTRIBUTE_PROCESSING){
        game = new GameLoop(isServer);
    }
    else{
        game = new GameLoop();
    }
    
    game->doLoop();
    if (MPIGameConfig::DEBUG_FILE_ENABLED){
        std::cout.rdbuf(coutbuf);
    }
    
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