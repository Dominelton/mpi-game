/* 
 * File:   Movement.cpp
 * Author: skrep
 * 
 * Created on 23 de Fevereiro de 2015, 20:07
 */

#include "Movement.h"

Movement::Movement() {
}

Movement::Movement(Position* start) {
    this->start = start;
}

Movement::Movement(const Movement& orig) {
}

Movement::~Movement() {
}