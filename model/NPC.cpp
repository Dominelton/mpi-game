/* 
 * File:   NPC.cpp
 * Author: wander
 * 
 * Created on October 14, 2014, 3:07 PM
 */

#include "NPC.h"

NPC::NPC(int id, Position* currentPosition, Facing* currentFacing):Character(id, currentPosition, currentFacing) {
}

NPC::NPC() {
}

NPC::NPC(const NPC& orig) {
}

NPC::~NPC() {
}

