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

GameLoop::GameLoop() {
    spawnNPC();
}

GameLoop::GameLoop(const GameLoop& orig) {
}

GameLoop::~GameLoop() {
}

void GameLoop::spawnNPC(){
    npcs.reserve(100);
    for (int id = 0; id < 100; id++){
        Position position(rand() % 1000, rand() % 1000, rand() % 1000);
        Movement movement(position);
        NPC npc(id, movement);
        npcs[id] = npc;
    }
}

void GameLoop::doLoop() {
    
    
    std::ofstream dataFile;
    dataFile.open( "../dataFile.txt" );
    
    int n = 0;
    while (n < 100){
        dataFile << "NPC " << n << ":\n";
        dataFile << "id: " << npcs[n].getId() << "\n";
        std::cout << "xxx " << npcs[n].getId() << "\n";
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