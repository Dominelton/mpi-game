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

class GameLoop {
public:
    GameLoop();
    GameLoop(const GameLoop& orig);
    virtual ~GameLoop();
    void doLoop();
private:
    clock_t startLoop;
    clock_t endLoop;
    std::vector<NPC> npcs;
};

#endif	/* GAMELOOP_H */

