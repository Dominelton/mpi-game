/* 
 * File:   gameLoop.h
 * Author: wander
 *
 * Created on September 25, 2014, 3:27 PM
 */

#ifndef GAMELOOP_H
#define	GAMELOOP_H

#include "../model/NPC.h"
#include "../model/Facing.h"
#include "../model/Position.h"
#include "../config/MPIGameConfig.h"
#include "MPIControl.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

class GameLoop {
public:
    GameLoop();
    GameLoop(bool);
    GameLoop(const GameLoop& orig);
    virtual ~GameLoop();
    void doLoop();
    
    std::vector<NPC*> getNPCs(){
        return this->NPCs;
    }
    
    std::vector<NPC*> getDisctributedNPCs(){
        return this->distributedNPCs;
    }
    
    void setDistributedLoopTime(long sec, long nsec){
        this->distributedLoopTime.tv_sec  = sec;
        this->distributedLoopTime.tv_nsec = nsec;
    }
    
private:
    void init();
    void spawnNPC();
    void debug(bool, int, std::ofstream&);
    timespec getCurrentTimeSpec();
    void doSleep();
    void calculateSleepTime();
    void collectData(std::ofstream&, int, int);
    
    std::vector<NPC*> getNPCsToDistribute();
    void updateNPCs(std::vector<NPC*>);
    
    struct timespec processingTimeStart;
    struct timespec processingTimeEnd;
    struct timespec processingTime;
    
    struct timespec sleepTime;
    struct timespec elapsedTime;
    
    struct timespec loopTime;
    struct timespec distributedLoopTime;
    
    struct timespec logicProcessingStart;
    struct timespec logicProcessingEnd;
    struct timespec logicProcessing;
    
    struct timespec distributedPhase1Start;
    struct timespec distributedPhase1End;
    struct timespec distributedPhase1;
    struct timespec distributedPhase2Start;
    struct timespec distributedPhase2End;
    struct timespec distributedPhase2;
    
    std::vector<NPC*> NPCs;
    std::vector<NPC*> distributedNPCs;
    
    bool isServer;
    
    MPIControl* mpi;
};

#endif	/* GAMELOOP_H */
