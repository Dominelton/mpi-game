/* 
 * File:   gameLoop.cpp
 * Author: wander
 * 
 * Created on September 25, 2014, 3:27 PM
 */

#include "GameLoop.h"


GameLoop::GameLoop() {
    this->diffLoop  = 0;
    this->startLoop = 0;
    this->endLoop   = 0;
    this->loopTime  = 0;
    this->sleepTime.tv_nsec = MPIGameConfig::MIN_LOOP_TIME_NS;
    this->sleepTime.tv_sec = 0;
    
    spawnNPC();
}

GameLoop::GameLoop(const GameLoop& orig) {
}

GameLoop::~GameLoop() {
}

void GameLoop::spawnNPC(){
    srand (time(NULL));
    this->npcs.reserve(MPIGameConfig::NPC_COUNT);
    for(int i=0; i< MPIGameConfig::NPC_COUNT; i++){
        Position* position = new Position();
        Facing* facing = new Facing(90, 0);
        NPC* npc = new NPC(i, position, facing);
        this->npcs.push_back(npc);
    }
}

void GameLoop::doLoop() {
    std::ofstream loopTime( "../loopTime.txt" );
    
    long timeRun = 0;
    long j = 0;
    while(timeRun < MPIGameConfig::SYSTEM_RUNTIME_MS){
        this->startLoop = getCurrentMs();
        // Aqui executa toda a lógica de loop
        for (int i = 0; i < MPIGameConfig::NPC_COUNT; i++){
            this->npcs[i]->executeAction(this->loopTime);
        }
        
        this->endLoop   = getCurrentMs();
        this->diffLoop = this->endLoop - this->startLoop;
        if (this->diffLoop < 0){
            this->diffLoop += 1000;
        }
        
        long sleepTimeNs = MPIGameConfig::MIN_LOOP_TIME_NS - (this->diffLoop * 1000000);
        long sleepTimeMs = sleepTimeNs / 1000000;
        
        if (sleepTimeMs > 0){
            this->loopTime = diffLoop + sleepTimeMs;
            
            this->sleepTime.tv_nsec = sleepTimeNs;
            nanosleep(&this->sleepTime, NULL);
        }
        else{
            this->loopTime = diffLoop;
        }
        
        loopTime << "Loop " << j << ": " << this->loopTime << "ms\n";
        
        timeRun += this->loopTime;
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