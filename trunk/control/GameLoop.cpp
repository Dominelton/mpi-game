/* 
 * File:   gameLoop.cpp
 * Author: wander
 * 
 * Created on September 25, 2014, 3:27 PM
 */

#include "GameLoop.h"
#include "Facing.h"
#include "Position.h"
#include "NPC.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <cmath>

GameLoop::GameLoop() {
    this->diffLoop  = 0;
    this->startLoop = 0;
    this->endLoop   = 0;
    this->npcCount = 1;
    spawnNPC();
}

GameLoop::GameLoop(const GameLoop& orig) {
}

GameLoop::~GameLoop() {
}

void GameLoop::spawnNPC(){
    /*this->npcs.reserve(100);
    srand (time(NULL));
    for (int id = 0; id < 100; id++){
        Position* position = new Position(rand() % 1000, rand() % 1000, rand() % 1000);
        Movement* movement = new Movement(position);
        NPC* npc = new NPC(id, movement);
        this->npcs[id] = npc;
    }*/
    srand (time(NULL));
    this->npcs.reserve(this->npcCount);
    for(int i=0; i< this->npcCount; i++){
        Position* position = new Position();
        Facing* facing = new Facing(90, 0);
        NPC* npc = new NPC(i, position, facing);
        this->npcs.push_back(npc);
    }
}

void GameLoop::doLoop() {
    std::ofstream dataFile( "../dataFile.txt" );
    std::streambuf *coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(dataFile.rdbuf());
    
    long timeRun = 0;
    struct timespec sleepTime;
    sleepTime.tv_nsec = 10000000;
    sleepTime.tv_sec = 0;
    while(timeRun < 5000){
        startLoop = getCurrentMs();
        std::cout << "********** NEW TURN STARTING AT " << startLoop << " ms. **********\n";
        // Aqui executa toda a lógica de loop
        for (int i = 0; i < this->npcCount; i++){
            npcs[i]->executeAction(diffLoop);
        }
        
        nanosleep(&sleepTime, NULL);
        
        endLoop   = getCurrentMs();
        diffLoop = endLoop - startLoop;
        if (diffLoop < 0){
            diffLoop += 1000;
        }
        std::cout << "********** TURN ENDING AT " << endLoop << " ms. ****************\n";
        timeRun += diffLoop;
    }
    
    std::cout.rdbuf(coutbuf);
    dataFile.close();
    
    /*int n = 0;
    while (n < 100){
        
        std::cout << "NPC id " << npcs[n]->getId() << "\n";
        std::cout << "Position start x " << npcs[n]->getMovement()->getStart()->getX() << "\n";
        std::cout << "Position start y " << npcs[n]->getMovement()->getStart()->getY() << "\n";
        std::cout << "Position start z " << npcs[n]->getMovement()->getStart()->getZ() << "\n";
        n++;
    }*/
    
    /* 
    std::ofstream dataFile;
    dataFile.open( "../dataFile.txt" );
    
    n = 0;
    while (n < 100){
    
        startLoop = clock();

        endLoop = clock();
        
        dataFile << "Loop " << n << ":\n";
        dataFile << startLoop << "\n";
     
        dataFile << "NPC " << n << ":\n";
        dataFile << "id: " << npcs[n]->getId() << "\n";
      
        dataFile << endLoop << "\n";
        dataFile << CLOCKS_PER_SEC << "\n";
        
        n++;
    }
    
    dataFile.close();*/
}

long GameLoop::getCurrentMs(){
    long   ms; // Milliseconds
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    return round(spec.tv_nsec / 1.0e6);
}