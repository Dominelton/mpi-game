/* 
 * File:   Position.cpp
 * Author: wander
 * 
 * Created on October 14, 2014, 3:08 PM
 */

#include "Position.h"

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

void Position::serialize(rapidjson::Writer<rapidjson::StringBuffer>& writer){
    writer.StartObject();
    
    if(this->x){
        writer.String("x");
        writer.Double(this->x);
    }
    if(this->y){
        writer.String("y");
        writer.Double(this->y);
    }
    if(this->z >= 0){
        writer.String("z");
        writer.Double(this->z);
    }
    
    writer.EndObject();
}

void Position::deserialize(rapidjson::Value& valuePosition){
    if (valuePosition.HasMember("x")){
        rapidjson::Value& valueX = valuePosition["x"];
        this->x = valueX.GetDouble();
    }
    if (valuePosition.HasMember("y")){
        rapidjson::Value& valueY = valuePosition["y"];
        this->y = valueY.GetDouble();
    }
    if (valuePosition.HasMember("z")){
        rapidjson::Value& valueZ = valuePosition["z"];
        this->z = valueZ.GetDouble();
    }
}
