/* 
 * File:   Player.h
 * Author: wander
 *
 * Created on October 14, 2014, 3:07 PM
 */

#ifndef PLAYER_H
#define	PLAYER_H
#include "Personagem.h"

class Player : public Personagem {
public:
    Player();
    Player(const Player& orig);
    virtual ~Player();
private:

};

#endif	/* PLAYER_H */

