/* 
 * File:   Character.h
 * Author: wander
 *
 * Created on October 14, 2014, 3:06 PM
 */

#ifndef PERSONAGEM_H
#define	PERSONAGEM_H
#include "Position.h"

class Character {
public:
    Character();
    Character(int, Position);
    Character(const Character& orig);
    virtual ~Character();
    void move();
    void stop();
    
    Position getPosition(){
        return position;
    }
    void setPosition(Position position){
        this->position = position;
    }
    int getSpeed(){
        return speed;
    }
    void setSpeed(int speed){
        this->speed = speed;
    }
    int getId(){
        return id;
    }
    void setId(int vId){
        id = vId;
    }
    
private:
    Position position;
    int speed;
    int id;
};

#endif	/* PERSONAGEM_H */

