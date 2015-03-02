/* 
 * File:   Character.cpp
 * Author: wander
 * 
 * Created on October 14, 2014, 3:07 PM
 */

#include "Character.h"
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

Character::Character() {
}

Character::Character(int id, Position* currentPosition, Facing* currentFacing) {
    this->id = id;
    this->currentPosition = currentPosition;
    this->currentFacing = currentFacing;
    this->action = new Action();
}

Character::Character(const Character& orig) {
}

Character::~Character() {
}

void Character::executeAction(long time){
    switch (this->action->getActionType()){
        case Action::WAIT: {
            this->processWaiting(time);
        }
            break;
        case Action::MOVETO: {
            this->processMoveTo(time);
        }
            break;
    }
}

void Character::processWaiting(long time){
    switch (this->action->getWaitingTime()){
        case -1: { }
            // Não faz nada, já que é um Wait sem tempo para acabar
            break;
        case 0: {
            std::cout << "NPC " << this->id << ": Start to move.\n";
            Position* destination = new Position();
            this->action->moveTo(destination);
        }
            break;
        default: {
            this->action->reduceWaitingTime(time);
        }
            break;
    }
}

void Character::processMoveTo(long time){
    if (this->action->getMovement()->getDestination()->equals(currentPosition)){
        std::cout << "NPC " << this->id << ": Start to wait.\n";
        this->action->waitRandomTime();
    }
    else{
        this->action->updatePositionAndFacing(this->currentPosition, this->currentFacing, time);
    }
}