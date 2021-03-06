/* 
 * File:   gameLoop.cpp
 * Author: wander
 * 
 * Created on September 25, 2014, 3:27 PM
 */

#include "GameLoop.h"

GameLoop::GameLoop() {
    this->init();
}

GameLoop::GameLoop(bool isServer) {
    this->init();
    
    this->isServer                    = isServer;
    this->mpi                         = new MPIControl(this->isServer);
}

GameLoop::GameLoop(const GameLoop& orig) {
}

GameLoop::~GameLoop() {
}

void GameLoop::init(){
    this->processingTimeStart.tv_nsec    = 0;
    this->processingTimeStart.tv_sec     = 0;
    this->processingTimeEnd.tv_nsec      = 0;
    this->processingTimeEnd.tv_sec       = 0;
    this->processingTime.tv_nsec         = 0;
    this->processingTime.tv_sec          = 0;

    this->loopTime.tv_nsec               = 0;
    this->loopTime.tv_sec                = 0;
    this->distributedLoopTime.tv_sec     = 0;
    this->distributedLoopTime.tv_nsec    = 0;
    this->sleepTime.tv_nsec              = (long)(1 / MPIGameConfig::MAX_UPS * Utils::NANOSECOND);
    this->sleepTime.tv_sec               = 0;
    this->elapsedTime.tv_nsec            = 0;
    this->elapsedTime.tv_sec             = 0;
    
    this->logicProcessingStart.tv_sec    = 0;
    this->logicProcessingStart.tv_nsec   = 0;
    this->logicProcessingEnd.tv_sec      = 0;
    this->logicProcessingEnd.tv_nsec     = 0;
    this->logicProcessing.tv_sec         = 0;
    this->logicProcessing.tv_nsec        = 0;
    this->distributedPhase1Start.tv_nsec = 0;
    this->distributedPhase1Start.tv_sec  = 0;
    this->distributedPhase1End.tv_nsec   = 0;
    this->distributedPhase1End.tv_sec    = 0;
    this->distributedPhase1.tv_nsec      = 0;
    this->distributedPhase1.tv_sec       = 0;
    this->distributedPhase2Start.tv_nsec = 0;
    this->distributedPhase2Start.tv_sec  = 0;
    this->distributedPhase2End.tv_nsec   = 0;
    this->distributedPhase2End.tv_sec    = 0;
    this->distributedPhase2.tv_nsec      = 0;
    this->distributedPhase2.tv_sec       = 0;
    
    spawnNPC();
}

void GameLoop::spawnNPC(){
    srand (time(NULL));
    this->NPCs.reserve(MPIGameConfig::NPC_COUNT);
    for(int i=0; i< MPIGameConfig::NPC_COUNT; i++){
        Position* position = new Position();
        Facing* facing = new Facing(90, 0);
        NPC* npc = new NPC(i, position, facing);
        this->NPCs.push_back(npc);
    }
}

