/* 
 * File:   MPIGameConfig.h
 * Author: skrep
 *
 * Created on 3 de Março de 2015, 19:08
 */

#ifndef MPIGAMECONFIG_H
#define	MPIGAMECONFIG_H

#include <fstream>
#include <map>
#include <string>
#include <sstream>

namespace MPIGameConfig {
    // General Parameters
    extern int BATTLEFIELD_SIZE_X;
    extern int BATTLEFIELD_SIZE_Y;
    extern int NPC_COUNT;
    extern int RANDOM_WAIT_TIME_SEC;
    extern int MAX_UPS;
    extern int SYSTEM_RUNTIME_SEC;
    
    // Distribute parameters
    extern bool DISTRIBUTE_PROCESSING;
    
    extern bool DEBUG_CHARACTER_FULL;
    extern bool DEBUG_MOVEMENT;
    extern bool DEBUG_CLOCKS;
    extern bool DEBUG_FILE_ENABLED;
    
    extern bool COLLECT_DATA;
    
    /* Measured in Degrees per second */
    extern int SLOW_TURN_SPEED;
    extern int FAST_TURN_SPEED;
    /* Measured in Meters per second */
    extern double WALK_SPEED;
    extern double RUN_SPEED;

    bool loadConfigFromFile(std::string);
    
    bool loadProperties(std::map<std::string, int>, std::map<std::string, double>, std::map<std::string, bool>);
};

#endif	/* MPIGAMECONFIG_H */
