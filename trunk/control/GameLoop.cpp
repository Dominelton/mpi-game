/* 
 * File:   gameLoop.cpp
 * Author: wander
 * 
 * Created on September 25, 2014, 3:27 PM
 */

#include "GameLoop.h"

GameLoop::GameLoop() {
    this->processingTimeStart.tv_nsec = 0;
    this->processingTimeStart.tv_sec  = 0;
    this->processingTimeEnd.tv_nsec   = 0;
    this->processingTimeEnd.tv_sec    = 0;
    this->processingTime.tv_nsec      = 0;
    this->processingTime.tv_sec       = 0;
    
    this->loopTime.tv_nsec            = 0;
    this->loopTime.tv_sec             = 0;
    this->sleepTime.tv_nsec           = (long)(1 / MPIGameConfig::MAX_UPS * Utils::NANOSECOND);
    this->sleepTime.tv_sec            = 0;
    this->elapsedTime.tv_nsec         = 0;
    this->elapsedTime.tv_sec          = 0;
    
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
    long loop = 0;
    while(elapsedTime.tv_sec < MPIGameConfig::SYSTEM_RUNTIME_SEC){
        
        // Get the current time on the start of the logic processing phase
        this->processingTimeStart = getCurrentTimeSpec();
        
        // Debugging processingTimeStart
        this->debug(MPIGameConfig::DEBUG_CLOCKS, 0, loopTimeFile);
        
        // Execute the logic processing
        for (int i = 0; i < MPIGameConfig::NPC_COUNT; i++){
            this->npcs[i]->executeAction(this->loopTime.tv_nsec + (this->loopTime.tv_sec * Utils::NANOSECOND));
        }
        
        // Get the current time on the end of the logic processing phase
        this->processingTimeEnd   = getCurrentTimeSpec();
        
        // Debugging processingTimeEnd
        this->debug(MPIGameConfig::DEBUG_CLOCKS, 1, loopTimeFile);
        
        // Set the elapsed time of the logic processing
        this->processingTime = Utils::timespecSubtract(this->processingTimeEnd, this->processingTimeStart);
        
        // Debugging processingTime
        this->debug(MPIGameConfig::DEBUG_CLOCKS, 2, loopTimeFile);
        
        // Sleep to upstand the Config UPS
        this->doSleep();
        
        // Debugging sleepTime
        this->debug(MPIGameConfig::DEBUG_CLOCKS, 3, loopTimeFile);
        
        // Debugging loopTime
        this->debug(MPIGameConfig::DEBUG_CLOCKS, 4, loopTimeFile);
        
        // Print the loop time on a control file
        loopTimeFile << "Loop " << loop << ": " << this->loopTime.tv_nsec << "ns\n";
        
        // Increments elapsed time and loop count
        this->elapsedTime = Utils::timespecSum(this->elapsedTime, this->loopTime);
        loop++;
        
        // Debugging elapsedTime
        this->debug(MPIGameConfig::DEBUG_CLOCKS, 5, loopTimeFile);
    }
    
    // Closes the control file of the loop time to be measured
    loopTimeFile.close();
}

timespec GameLoop::getCurrentTimeSpec(){
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    return spec;
}

void GameLoop::doSleep(){
    this->calculateSleepTime();
    
    this->loopTime = this->processingTime;
    
    // Calculate the loop time including a possible sleep of the loop
    if (this->sleepTime.tv_sec > 0 || this->sleepTime.tv_nsec > 0){
        this->loopTime = Utils::timespecSum(this->loopTime, this->sleepTime);
        
        nanosleep(&this->sleepTime, NULL);
    }
}

void GameLoop::calculateSleepTime(){
    long updateNS = (long)(1 / MPIGameConfig::MAX_UPS * Utils::NANOSECOND);
    
    this->sleepTime.tv_nsec = updateNS;
    this->sleepTime.tv_sec  = 0;
    
    this->sleepTime = Utils::timespecSubtract(this->sleepTime, this->processingTime);
}

void GameLoop::debug(bool isDebugging, int variableToDebug, std::ofstream file){
    if (isDebugging){
        switch (variableToDebug){
            case 0: {
                file << "processingTimeStart:\n";
                file << "{\n";
                file << "    tv_sec: " << this->processingTimeStart.tv_sec << "\n";
                file << "    tv_nsec: " << this->processingTimeStart.tv_nsec << "\n";
                file << "}\n";
            }
                break;
            case 1: {
                file << "processingTimeEnd:\n";
                file << "{\n";
                file << "    tv_sec: " << this->processingTimeEnd.tv_sec << "\n";
                file << "    tv_nsec: " << this->processingTimeEnd.tv_nsec << "\n";
                file << "}\n";
            }
                break;
            case 2: {
                file << "processingTime:\n";
                file << "{\n";
                file << "    tv_sec: " << this->processingTime.tv_sec << "\n";
                file << "    tv_nsec: " << this->processingTime.tv_nsec << "\n";
                file << "}\n";
            }
                break;
            case 3: {
                file << "sleepTime:\n";
                file << "{\n";
                file << "    tv_sec: " << this->sleepTime.tv_sec << "\n";
                file << "    tv_nsec: " << this->sleepTime.tv_nsec << "\n";
                file << "}\n";
            }
                break;
            case 4: {
                file << "loopTime:\n";
                file << "{\n";
                file << "    tv_sec: " << this->loopTime.tv_sec << "\n";
                file << "    tv_nsec: " << this->loopTime.tv_nsec << "\n";
                file << "}\n";
            }
                break;
            case 5: {
                file << "elapsedTime:\n";
                file << "{\n";
                file << "    tv_sec: " << this->elapsedTime.tv_sec << "\n";
                file << "    tv_nsec: " << this->elapsedTime.tv_nsec << "\n";
                file << "}\n";
            }
                break;
        }
    }
}