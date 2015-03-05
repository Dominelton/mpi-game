/* 
 * File:   Action.h
 * Author: skrep
 *
 * Created on 25 de Fevereiro de 2015, 19:37
 */

#ifndef ACTION_H
#define	ACTION_H

#include "Movement.h"
#include "MPIGameConfig.h"
#include "Utils.h"

#include <time.h>
#include <stdlib.h>

class Action {
public:
    const static int WAIT   = 0;
    const static int MOVETO = 1;
    
    Action();
    Action(long);
    Action(const Action& orig);
    virtual ~Action();

    void waitRandomTime();
    
    void reduceWaitingTime(long time);
    
    void moveTo(Position* destination);
    
    void updatePositionAndFacing(Position*&, Facing*&, long);
    
    void setMovement(Movement* movement) {
        this->movement = movement;
    }

    Movement* getMovement() const {
        return movement;
    }

    void setWaitingTime(long waitingTime) {
        this->waitingTime = waitingTime;
    }

    long getWaitingTime() const {
        return waitingTime;
    }

    void setActionType(int actionType) {
        this->actionType = actionType;
    }

    int getActionType() const {
        return actionType;
    }
    
    
private:
    int actionType;
    long waitingTime;
    Movement* movement;
};

#endif	/* ACTION_H */

