/* 
 * File:   Position.cpp
 * Author: wander
 * 
 * Created on October 14, 2014, 3:08 PM
 */

#include "Position.h"

Position::Position() {
    this->x = rand() % 1000;
    this->y = rand() % 1000;
    this->z = 0;
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

