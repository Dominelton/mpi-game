/* 
 * File:   gameLoop.cpp
 * Author: wander
 * 
 * Created on September 25, 2014, 3:27 PM
 */

#include "GameLoop.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <NPC.h>
#include <time.h> 

GameLoop::GameLoop() {
    spawnNPC();
}

GameLoop::GameLoop(const GameLoop& orig) {
}

GameLoop::~GameLoop() {
}

void GameLoop::spawnNPC(){
    this->npcs.reserve(100);
    srand (time(NULL));
    for (int id = 0; id < 100; id++){
        Position* position = new Position(rand() % 1000, rand() % 1000, rand() % 1000);
        Movement* movement = new Movement(position);
        NPC* npc = new NPC(id, movement);
        this->npcs[id] = npc;
    }
}

void GameLoop::doLoop() {
    
     
    std::ofstream dataFile;
    dataFile.open( "../dataFile.txt" );
    
    int n = 0;
    while (n < 100){
        dataFile << "NPC " << n << ":\n";
        dataFile << "id: " << npcs[n]->getId() << "\n";
        std::cout << "NPC id " << npcs[n]->getId() << "\n";
        std::cout << "Position start x " << npcs[n]->getMovement()->getStart()->getX() << "\n";
        std::cout << "Position start y " << npcs[n]->getMovement()->getStart()->getY() << "\n";
        std::cout << "Position start z " << npcs[n]->getMovement()->getStart()->getZ() << "\n";
        n++;
    }
    
    n = 1;
    while (n < 100){
    
        startLoop = clock();

        endLoop = clock();
        
        dataFile << "Loop " << n << ":\n";
        dataFile << startLoop << "\n";
        dataFile << endLoop << "\n";
        dataFile << CLOCKS_PER_SEC << "\n";
        
        n++;
    }
    
    dataFile.close();
}