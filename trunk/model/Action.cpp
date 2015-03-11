/* 
 * File:   Action.cpp
 * Author: skrep
 * 
 * Created on 25 de Fevereiro de 2015, 19:37
 */

#include "Action.h"

Action::Action(){
    this->waitRandomTime();
}

Action::Action(long waitingTimeNSec){
    this->actionType = Action::WAIT;
    this->waitingTime = waitingTimeNSec;
}

Action::Action(const Action& orig) {
}

Action::~Action() {
}

void Action::waitRandomTime(){
    this->actionType = Action::WAIT;
    this->waitingTime = rand() % (MPIGameConfig::RANDOM_WAIT_TIME_SEC * Utils::NANOSECOND);
}

void Action::reduceWaitingTime(long time){
    if (this->waitingTime < time){
        this->waitingTime = 0;
    }
    else{
        this->waitingTime -= time;
    }
}

void Action::moveTo(Position* destination){
    this->actionType = Action::MOVETO;
    this->movement = new Movement(destination);
}

void Action::updatePositionAndFacing(Position *&currentPosition, Facing *&currentFacing, long time){
    this->movement->updatePositionAndFacing(currentPosition, currentFacing, time);
}

void Action::serialize(rapidjson::Writer<rapidjson::StringBuffer>& writer){
    writer.StartObject();
    
    if(this->actionType){
        writer.String("actionType");
        writer.Int(this->actionType);
    }
    if(this->waitingTime){
        writer.String("waitingTime");
        writer.Int64(this->waitingTime);
    }
    
    if(this->movement){
        writer.String("movement");
        this->movement->serialize(writer);
    }
    
    writer.EndObject();
}

void Action::deserialize(rapidjson::Value& valueAction){
    for (rapidjson::Value::MemberIterator actionMember = valueAction.MemberBegin(); actionMember != valueAction.MemberEnd(); ++actionMember) {
        std::string memberName(actionMember->name.GetString());
        std::string actionType("actionType");
        std::string waitingTime("waitingTime");
        std::string movement("movement");
        if(memberName.compare(actionType)==0){
            this->actionType = (actionMember->value.GetInt());
        }
        if(memberName.compare(waitingTime)==0){
            this->waitingTime = (actionMember->value.GetInt64());
        }
        if(memberName.compare(movement)==0){
            this->movement = new Movement();
            this->movement->deserialize(actionMember->value); 
        }
    }
}