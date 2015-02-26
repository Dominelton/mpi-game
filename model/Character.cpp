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
        case Action::WAIT:
            this->processWaiting(time);
            break;
    }
    std::cout << "Previous time for Action from owner " << this->getId() << ": " << time << "\n";
}

void Character::processWaiting(long time){
    switch (this->action->getWaitingTime()){
        case 0:
            // Mudar a ação para Andar pra um lugar random
            break;
        case -1:
            // Faz porra nenhuma, já que o desgraçado vai ficar esperando vai saber até quando
            break;
        default:
            this->action->reduceWaitingTime(time);
            break;
    }
}