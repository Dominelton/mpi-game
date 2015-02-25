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

class Movement {
public:
    const static int NOT_MOVING = 0;
    const static int WALKING    = 1;
    const static int RUNNING    = 2;
    
    const static int NOT_TURNING   = 100;
    const static int TURNING_RIGHT = 101;
    const static int TURNING_LEFT  = 102;
    const static int TURNING_UP    = 103;
    const static int TURNING_DOWN  = 104;
    
    Movement();
    Movement(Position*);
    Movement(const Movement& orig);
    virtual ~Movement();
    void moveTo(Position*);
    void move(double, int);
    
    void setTurnSpeed(double turnSpeed) {
        this->turnSpeed = turnSpeed;
    }

    double getTurnSpeed() const {
        return turnSpeed;
    }
    
    void setSpeed(double speed) {
        this->speed = speed;
    }

    double getSpeed() const {
        return speed;
    }
    
    void setFacing(Facing* facing) {
        this->facing = facing;
    }

    Facing* getFacing() const {
        return facing;
    }

    void setEnd(Position* end) {
        this->end = end;
    }

    Position* getEnd() {
        return end;
    }

    void setStart(Position* start) {
        this->start = start;
    }

    Position* getStart() {
        return start;
    }
private:
    Position* start;
    Position* end;
    Facing* facing;
    
    int moving;
    double speed;
    
    int turning;
    double turnSpeed;
    
    Facing* calcFacingToMove();
    int calculateTurnDirection(Facing*);
    void move(int);
    void turn(int);
};

#endif	/* MOVEMENT_H */

