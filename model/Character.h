/* 
 * File:   Character.h
 * Author: wander
 *
 * Created on October 14, 2014, 3:06 PM
 */

#ifndef PERSONAGEM_H
#define	PERSONAGEM_H

#include "Movement.h"

class Character {
public:
    Character();
    Character(int, Movement);
    Character(const Character& orig);
    virtual ~Character();
    void move();
    void stop();

    void setId(int id) {
        this->id = id;
    }

    int getId() const {
        return id;
    }

    void setSpeed(int speed) {
        this->speed = speed;
    }

    int getSpeed() const {
        return speed;
    }

    void setMovement(Movement movement) {
        this->movement = movement;
    }

    Movement getMovement() const {
        return movement;
    }
    
private:
    Movement movement;
    int speed;
    int id;
};

#endif	/* PERSONAGEM_H */

