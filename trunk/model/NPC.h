/* 
 * File:   NPC.h
 * Author: wander
 *
 * Created on October 14, 2014, 3:07 PM
 */

#ifndef NPC_H
#define	NPC_H
#include "Personagem.h"

class NPC : public Personagem {
public:
    NPC();
    NPC(const NPC& orig);
    virtual ~NPC();
private:

};

#endif	/* NPC_H */

