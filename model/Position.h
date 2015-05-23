/* 
 * File:   Position.h
 * Author: wander
 *
 * Created on October 14, 2014, 3:08 PM
 */

#ifndef POSICAO_H
#define	POSICAO_H

#include "../config/MPIGameConfig.h"

#include <stdlib.h>
#include <time.h>

#include "../include/rapidjson/document.h"
#include "../include/rapidjson/writer.h"
#include "../include/rapidjson/stringbuffer.h"


class Position {
public:
    Position();
    Position(double, double, double);
    Position(const Position& orig);
    virtual ~Position();
    
    bool equals(Position*);
    void serialize(rapidjson::Writer<rapidjson::StringBuffer>&);    
    void deserialize(rapidjson::Value&);
    
    void setZ(double z) {
        this->z = z;
    }

    double getZ() const {
        return z;
    }

    void setY(double y) {
        this->y = y;
    }

    double getY() const {
        return y;
    }

    void setX(double x) {
        this->x = x;
    }

    double getX() const {
        return x;
    }
private:
    double x;
    double y;
    double z;
};

#endif	/* POSICAO_H */

