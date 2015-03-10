/* 
 * File:   Movement.cpp
 * Author: skrep
 * 
 * Created on 23 de Fevereiro de 2015, 20:07
 */

#include "Movement.h"

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
    
    Facing* facing = new Facing(Utils::mod(facingAngleXY, 360), facingAngleZ);
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
    double angleXYStart = currentFacing->getFacingDirectionXY();
    double angleXYEnd = facingToMove->getFacingDirectionXY();
    double angleZStart = currentFacing->getFacingDirectionZ();
    double angleZEnd = facingToMove->getFacingDirectionZ();
    
    if (angleXYStart != angleXYEnd){
        double distanceRight = 0;
        double distanceLeft = 0;
        
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
    double degrees = this->calcTurningDegrees(time);
    double degreesXY = Facing::differenceOfAngleXY(currentFacing, facingToMove);
    double degreesZ = Facing::differenceOfAngleZ(currentFacing, facingToMove);
    
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
    double distanceToDestination = sqrt(pow((currentPosition->getX() - this->destination->getX()), 2) + 
                                        pow((currentPosition->getY() - this->destination->getY()), 2) + 
                                        pow((currentPosition->getZ() - this->destination->getZ()), 2));
    
    
    
    double distanceMoved = this->calcDistanceMoved(isRunning, time);
    
    if (MPIGameConfig::DEBUG_MOVEMENT){
        std::cout << "    distanceToDestination: " << distanceToDestination << "\n";
        std::cout << "    distanceMoved: " << distanceMoved << "\n";
        std::cout << "}\n";
    }
    
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

double Movement::calcTurningDegrees(long time){
    return MPIGameConfig::SLOW_TURN_SPEED * time / Utils::NANOSECOND;
}

double Movement::calcDistanceMoved(bool isRunning, long time){
    if (isRunning){
        return MPIGameConfig::RUN_SPEED * time / Utils::NANOSECOND;
    }
    return MPIGameConfig::WALK_SPEED * time / Utils::NANOSECOND;
}
