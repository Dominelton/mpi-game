/* 
 * File:   gameLoop.h
 * Author: wander
 *
 * Created on September 25, 2014, 3:27 PM
 */

#ifndef GAMELOOP_H
#define	GAMELOOP_H

class gameLoop {
public:
    gameLoop();
    gameLoop(const gameLoop& orig);
    virtual ~gameLoop();
    void doLoop();
private:
    int startLoop;
    int endLoop;
};

#endif	/* GAMELOOP_H */

