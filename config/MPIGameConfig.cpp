/* 
 * File:   MPIGameConfig.cpp
 * Author: skrep
 * 
 * Created on 3 de Março de 2015, 19:08
 */

#include "MPIGameConfig.h"

#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>
#include <cstdio>

namespace MPIGameConfig {
    int BATTLEFIELD_SIZE_X     = 50;
    int BATTLEFIELD_SIZE_Y     = 50;
    int NPC_COUNT              = 3;
    int RANDOM_WAIT_TIME_SEC   = 5;
    int MAX_UPS                = 50;
    int SYSTEM_RUNTIME_SEC     = 5;
    
    // Distribute parameters
    bool DISTRIBUTE_PROCESSING = false;
    
    bool DEBUG_CHARACTER_FULL  = false;
    bool DEBUG_MOVEMENT        = false;
    bool DEBUG_CLOCKS          = false;
    bool DEBUG_FILE_ENABLED    = false;
    
    bool COLLECT_DATA          = false;
    
    /* Measured in Degrees per second */
    int SLOW_TURN_SPEED        = 180;
    int FAST_TURN_SPEED        = 360;
    /* Measured in Meters per second */
    double WALK_SPEED          = 1.5;
    double RUN_SPEED           = 5.0;
}

bool MPIGameConfig::loadConfigFromFile(std::string filePath){
    std::ifstream configFile(filePath.c_str());
    
    std::map<std::string, int>    intMap;
    std::map<std::string, double> doubleMap;
    std::map<std::string, bool>   boolMap;
    
    std::string line = "";
    std::string property;
    std::string separator;
    bool boolValue;
    int intValue;
    double doubleValue;
    
    int lineLoop = 1;
    
    while (std::getline(configFile, line)) {
        
        lineLoop++;
        
        // Pula linha vazia
        if (!line.length()) continue;
        
        // Pula linhas comentadas ( com # ou ; )
        if (line[0] == '#') continue;
        if (line[0] == ';') continue;

        std::istringstream issInt (line);
        if ((issInt >> property >> separator >> intValue) && (separator == "=")) {
            intMap.insert(std::make_pair(property, intValue));
        }
        
        std::istringstream issDouble (line);
        if ((issDouble >> property >> separator >> doubleValue) && (separator == "=")) {
            doubleMap.insert(std::make_pair(property, doubleValue));
        }
        
        std::istringstream issBool (line);
        if ((issBool >> property >> separator >> boolValue) && (separator == "=")) {
            boolMap.insert(std::make_pair(property, boolValue));
        }
    }
    
    configFile.close();
    
    /*
    std::cout << "\nInt Map:\n";
    typedef std::map<std::string, int> ::const_iterator MapIterator;
    for (MapIterator iter = intMap.begin(); iter != intMap.end(); iter++)
    {
        std::cout << "Key: " << iter->first << " - " << "Values: " << iter->second << "\n";
    }
    
    std::cout << "\nDouble Map:\n";
    typedef std::map<std::string, double> ::const_iterator MapIterator2;
    for (MapIterator2 iter2 = doubleMap.begin(); iter2 != doubleMap.end(); iter2++)
    {
        std::cout << "Key: " << iter2->first << " - " << "Values: " << iter2->second << "\n";
    }
    
    std::cout << "\nBool Map:\n";
    typedef std::map<std::string, bool> ::const_iterator MapIterator3;
    for (MapIterator3 iter3 = boolMap.begin(); iter3 != boolMap.end(); iter3++)
    {
        std::cout << "Key: " << iter3->first << " - " << "Values: " << iter3->second << "\n";
    }
    */
    return loadProperties(intMap, doubleMap, boolMap);
}

bool MPIGameConfig::loadProperties(std::map<std::string, int> intMap, std::map<std::string, double> doubleMap, std::map<std::string, bool> boolMap){
    MPIGameConfig::BATTLEFIELD_SIZE_X    = intMap.at("BATTLEFIELD_SIZE_X");
    MPIGameConfig::BATTLEFIELD_SIZE_Y    = intMap.at("BATTLEFIELD_SIZE_Y");
    MPIGameConfig::NPC_COUNT             = intMap.at("NPC_COUNT");
    MPIGameConfig::RANDOM_WAIT_TIME_SEC  = intMap.at("RANDOM_WAIT_TIME_SEC");
    MPIGameConfig::MAX_UPS               = intMap.at("MAX_UPS");
    MPIGameConfig::SYSTEM_RUNTIME_SEC    = intMap.at("SYSTEM_RUNTIME_SEC");
    
    // Distribute parameters
    MPIGameConfig::DISTRIBUTE_PROCESSING = boolMap.at("DISTRIBUTE_PROCESSING");
    
    // Debug
    MPIGameConfig::DEBUG_CHARACTER_FULL  = boolMap.at("DEBUG_CHARACTER_FULL");
    MPIGameConfig::DEBUG_MOVEMENT        = boolMap.at("DEBUG_MOVEMENT");
    MPIGameConfig::DEBUG_CLOCKS          = boolMap.at("DEBUG_CLOCKS");
    MPIGameConfig::DEBUG_FILE_ENABLED    = boolMap.at("DEBUG_FILE_ENABLED");
    
    MPIGameConfig::COLLECT_DATA          = boolMap.at("COLLECT_DATA");
    
    /* Measured in Degrees per second */
    MPIGameConfig::SLOW_TURN_SPEED       = intMap.at("SLOW_TURN_SPEED");
    MPIGameConfig::FAST_TURN_SPEED       = intMap.at("FAST_TURN_SPEED");
    /* Measured in Meters per second */
    MPIGameConfig::WALK_SPEED            = doubleMap.at("WALK_SPEED");
    MPIGameConfig::RUN_SPEED             = doubleMap.at("RUN_SPEED");
    
    return true;
}