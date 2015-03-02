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
    
    static int differenceOfAngleXY(Facing*, Facing*);
    static int differenceOfAngleZ(Facing*, Facing*);
    
private:
    int facingDirectionXY;
    int facingDirectionZ;
};

#endif	/* FACING_H */

