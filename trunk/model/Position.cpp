/* 
 * File:   Position.cpp
 * Author: wander
 * 
 * Created on October 14, 2014, 3:08 PM
 */

#include "Position.h"
#include "MPIGameConfig.h"

Position::Position() {
    this->x = rand() % MPIGameConfig::BATTLEFIELD_SIZE_X;
    this->y = rand() % MPIGameConfig::BATTLEFIELD_SIZE_Y;
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

