/* 
 * File:   Movement.h
 * Author: skrep
 *
 * Created on 23 de Fevereiro de 2015, 20:07
 */

#ifndef MOVEMENT_H
#define	MOVEMENT_H

#include "Position.h"

class Movement {
public:
    /*const double SPEED_STOPPED  = 0.00;
    const double SPEED_WALKING  = 1.50;
    const double SPEED_RUNNING  = 5.00;
    const double MULT_BACKWARDS = 0.50;*/
    
    Movement();
    Movement(Position);
    Movement(const Movement& orig);
    virtual ~Movement();

    void setSpeed(double speed) {
        this->speed = speed;
    }

    double getSpeed() const {
        return speed;
    }

    void setDirecao(double direcao) {
        this->direcao = direcao;
    }

    double getDirecao() const {
        return direcao;
    }

    void setEnd(Position end) {
        this->end = end;
    }

    Position getEnd() const {
        return end;
    }

    void setStart(Position start) {
        this->start = start;
    }

    Position getStart() const {
        return start;
    }
private:
    Position start;
    Position end;
    double direcao;
    double speed;
};

#endif	/* MOVEMENT_H */

