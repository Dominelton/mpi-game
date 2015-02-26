/* 
 * File:   Action.h
 * Author: skrep
 *
 * Created on 25 de Fevereiro de 2015, 19:37
 */

#ifndef ACTION_H
#define	ACTION_H

#include "Movement.h"
#include "Character.h"

class Action {
public:
    const static int WAIT   = 0;
    const static int MOVETO = 1;
    
    Action();
    Action(Character*);
    Action(const Action& orig);
    virtual ~Action();
    
    void executeAction(long);

    void setOwner(Character* owner) {
        this->owner = owner;
    }

    Character* getOwner() const {
        return owner;
    }

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
    Character* owner;
};

#endif	/* ACTION_H */
