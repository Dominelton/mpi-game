/* 
 * File:   Facing.cpp
 * Author: skrep
 * 
 * Created on 24 de Fevereiro de 2015, 19:25
 */

#include "Facing.h"

Facing::Facing() {
}

Facing::Facing(double facingDirectionXY, double facingDirectionZ) {
    this->facingDirectionXY = facingDirectionXY;
    this->facingDirectionZ = facingDirectionZ;
}

Facing::Facing(const Facing& orig) {
}

Facing::~Facing() {
}

double Facing::differenceOfAngleXY(Facing* start, Facing* end){
    double angleXYStart = start->getFacingDirectionXY();
    double angleXYEnd   = end->getFacingDirectionXY();
    
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
            return distanceRight;
        }
        return distanceLeft;
    }
}

double Facing::differenceOfAngleZ(Facing* start, Facing* end){
    if (start->getFacingDirectionZ() < end->getFacingDirectionZ()){
        return end->getFacingDirectionZ() - start->getFacingDirectionZ();
    }
    return start->getFacingDirectionZ() - end->getFacingDirectionZ();
}