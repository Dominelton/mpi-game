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
    Character(const Character& orig);
    virtual ~Character();
    void mover();
    void parar();
    
    Position getPosition(){
        return posicao;
    }
    void setPosition(Position posicao){
        this->posicao = posicao;
    }
    int getSpeed(){
        return speed;
    }
    void setSpeed(int speed){
        this->speed = speed;
    }
    
private:
    Position posicao;
    int speed;
};

#endif	/* PERSONAGEM_H */

