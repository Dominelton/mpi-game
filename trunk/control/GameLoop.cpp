/* 
 * File:   gameLoop.cpp
 * Author: wander
 * 
 * Created on September 25, 2014, 3:27 PM
 */

#include "GameLoop.h"


GameLoop::GameLoop() {
    this->processingTimeStart = 0;
    this->processingTimeEnd   = 0;
    this->processingTimeDiff  = 0;
    this->loopTime            = 0;
    this->sleepTime.tv_nsec   = MPIGameConfig::MIN_LOOP_TIME_NS;
    this->sleepTime.tv_sec    = 0;
    
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
    // Starts and opens a control file of the loop time to be measured
    std::ofstream loopTimeFile( "../loopTime.txt" );
    
    // Starts elapsed time and loop count variables
    long elapsedTime = 0;
    long loop = 0;
    while(elapsedTime < MPIGameConfig::SYSTEM_RUNTIME_MS){
        
        // Get the current time on the start of the logic processing phase
        this->processingTimeStart = getCurrentMs();
        
        // Execute the logic processing
        for (int i = 0; i < MPIGameConfig::NPC_COUNT; i++){
            this->npcs[i]->executeAction(this->loopTime);
        }
        
        // Get the current time on the end of the logic processing phase
        this->processingTimeEnd   = getCurrentMs();
        
        // Set the elapsed time of the logic processing
        this->processingTimeDiff = this->processingTimeEnd - this->processingTimeStart;
        if (this->processingTimeDiff < 0){
            this->processingTimeDiff += 1000;
        }
        
        // Sleep to upstand the Config UPS
        this->doSleep();
        
        // Print the loop time on a control file
        loopTimeFile << "Loop " << loop << ": " << this->loopTime << "ms\n";
        
        // Increments elapsed time and loop count
        elapsedTime += this->loopTime;
        loop++;
    }
    
    // Closes the control file of the loop time to be measured
    loopTimeFile.close();
}

long GameLoop::getCurrentMs(){
    long   ms; // Milliseconds
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    return round(spec.tv_nsec / 1.0e6);
}

void GameLoop::doSleep(){
    // Set the sleep timers in nanoseconds and milliseconds for calculations
    long sleepTimeNs = MPIGameConfig::MIN_LOOP_TIME_NS - (this->processingTimeDiff * 1000000);
    long sleepTimeMs = sleepTimeNs / 1000000;
    
    this->loopTime = this->processingTimeDiff;
    
    // Calculate the loop time including a possible sleep of the loop
    if (sleepTimeMs > 0){
        this->loopTime += sleepTimeMs;

        this->sleepTime.tv_nsec = sleepTimeNs;
        nanosleep(&this->sleepTime, NULL);
    }
}