/* 
 * File:   gameLoop.h
 * Author: wander
 *
 * Created on September 25, 2014, 3:27 PM
 */

#ifndef GAMELOOP_H
#define	GAMELOOP_H

#include "NPC.h"
#include "Facing.h"
#include "Position.h"
#include "MPIGameConfig.h"
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
    void spawnNPC();
    void debug(bool, int, std::ofstream&);
    timespec getCurrentTimeSpec();
    void doSleep();
    void calculateSleepTime();
    
    std::vector<NPC*> getNPCsToDistribute();
    void updateNPCs(std::vector<NPC*>);
    
    struct timespec processingTimeStart;
    struct timespec processingTimeEnd;
    struct timespec processingTime;
    struct timespec loopTime;
    struct timespec sleepTime;
    struct timespec elapsedTime;
    struct timespec distributedLoopTime;
    
    std::vector<NPC*> NPCs;
    std::vector<NPC*> distributedNPCs;
    
    bool isServer;
    
    MPIControl* mpi;
};

#endif	/* GAMELOOP_H */
