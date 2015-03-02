/* 
 * File:   Action.cpp
 * Author: skrep
 * 
 * Created on 25 de Fevereiro de 2015, 19:37
 */

#include "Action.h"
#include <time.h>
#include <stdlib.h>

Action::Action(){
    this->actionType = Action::WAIT;
    this->waitingTime = rand() % 1000;
}

Action::Action(long waitingTime){
    this->actionType = Action::WAIT;
    this->waitingTime = waitingTime;
}

Action::Action(const Action& orig) {
}

Action::~Action() {
}

void Action::waitRandomTime(){
    this->actionType = Action::WAIT;
    this->waitingTime = rand() % 1000;
}

void Action::reduceWaitingTime(long time){
    if (this->waitingTime <= time){
        this->waitingTime = 0;
    }
    else{
        this->waitingTime -= time;
    }
}

void Action::moveTo(Position* destination){
    this->actionType = Action::MOVETO;
    this->movement = new Movement(destination);
}

void Action::updatePositionAndFacing(Position *&currentPosition, Facing *&currentFacing, long time){
    this->movement->updatePositionAndFacing(currentPosition, currentFacing, time);
}