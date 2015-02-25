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
#include <cmath>

GameLoop::GameLoop() {
    //spawnNPC();
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
    
    int x1 = 0;
    int y1 = 0;
    int z1 = 0;
    
    int x2 = -5;
    int y2 = 5;
    int z2 = 5;
    
    double deltaX = x2 - x1;
    double deltaY = y2 - y1;
    double deltaZ = z2 - z1;
    
    double facingAngleXY = atan2(deltaY, deltaX) * 180 / M_PI;
    
    double theta = atan2(deltaZ, deltaX);
    
    
    std::cout << "Angulo XY: " << facingAngleXY;
    
    std::cout << "Angulo XY: " << theta * 180 / M_PI;
    
    double dist=sqrt(pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2));
    
    double dist2=sqrt(pow(deltaX, 2) + pow(deltaZ, 2));
    
    std::cout << "Angulo Z: " << acos(dist2/dist) * 180 / M_PI;
    
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
