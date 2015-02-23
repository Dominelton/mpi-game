/* 
 * File:   Position.h
 * Author: wander
 *
 * Created on October 14, 2014, 3:08 PM
 */

#ifndef POSICAO_H
#define	POSICAO_H

class Position {
public:
    Position();
    Position(int, int, int);
    Position(const Position& orig);
    virtual ~Position();
    int getX(){
        return x;
    }
    void setX(int x){
        this->x = x;
    }
    int getY(){
        return y;
    }
    void setY(int y){
        this->y = y;
    }
    int getZ(){
        return z;
    }
    void setZ(int z){
        this->z = z;
    }
private:
    int x;
    int y;
    int z;
};

#endif	/* POSICAO_H */

