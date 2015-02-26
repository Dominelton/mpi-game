/* 
 * File:   Action.cpp
 * Author: skrep
 * 
 * Created on 25 de Fevereiro de 2015, 19:37
 */

#include "Action.h"
#include <time.h>
#include <stdio.h>
#include <iostream>

Action::Action(){
}

Action::Action(Character* owner){
    this->owner = owner;
    this->actionType = Action::WAIT;
}

Action::Action(const Action& orig) {
}

Action::~Action() {
}

void Action::executeAction(long time){
    std::cout << "Previous time for Action from owner " << this->owner->getId() << ": " << time << "\n";
}

