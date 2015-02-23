/* 
 * File:   Position.cpp
 * Author: wander
 * 
 * Created on October 14, 2014, 3:08 PM
 */

#include "Position.h"

Position::Position() {
}

Position::Position(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Position::Position(const Position& orig) {
}

Position::~Position() {
}

