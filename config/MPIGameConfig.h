/* 
 * File:   MPIGameConfig.h
 * Author: skrep
 *
 * Created on 3 de Março de 2015, 19:08
 */

#ifndef MPIGAMECONFIG_H
#define	MPIGAMECONFIG_H

class MPIGameConfig {
public:
    MPIGameConfig();
    MPIGameConfig(const MPIGameConfig& orig);
    virtual ~MPIGameConfig();
    
    const static int BATTLEFIELD_SIZE_X     = 50;
    const static int BATTLEFIELD_SIZE_Y     = 50;
    const static int NPC_COUNT              = 3;
    const static int RANDOM_WAIT_TIME_SEC   = 5;
    const static int MAX_UPS                = 50;
    const static int SYSTEM_RUNTIME_SEC     = 2;
    
    // Distribute parameters
    const static bool DISTRIBUTE_PROCESSING = true;
    
    const static bool DEBUG_CHARACTER_FULL  = false;
    const static bool DEBUG_MOVEMENT        = false;
    const static bool DEBUG_CLOCKS          = false;
    const static bool DEBUG_FILE_ENABLED    = false;
    
    /* Measured in Degrees per second */
    const static int SLOW_TURN_SPEED        = 180;
    const static int FAST_TURN_SPEED        = 360;
    /* Measured in Meters per second */
    const static double WALK_SPEED          = 1.5;
    const static double RUN_SPEED           = 5.0;
private:

};

#endif	/* MPIGAMECONFIG_H */
