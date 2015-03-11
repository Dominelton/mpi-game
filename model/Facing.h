/* 
 * File:   Facing.h
 * Author: skrep
 *
 * Created on 24 de Fevereiro de 2015, 19:19
 */

#ifndef FACING_H
#define	FACING_H

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

class Facing {
public:
    Facing();
    Facing(double, double);
    Facing(const Facing& orig);
    virtual ~Facing();
    
    void setFacingDirectionZ(double facingDirectionZ) {
        this->facingDirectionZ = facingDirectionZ;
    }

    double getFacingDirectionZ() const {
        return facingDirectionZ;
    }
    
    void setFacingDirectionXY(double facingDirectionXY) {
        this->facingDirectionXY = facingDirectionXY;
    }

    double getFacingDirectionXY() const {
        return facingDirectionXY;
    }
    
    static double differenceOfAngleXY(Facing*, Facing*);
    static double differenceOfAngleZ(Facing*, Facing*);
    
    void serialize(rapidjson::Writer<rapidjson::StringBuffer>&);    
    void deserialize(rapidjson::Value&);
    
private:
    double facingDirectionXY;
    double facingDirectionZ;
};

#endif	/* FACING_H */

