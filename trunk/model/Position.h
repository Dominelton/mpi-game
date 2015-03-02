/* 
 * File:   Position.h
 * Author: wander
 *
 * Created on October 14, 2014, 3:08 PM
 */

#ifndef POSICAO_H
#define	POSICAO_H

#include <stdlib.h>

class Position {
public:
    Position();
    Position(int, int, int);
    Position(const Position& orig);
    virtual ~Position();

    void setZ(int z) {
        this->z = z;
    }

    int getZ() const {
        return z;
    }

    void setY(int y) {
        this->y = y;
    }

    int getY() const {
        return y;
    }

    void setX(int x) {
        this->x = x;
    }

    int getX() const {
        return x;
    }
private:
    int x;
    int y;
    int z;
};

#endif	/* POSICAO_H */

