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
    if(this->z){
        writer.String("z");
        writer.Double(this->z);
    }
    
    writer.EndObject();
}

void Position::deserialize(rapidjson::Value& valuePosition){
    
    for (rapidjson::Value::MemberIterator positionMember = valuePosition.MemberBegin(); positionMember != valuePosition.MemberEnd(); ++positionMember) {
        std::string x("x");
        std::string y("y");
        std::string z("z");
        std::string memberName(positionMember->name.GetString());
        
        if(memberName.compare(x)==0){
            this->x = (positionMember->value.GetDouble());
        }
        if(memberName.compare(y)==0){
            this->y = (positionMember->value.GetDouble());
        }
        if(memberName.compare(z)==0){
            this->z = (positionMember->value.GetDouble());
        }
    }
}
