/* 
 * File:   Facing.cpp
 * Author: skrep
 * 
 * Created on 24 de Fevereiro de 2015, 19:25
 */

#include "Facing.h"

Facing::Facing() {
}

Facing::Facing(int facingDirectionXY, int facingDirectionZ) {
    this->facingDirectionXY = facingDirectionXY;
    this->facingDirectionZ = facingDirectionZ;
}

Facing::Facing(const Facing& orig) {
}

Facing::~Facing() {
}

