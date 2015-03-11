/* 
 * File:   Character.cpp
 * Author: wander
 * 
 * Created on October 14, 2014, 3:07 PM
 */

#include "Character.h"

Character::Character() {
}

Character::Character(int id, Position* currentPosition, Facing* currentFacing) {
    this->id = id;
    this->currentPosition = currentPosition;
    this->currentFacing = currentFacing;
    this->action = new Action();
}

Character::Character(const Character& orig) {
}

Character::~Character() {
}

void Character::executeAction(long time){
    if (MPIGameConfig::DEBUG_CHARACTER_FULL){
        std::cout << "NPC " << this->id << ":\n";
        std::cout << "{\n";
        std::cout << "    currentPosition:\n";
        std::cout << "    {\n";
        std::cout << "        x: " << this->currentPosition->getX() << "\n";
        std::cout << "        y: " << this->currentPosition->getY() << "\n";
        std::cout << "        z: " << this->currentPosition->getZ() << "\n";
        std::cout << "    }\n";
        std::cout << "    currentFacing:\n";
        std::cout << "    {\n";
        std::cout << "        facingDirectionXY: " << this->currentFacing->getFacingDirectionXY() << "\n";
        std::cout << "        facingDirectionZ: "  << this->currentFacing->getFacingDirectionZ()  << "\n";
        std::cout << "    }\n";
        std::cout << "    action:\n";
        std::cout << "    {\n";
        std::cout << "        actiongType: " << ((this->action->getActionType() == 0) ? "WAIT" : "MOVETO") << "\n";
        if (this->action->getActionType() == 0){
            std::cout << "        waitingTime: " << this->action->getWaitingTime() << "ms\n";
        }
        else{
            std::cout << "        movement:\n";
            std::cout << "        {\n";
            std::cout << "            destination:\n";
            std::cout << "            {\n";
            std::cout << "                x: " << this->action->getMovement()->getDestination()->getX() << "\n";
            std::cout << "                y: " << this->action->getMovement()->getDestination()->getY() << "\n";
            std::cout << "                z: " << this->action->getMovement()->getDestination()->getZ() << "\n";
            std::cout << "            }\n";
            std::cout << "        }\n";
        }
        std::cout << "    }\n";
        std::cout << "}\n";
    }
    
    if (MPIGameConfig::DEBUG_MOVEMENT){
        if (this->action->getActionType() == 1){
            std::cout << "NPC " << this->id << ":\n";
            std::cout << "{\n";
            std::cout << "    currentPosition:\n";
            std::cout << "    {\n";
            std::cout << "        x: " << this->currentPosition->getX() << "\n";
            std::cout << "        y: " << this->currentPosition->getY() << "\n";
            std::cout << "        z: " << this->currentPosition->getZ() << "\n";
            std::cout << "    }\n";
            std::cout << "    currentFacing:\n";
            std::cout << "    {\n";
            std::cout << "        facingDirectionXY: " << this->currentFacing->getFacingDirectionXY() << "\n";
            std::cout << "        facingDirectionZ: "  << this->currentFacing->getFacingDirectionZ()  << "\n";
            std::cout << "    }\n";
            std::cout << "    destination:\n";
            std::cout << "    {\n";
            std::cout << "        x: " << this->action->getMovement()->getDestination()->getX() << "\n";
            std::cout << "        y: " << this->action->getMovement()->getDestination()->getY() << "\n";
            std::cout << "        z: " << this->action->getMovement()->getDestination()->getZ() << "\n";
            std::cout << "    }\n";
        }
    }
    
    switch (this->action->getActionType()){
        case Action::WAIT: {
            this->processWaiting(time);
        }
            break;
        case Action::MOVETO: {
            this->processMoveTo(time);
        }
            break;
    }
}

void Character::processWaiting(long time){
    switch (this->action->getWaitingTime()){
        case -1: { }
            // Não faz nada, já que é um Wait sem tempo para acabar
            break;
        case 0: {
            std::cout << "NPC " << this->id << ": Start to move.\n";
            Position* destination = new Position();
            this->action->moveTo(destination);
        }
            break;
        default: {
            this->action->reduceWaitingTime(time);
        }
            break;
    }
}

void Character::processMoveTo(long time){
    if (this->action->getMovement()->getDestination()->equals(currentPosition)){
        std::cout << "NPC " << this->id << ": Start to wait.\n";
        this->action->waitRandomTime();
    }
    else{
        this->action->updatePositionAndFacing(this->currentPosition, this->currentFacing, time);
    }
}

void Character::serialize(rapidjson::Writer<rapidjson::StringBuffer>& writer){
    writer.StartObject();
    
    if(this->id >= 0){
        writer.String("id");
        writer.Int(this->id);
    }
    
    if(this->action){
        writer.String("action");
        this->action->serialize(writer);
    }
    
    if(this->currentFacing){
        writer.String("currentFacing");
        this->currentFacing->serialize(writer);
    }
    
    if(this->currentPosition){
        writer.String("currentPosition");
        this->currentPosition->serialize(writer);
    }
    
    writer.EndObject();
}

void Character::deserialize(rapidjson::Value& valueCharacter){
    if(valueCharacter.HasMember("id")){
        rapidjson::Value& valueId = valueCharacter["id"];
        this->id = valueId.GetInt();
    }
    
    if(valueCharacter.HasMember("action")){
        rapidjson::Value& valueAction = valueCharacter["action"];
        this->action = new Action();
        this->action->deserialize(valueAction);
    }
    
    if(valueCharacter.HasMember("currentFacing")){
        rapidjson::Value& valueFacing = valueCharacter["currentFacing"];
        this->currentFacing = new Facing();
        this->currentFacing->deserialize(valueFacing);
    }
    
    if(valueCharacter.HasMember("currentPosition")){
        rapidjson::Value& valuePosition = valueCharacter["currentPosition"];
        this->currentPosition = new Position();
        this->currentPosition->deserialize(valuePosition);
    }
    
}