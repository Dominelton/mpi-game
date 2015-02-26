/* 
 * File:   Character.cpp
 * Author: wander
 * 
 * Created on October 14, 2014, 3:07 PM
 */

#include "Character.h"

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
