/* 
 * File:   Facing.h
 * Author: skrep
 *
 * Created on 24 de Fevereiro de 2015, 19:19
 */

#ifndef FACING_H
#define	FACING_H

class Facing {
public:
    Facing();
    Facing(int, int);
    Facing(const Facing& orig);
    virtual ~Facing();
    
    void setFacingDirectionZ(int facingDirectionZ) {
        this->facingDirectionZ = facingDirectionZ;
    }

    int getFacingDirectionZ() const {
        return facingDirectionZ;
    }
    
    void setFacingDirectionXY(int facingDirectionXY) {
        this->facingDirectionXY = facingDirectionXY;
    }

    int getFacingDirectionXY() const {
        return facingDirectionXY;
    }
private:
    int facingDirectionXY;
    int facingDirectionZ;
};

#endif	/* FACING_H */

