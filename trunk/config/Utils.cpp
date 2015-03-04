/* 
 * File:   Utils.cpp
 * Author: skrep
 * 
 * Created on 2 de Março de 2015, 16:13
 */

#include "Utils.h"

Utils::Utils() {
}

Utils::Utils(const Utils& orig) {
}

Utils::~Utils() {
}

long long int Utils::mod(long long int a, long long int b){
    long long int rest = a % b;
    if (rest < 0){
        rest += b;
    }
    
    return rest;
}

