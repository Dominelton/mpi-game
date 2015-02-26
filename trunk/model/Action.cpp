/* 
 * File:   Action.cpp
 * Author: skrep
 * 
 * Created on 25 de Fevereiro de 2015, 19:37
 */

#include "Action.h"
#include <time.h>

Action::Action(){
    this->actionType = Action::WAIT;
}

Action::Action(const Action& orig) {
}

Action::~Action() {
}

void Action::executeAction(long){
    
}

