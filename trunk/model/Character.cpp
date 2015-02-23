/* 
 * File:   Character.cpp
 * Author: wander
 * 
 * Created on October 14, 2014, 3:07 PM
 */

#include "Character.h"

Character::Character() {
}

Character::Character(int id, Position position) {
    this->id = id;
    this->position = position;
}

Character::Character(const Character& orig) {
}

Character::~Character() {
}
