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
            std::cout << "NPC " << id << " waiting for more " << this->action->getWaitingTime() << " milliseconds. Processing " << time << " milliseconds.\n";
            this->processWaiting(time);
        }
            break;
        case Action::MOVETO: {
            std::cout << "NPC " << id << " is moving.\n";
            std::cout << "Current Position -> X-axis: " << this->currentPosition->getX() << "; ";
            std::cout << "Y-axis: " << this->currentPosition->getY() << "; ";
            std::cout << "Z-axis: " << this->currentPosition->getZ() << "; \n";
            std::cout << "Destination Position -> X-axis: " << this->action->getMovement()->getDestination()->getX() << "; ";
            std::cout << "Y-axis: " << this->action->getMovement()->getDestination()->getY() << "; ";
            std::cout << "Z-axis: " << this->action->getMovement()->getDestination()->getZ() << "; \n";
            std::cout << "Current Facing -> XY-axis: " << this->currentFacing->getFacingDirectionXY() << "; ";
            std::cout << "Z-axis: " << this->currentFacing->getFacingDirectionZ() << "; \n";
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
    if (this->action->getMovement()->getDestination() == currentPosition){
        //this->action->waitRandomTime();
    }
    else{
        this->action->updatePositionAndFacing(this->currentPosition, this->currentFacing, time);
    }
}