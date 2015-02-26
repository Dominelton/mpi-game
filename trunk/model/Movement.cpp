/* 
 * File:   Movement.cpp
 * Author: skrep
 * 
 * Created on 23 de Fevereiro de 2015, 20:07
 */

#include "Movement.h"
#include <cmath>

Movement::Movement() {
}

Movement::Movement(Position* targetPosition) {
    this->targetPosition = targetPosition;
    
    this->currentState = Movement::NOT_MOVING;
}

Movement::Movement(const Movement& orig) {
}

Movement::~Movement() {
}

/*void Movement::moveTo(Position* end){
    this->end = end;
    Facing* facingToMove = calcFacingToMove();
    
    bool needToTurn = (this->facing->getFacingDirectionXY() != facingToMove->getFacingDirectionXY() ||
                       this->facing->getFacingDirectionZ() != facingToMove->getFacingDirectionZ());
    
    if (needToTurn) {
        int turningDirection = calculateTurnDirection(facingToMove);
        turn(turningDirection);
    }
    else{
        // Aqui ele vai andar/correr
    }
}

Facing* Movement::calcFacingToMove(){
    double deltaX = this->end->getX() - this->start->getX();
    double deltaY = this->end->getY() - this->start->getY();
    double deltaZ = this->end->getZ() - this->start->getZ();
    
    double facingAngleXY = atan2(deltaY, deltaX) * 180 / M_PI;
    
    double dist=sqrt(pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2));
    double dist2=sqrt(pow(deltaX, 2) + pow(deltaZ, 2));
    
    double facingAngleZ = acos(dist2/dist) * 180 / M_PI;
    
    Facing* facing = new Facing((int)round(facingAngleXY), (int)round(facingAngleZ));
    return facing;
}

int Movement::calculateTurnDirection(Facing* facingToMove){
    int angleXYStart = this->facing->getFacingDirectionXY();
    int angleXYEnd = facingToMove->getFacingDirectionXY();
    int angleZStart = this->facing->getFacingDirectionZ();
    int angleZEnd = facingToMove->getFacingDirectionZ();
    
    if (angleXYStart != angleXYEnd){
        int distanceRight = 0;
        int distanceLeft = 0;
        
        if (angleXYStart > angleXYEnd){
            distanceRight = angleXYStart - angleXYEnd;
            distanceLeft  = angleXYEnd - angleXYStart + 360;
        }
        else{
            distanceRight = angleXYStart - angleXYEnd + 360;
            distanceLeft  = angleXYEnd - angleXYStart;
        }
        
        if (distanceRight < distanceLeft){
            return Movement::TURNING_RIGHT;
        }
        return Movement::TURNING_LEFT;
    }
    else{
        if (angleZStart < angleZEnd){
            return Movement::TURNING_UP;
        }
        return Movement::TURNING_DOWN;
    }
}

void Movement::move(int typeOfMove){
    this->moving = typeOfMove;
    switch(typeOfMove){
        case Movement::NOT_MOVING:
            return;
        case Movement::WALKING:
            // implementacao
            break;
        case Movement::RUNNING:
            // implementacao
            break;
    }
}

void Movement::turn(int typeOfTurn){
    this->turning = typeOfTurn;
    switch(typeOfTurn){
        case Movement::NOT_TURNING:
            return;
        case Movement::TURNING_RIGHT:
            //Verificar Tratamento facing < 0  ou >180
            this->facing->setFacingDirectionXY((this->facing->getFacingDirectionXY()-this->turnSpeed) % 360);
            break;
        case Movement::TURNING_LEFT:
            //Verificar Tratamento facing < 0  ou >180
            this->facing->setFacingDirectionXY((this->facing->getFacingDirectionXY()+this->turnSpeed) % 360);
            break;
        case Movement::TURNING_UP:
            //Verificar Tratamento facing < 0  ou >180
            if (this->facing->getFacingDirectionZ()+this->turnSpeed > 90){
                this->facing->setFacingDirectionZ(90);
            }
            else{
                this->facing->setFacingDirectionZ(this->facing->getFacingDirectionZ()+this->turnSpeed);
            }
            break;
        case Movement::TURNING_DOWN:
            //Verificar Tratamento facing < 0  ou >180
            if (this->facing->getFacingDirectionZ()-this->turnSpeed < -90){
                this->facing->setFacingDirectionZ(-90);
            }
            else{
                this->facing->setFacingDirectionZ(this->facing->getFacingDirectionZ()-this->turnSpeed);
            }
            break;
    }
}*/