/* 
 * File:   Movement.h
 * Author: skrep
 *
 * Created on 23 de Fevereiro de 2015, 20:07
 */

#ifndef MOVEMENT_H
#define	MOVEMENT_H

#include "Position.h"
#include "Facing.h"
#include "../config/Utils.h"
#include "../config/MPIGameConfig.h"

#include <stdio.h>

#include <cmath>
#include <iostream>
#include <fstream>

#include "../include/rapidjson/document.h"
#include "../include/rapidjson/writer.h"
#include "../include/rapidjson/stringbuffer.h"

class Movement {
public:
    const static int NOT_MOVING    = 0;
    const static int WALKING       = 1;
    const static int RUNNING       = 2;
    const static int TURNING_RIGHT = 3;
    const static int TURNING_LEFT  = 4;
    const static int TURNING_UP    = 5;
    const static int TURNING_DOWN  = 6;
    
    Movement();
    Movement(Position*);
    Movement(const Movement& orig);
    virtual ~Movement();
    
    void updatePositionAndFacing(Position*&, Facing*&, long);
    void serialize(rapidjson::Writer<rapidjson::StringBuffer>&);    
    void deserialize(rapidjson::Value&);
    
    void setDestination(Position* destination) {
        this->destination = destination;
    }

    Position* getDestination() {
        return destination;
    }

    void setCurrentState(int currentState) {
        this->currentState = currentState;
    }

    int getCurrentState() const {
        return this->currentState;
    }
    
private:
    Position* destination;
    
    int currentState;
    
    Facing* calcFacingToMove(Position*);
    void updateCurrentState(Facing*, Facing*);
    int calculateTurnDirection(Facing*, Facing*);
    void executeMovement(Position*&, Facing*&, Facing*, long);
    
    double calcTurningDegrees(long);
    double calcDistanceMoved(bool, long);
    
    void turn(Facing*&, Facing*, long);
    void move(Position*&, bool, long);
    
    bool isFacingTargetPosition(Facing*);
    bool hasArrivedTargetPosition(Position*);
};

#endif	/* MOVEMENT_H */

