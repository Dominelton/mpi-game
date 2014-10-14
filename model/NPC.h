/* 
 * File:   NPC.h
 * Author: wander
 *
 * Created on October 14, 2014, 3:07 PM
 */

#ifndef NPC_H
#define	NPC_H
#include "Character.h"

class NPC : public Character {
public:
    NPC();
    NPC(const NPC& orig);
    virtual ~NPC();
private:

};

#endif	/* NPC_H */

