/* 
 * File:   Position.cpp
 * Author: wander
 * 
 * Created on October 14, 2014, 3:08 PM
 */

#include "Position.h"

Position::Position() {
    srand (time(NULL));
    this->x = rand() % 1000;
    this->y = rand() % 1000;
    this->z = 0;
}

Position::Position(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Position::Position(const Position& orig) {
}

Position::~Position() {
}

bool Position::equals(Position* compareTo){
    bool equals = false;
    
    if (this->getX() == compareTo->getX() &&
            this->getY() == compareTo->getY() &&
            this->getZ() == compareTo->getZ()){
        equals = true;
    }
    
    return equals;
}

