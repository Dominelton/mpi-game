/* 
 * File:   Character.h
 * Author: wander
 *
 * Created on October 14, 2014, 3:06 PM
 */

#ifndef PERSONAGEM_H
#define	PERSONAGEM_H

#include "Movement.h"
#include "Position.h"
#include "Facing.h"
#include "Action.h"

class Character {
public:
    Character();
    Character(int, Position*, Facing*);
    Character(const Character& orig);
    virtual ~Character();
    
    void executeAction(long);
    
    void processWaiting(long);
    
    void processMoveTo(long);

    void setAction(Action* action) {
        this->action = action;
    }

    Action* getAction() const {
        return action;
    }
    
    void setCurrentFacing(Facing* currentFacing) {
        this->currentFacing = currentFacing;
    }

    Facing* getCurrentFacing() const {
        return currentFacing;
    }

    void setCurrentPosition(Position* currentPosition) {
        this->currentPosition = currentPosition;
    }

    Position* getCurrentPosition() const {
        return currentPosition;
    }

    void setId(int id) {
        this->id = id;
    }

    int getId() const {
        return id;
    }
    
private:
    int id;
    Position* currentPosition;
    Facing* currentFacing;
    Action* action;
};

#endif	/* PERSONAGEM_H */

