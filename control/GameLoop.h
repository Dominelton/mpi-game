/* 
 * File:   gameLoop.h
 * Author: wander
 *
 * Created on September 25, 2014, 3:27 PM
 */

#ifndef GAMELOOP_H
#define	GAMELOOP_H

#include <time.h>
#include <vector>
#include "Action.h"


class GameLoop {
public:
    GameLoop();
    GameLoop(const GameLoop& orig);
    virtual ~GameLoop();
    void doLoop();
    long getCurrentMs();
    
private:
    void spawnNPC();
    long startLoop;
    long endLoop;
    long diffLoop;
    long actionCount;
    std::vector<Action*> actions;
};

#endif	/* GAMELOOP_H */

