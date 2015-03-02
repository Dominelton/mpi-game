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
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>

GameLoop::GameLoop() {
    this->diffLoop  = 0;
    this->startLoop = 0;
    this->endLoop   = 0;
    this->npcCount = 10000;
    spawnNPC();
}

GameLoop::GameLoop(const GameLoop& orig) {
}

GameLoop::~GameLoop() {
}

void GameLoop::spawnNPC(){
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
    std::ofstream loopTime( "../loopTime.txt" );
    
    long timeRun = 0;
    struct timespec sleepTime;
    sleepTime.tv_nsec = 20000000;
    sleepTime.tv_sec = 0;
    long j = 0;
    while(timeRun < 60000){
        startLoop = getCurrentMs();
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
        loopTime << "Loop " << j << ": " << diffLoop << "ms\n";
        timeRun += diffLoop;
        j++;
    }
    
    loopTime.close();
    
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