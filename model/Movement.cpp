/* 
 * File:   Movement.cpp
 * Author: skrep
 * 
 * Created on 23 de Fevereiro de 2015, 20:07
 */

#include "Movement.h"
#include "Utils.h"
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <fstream>

Movement::Movement() {
}

Movement::Movement(Position* destination) {
    this->destination = destination;
    
    this->currentState = Movement::NOT_MOVING;
}

Movement::Movement(const Movement& orig) {
}

Movement::~Movement() {
}

void Movement::updatePositionAndFacing(Position*& currentPosition, Facing*& currentFacing, long time){
    Facing* facingToMove = calcFacingToMove(currentPosition);
    
    this->updateCurrentState(currentFacing, facingToMove);
    
    this->executeMovement(currentPosition, currentFacing, facingToMove, time);
}

Facing* Movement::calcFacingToMove(Position* currentPosition){
    double deltaX = this->destination->getX() - currentPosition->getX();
    double deltaY = this->destination->getY() - currentPosition->getY();
    double deltaZ = this->destination->getZ() - currentPosition->getZ();
    
    double facingAngleXY = atan2(deltaY, deltaX) * 180 / M_PI;

    double dist=sqrt(pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2));
    double dist2=sqrt(pow(deltaX, 2) + pow(deltaY, 2));
    
    double facingAngleZ = 0;
    if (dist != 0 || dist2 != 0){
        facingAngleZ = acos(dist2/dist) * 180 / M_PI;
    }
    
    Facing* facing = new Facing(Utils::mod((int)round(facingAngleXY),360), (int)round(facingAngleZ));
    return facing;
}

void Movement::updateCurrentState(Facing* currentFacing, Facing* facingToMove){
    
    bool needToTurn = (currentFacing->getFacingDirectionXY() != facingToMove->getFacingDirectionXY() ||
                       currentFacing->getFacingDirectionZ() != facingToMove->getFacingDirectionZ());
    
    if (needToTurn) {
        this->currentState = calculateTurnDirection(currentFacing, facingToMove);
    }
    else{
        this->currentState = Movement::RUNNING;
    }
}

int Movement::calculateTurnDirection(Facing* currentFacing, Facing* facingToMove){
    int angleXYStart = currentFacing->getFacingDirectionXY();
    int angleXYEnd = facingToMove->getFacingDirectionXY();
    int angleZStart = currentFacing->getFacingDirectionZ();
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

void Movement::executeMovement(Position*& currentPosition, Facing*& currentFacing, Facing* facingToMove, long time){
    switch(this->currentState){
        case Movement::NOT_MOVING:{
            return;
        }
            break;
        case Movement::WALKING:{
            this->move(currentPosition, false, time);
        }
            break;
        case Movement::RUNNING:{
            this->move(currentPosition, true, time);
        }
            break;
        case Movement::TURNING_LEFT:
        case Movement::TURNING_RIGHT:
        case Movement::TURNING_UP:
        case Movement::TURNING_DOWN:{
            this->turn(currentFacing, facingToMove, time);
        }
    }
}

void Movement::turn(Facing*& currentFacing, Facing* facingToMove, long time){
    int degrees = this->calcTurningDegrees(time);
    int degreesXY = Facing::differenceOfAngleXY(currentFacing, facingToMove);
    int degreesZ = Facing::differenceOfAngleZ(currentFacing, facingToMove);
    
    switch(this->currentState){
        case Movement::TURNING_RIGHT:{
            if (degreesXY > degrees){
                currentFacing->setFacingDirectionXY(Utils::mod((currentFacing->getFacingDirectionXY() - degrees),360));
            }
            else{
                currentFacing->setFacingDirectionXY(facingToMove->getFacingDirectionXY());
            }
        }
            break;
        case Movement::TURNING_LEFT:{
            if (degreesXY > degrees){
                currentFacing->setFacingDirectionXY(Utils::mod((currentFacing->getFacingDirectionXY() + degrees), 360));
            }
            else{
                currentFacing->setFacingDirectionXY(facingToMove->getFacingDirectionXY());
            }
        }
            break;
        case Movement::TURNING_UP:{
            if (degreesZ > degrees){
                currentFacing->setFacingDirectionZ(currentFacing->getFacingDirectionZ() + degrees);
            }
            else{
                currentFacing->setFacingDirectionZ(facingToMove->getFacingDirectionZ());
            }
        }
            break;
        case Movement::TURNING_DOWN:{
            if (degreesZ > degrees){
                currentFacing->setFacingDirectionZ(currentFacing->getFacingDirectionZ() - degrees);
            }
            else{
                currentFacing->setFacingDirectionZ(facingToMove->getFacingDirectionZ());
            }
        }
            break;
    }
}

void Movement::move(Position*& currentPosition, bool isRunning, long time){
    double distanceToDestination = sqrt(pow((currentPosition->getX() + this->destination->getX()), 2) + 
                                        pow((currentPosition->getY() + this->destination->getY()), 2) + 
                                        pow((currentPosition->getZ() + this->destination->getZ()), 2));
    
    double distanceMoved = this->calcDistanceMoved(isRunning, time);
    
    if (distanceToDestination < distanceMoved){
        currentPosition = this->destination;
    }
    else{
        double distanceDivisor = distanceMoved / distanceToDestination;
        
        currentPosition->setX(currentPosition->getX() + (this->destination->getX() - currentPosition->getX()) * distanceDivisor);
        currentPosition->setY(currentPosition->getY() + (this->destination->getY() - currentPosition->getY()) * distanceDivisor);
        currentPosition->setZ(currentPosition->getZ() + (this->destination->getZ() - currentPosition->getZ()) * distanceDivisor);
    }
}

int Movement::calcTurningDegrees(long time){
    return (int)(Movement::TURN_SPEED * time / 1000);
}

double Movement::calcDistanceMoved(bool isRunning, long time){
    if (isRunning){
        return Movement::RUN_SPEED * time / 1000;
    }
    return Movement::WALK_SPEED * time / 1000;
}