void GameLoop::doLoop() {
    // Starts and opens a control file of the loop time to be measured
    char* dataFileName;
    char* loopTimeFileName;
    
    if (this->isServer){
        dataFileName = "../dataServer.csv";
        loopTimeFileName = "../loopTimeServer.txt";
    }
    else{
        dataFileName = "../dataClient.csv";
        loopTimeFileName = "../loopTimeClient.txt";
    }
    
    std::ofstream dataFile(dataFileName);
    std::ofstream loopTimeFile(loopTimeFileName);
    
    this->collectData(dataFile, 0, 0);
    
    // Starts elapsed time and loop count variables
    long loop = 0;
    while(elapsedTime.tv_sec < MPIGameConfig::SYSTEM_RUNTIME_SEC){
        
        // Get the current time on the start of the logic processing phase
        this->processingTimeStart = getCurrentTimeSpec();
        
        // Debugging processingTimeStart
        this->debug(MPIGameConfig::DEBUG_CLOCKS, 0, loopTimeFile);
        
        this->distributedPhase1Start = getCurrentTimeSpec();
        if (MPIGameConfig::DISTRIBUTE_PROCESSING){
            if (this->isServer){
                std::vector<NPC*> npcsToDistribute = getNPCsToDistribute();
                this->mpi->sendLoopTime(this->loopTime.tv_sec, this->loopTime.tv_nsec);
                this->mpi->sendNPCs(npcsToDistribute);
            }
            else{
                this->distributedLoopTime.tv_sec  = this->mpi->receiveLoopTimeSec();
                this->distributedLoopTime.tv_nsec = this->mpi->receiveLoopTimeNSec();
                this->distributedNPCs = this->mpi->receiveNPCs();
            }
        }
        this->distributedPhase1End = getCurrentTimeSpec();
        
        this->logicProcessingStart = getCurrentTimeSpec();
        // Execute the logic processing of the NPCs
        for (int i = 0; i < MPIGameConfig::NPC_COUNT; i++){
            this->NPCs[i]->executeAction(this->loopTime.tv_nsec + (this->loopTime.tv_sec * Utils::NANOSECOND));
        }
        
        if (MPIGameConfig::DISTRIBUTE_PROCESSING){
            if (!this->isServer){
                // Execute the logic processing of the distributed NPCs
                for (int i = 0; i < this->distributedNPCs.size(); i++){
                    this->distributedNPCs[i]->executeAction(this->distributedLoopTime.tv_nsec + (this->distributedLoopTime.tv_sec * Utils::NANOSECOND));
                }
            }
        }
        this->logicProcessingEnd = getCurrentTimeSpec();
        
        this->distributedPhase2Start = getCurrentTimeSpec();
        if (MPIGameConfig::DISTRIBUTE_PROCESSING){
            if (this->isServer){
                std::vector<NPC*> processedNPCs = this->mpi->receiveNPCs();
                
                this->updateNPCs(processedNPCs);
            }
            else{
                this->mpi->sendNPCs(this->distributedNPCs);
            }
        }
        this->distributedPhase2End = getCurrentTimeSpec();
        
        // Get the current time on the end of the logic processing phase
        this->processingTimeEnd   = getCurrentTimeSpec();
        
        // Set the elapsed times of code blocs
        this->distributedPhase1 = Utils::timespecSubtract(this->distributedPhase1End, this->distributedPhase1Start);
        this->distributedPhase2 = Utils::timespecSubtract(this->distributedPhase2End, this->distributedPhase2Start);
        this->logicProcessing = Utils::timespecSubtract(this->logicProcessingEnd, this->logicProcessingStart);
        
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
        
        // Increments elapsed time and loop count
        this->elapsedTime = Utils::timespecSum(this->elapsedTime, this->loopTime);
        loop++;
        
        // Debugging elapsedTime
        this->debug(MPIGameConfig::DEBUG_CLOCKS, 5, loopTimeFile);
        
        this->collectData(dataFile, 1, loop);
    }
    
    loopTimeFile << "Loops: " << loop;
            
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
    long updateNS = (long)(Utils::NANOSECOND / MPIGameConfig::MAX_UPS);
    
    this->sleepTime.tv_nsec = updateNS;
    this->sleepTime.tv_sec  = 0;
    
    this->sleepTime = Utils::timespecSubtract(this->sleepTime, this->processingTime);
}

void GameLoop::debug(bool isDebugging, int variableToDebug, std::ofstream& file){
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

void GameLoop::collectData(std::ofstream& file, int data, int loop){
    char separator = ',';
    if (MPIGameConfig::COLLECT_DATA){
        switch (data){
            case 0: {
                file << "NPCs" << separator << MPIGameConfig::NPC_COUNT << "\n";
                file << "MPI" << separator;
                if (MPIGameConfig::DISTRIBUTE_PROCESSING){
                    file << "Enabled\n";
                }
                else{
                    file << "Disabled\n";
                }
                file << "Loop" << separator << "Processing Time" << separator << "Logic Processing" << separator << "Distributed P1" << separator << "Distributed P2\n";
            }
            break;
            case 1: {
                file << loop << separator;
                file << ((this->processingTime.tv_sec * Utils::NANOSECOND) + this->processingTime.tv_nsec) << separator;
                file << ((this->logicProcessing.tv_sec * Utils::NANOSECOND) + this->logicProcessing.tv_nsec) << separator;
                file << ((this->distributedPhase1.tv_sec * Utils::NANOSECOND) + this->distributedPhase1.tv_nsec) << separator;
                file << ((this->distributedPhase2.tv_sec * Utils::NANOSECOND) + this->distributedPhase2.tv_nsec) << "\n";
            }
            break;
        }
    }
}

std::vector<NPC*> GameLoop::getNPCsToDistribute(){
    std::vector<NPC*> npcsToDistribute;
    
    int elements = (int)(this->NPCs.size()/2);
    
    for (int i = 0; i < elements; i++){
        npcsToDistribute.push_back(this->NPCs[this->NPCs.size() - 1]);
        this->NPCs.pop_back();
    }
    
    return npcsToDistribute;
}

void GameLoop::updateNPCs(std::vector<NPC*> processedNPCs){
    for (int i = 0; i < processedNPCs.size(); i++){
        this->NPCs.push_back(processedNPCs[i]);
    }
}