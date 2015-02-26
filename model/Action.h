/* 
 * File:   Action.h
 * Author: skrep
 *
 * Created on 25 de Fevereiro de 2015, 19:37
 */

#ifndef ACTION_H
#define	ACTION_H

#include "Movement.h"
#include "Character.h"

class Action {
public:
    const static int WAIT   = 0;
    const static int MOVETO = 1;
    
    Action();
    Action(const Action& orig);
    virtual ~Action();
    
    void executeAction(long);

private:
    int actionType;
    long waitingTime;
    Movement* movement;
    Character* owner;
};

#endif	/* ACTION_H */

