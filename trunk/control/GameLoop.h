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
    GameLoop(const GameLoop& orig);
    virtual ~GameLoop();
    void doLoop();
    long getCurrentMs();
    void doSleep();
    
    std::vector<NPC*> getNPCS(){
        return this->npcs;
    }
    
private:
    void spawnNPC();
    long processingTimeStart;
    long processingTimeEnd;
    long processingTimeDiff;
    long loopTime;
    struct timespec sleepTime;
    std::vector<NPC*> npcs;
};

#endif	/* GAMELOOP_H */

