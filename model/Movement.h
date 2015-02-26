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
    const static int NOT_MOVING    = 0;
    const static int WALKING       = 1;
    const static int RUNNING       = 2;
    const static int TURNING_RIGHT = 3;
    const static int TURNING_LEFT  = 4;
    const static int TURNING_UP    = 5;
    const static int TURNING_DOWN  = 6;
    
    /* Measured in Degrees per second */
    const static int TURN_SPEED    = 180;
    /* Measured in meters per second */
    const static double WALK_SPEED = 1.5;
    const static double RUN_SPEED  = 5.0;
    
    Movement();
    Movement(Position*);
    Movement(const Movement& orig);
    virtual ~Movement();
    
    void moveTo(Position*);
    void move(double, int);

    void setTargetPosition(Position* targetPosition) {
        this->targetPosition = targetPosition;
    }

    Position* getTargetPosition() {
        return targetPosition;
    }
private:
    Position* targetPosition;
    
    int currentState;
    
    Facing* calcFacingToMove();
    int calculateTurnDirection(Facing*);
    void move(int);
    void turn(int);
    
    bool isFacingTargetPosition(Facing*);
    bool hasArrivedTargetPosition(Position*);
};

#endif	/* MOVEMENT_H */

