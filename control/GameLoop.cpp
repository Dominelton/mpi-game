/* 
 * File:   gameLoop.cpp
 * Author: wander
 * 
 * Created on September 25, 2014, 3:27 PM
 */

#include "GameLoop.h"
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>

GameLoop::GameLoop() {
}

GameLoop::GameLoop(const GameLoop& orig) {
}

GameLoop::~GameLoop() {
}

void GameLoop::doLoop() {
    int n = 1;
    
    std::ofstream dataFile;
    dataFile.open( "../dataFile.txt" );
    // Outputs to example.txt through a_file
    
    while (n < 100){
    
        startLoop = clock();
        // Aqui teremos a logica de loop
        //Creates an instance of ofstream, and opens example.txt

        endLoop = clock();
        
        
        
        dataFile << "Loop :\n";

        dataFile << startLoop << "\n";

        // Close the file stream explicitly
        dataFile << endLoop << "\n";

        dataFile << CLOCKS_PER_SEC << "\n";
        
        n++;
    }
    
    dataFile.close();
    // Aqui gravaremos dados em arquivo para análise
}