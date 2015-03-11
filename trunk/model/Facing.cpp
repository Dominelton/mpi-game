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

void Facing::serialize(rapidjson::Writer<rapidjson::StringBuffer>& writer){
    writer.StartObject();
    
    if(this->facingDirectionXY){
        writer.String("facingDirectionXY");
        writer.Double(this->facingDirectionXY);
    }
    if(this->facingDirectionZ >= -90 && this->facingDirectionZ <= 90){
        writer.String("facingDirectionZ");
        writer.Double(this->facingDirectionZ);
    }
        
    writer.EndObject();
}

void Facing::deserialize(rapidjson::Value& valueFacing){
    if (valueFacing.HasMember("facingDirectionZ")){
        rapidjson::Value& valuefacingDirectionZ = valueFacing["facingDirectionZ"];
        this->facingDirectionZ = valuefacingDirectionZ.GetDouble();
    }
    
    if (valueFacing.HasMember("facingDirectionXY")){
        rapidjson::Value& valuefacingDirectionXY = valueFacing["facingDirectionXY"];
        this->facingDirectionXY = valuefacingDirectionXY.GetDouble();
    }
}