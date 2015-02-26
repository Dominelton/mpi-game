/* 
 * File:   Character.h
 * Author: wander
 *
 * Created on October 14, 2014, 3:06 PM
 */

#ifndef PERSONAGEM_H
#define	PERSONAGEM_H

#include "Movement.h"
#include "Action.h"
#include "Position.h"
#include "Facing.h"

class Character {
public:
    Character();
    Character(int, Position*, Facing*);
    Character(const Character& orig);
    virtual ~Character();

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

    void setAction(Action* action) {
        this->action = action;
    }

    Action* getAction() const {
        return action;
    }

    void setId(int id) {
        this->id = id;
    }

    int getId() const {
        return id;
    }
    
private:
    int id;
    Action* action;
    Position* currentPosition;
    Facing* currentFacing;
};

#endif	/* PERSONAGEM_H */

