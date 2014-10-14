/* 
 * File:   Player.h
 * Author: wander
 *
 * Created on October 14, 2014, 3:07 PM
 */

#ifndef PLAYER_H
#define	PLAYER_H
#include "Character.h"

class Player : public Character {
public:
    Player();
    Player(const Player& orig);
    virtual ~Player();
private:

};

#endif	/* PLAYER_H */

