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

long Utils::mod(long a, long b){
    long rest = a % b;
    if (rest < 0){
        rest += b;
    }
    
    return rest;
}

double Utils::mod(double a, long b){
    long intA = (long)a;
    long rest = intA % b;
    if (rest < 0){
        rest += b;
    }
    
    return rest + (a - intA);
}

timespec Utils::timespecSubtract(timespec first, timespec second){
    
    struct timespec result;
    result.tv_sec = first.tv_sec - second.tv_sec;
    result.tv_nsec = first.tv_nsec - second.tv_nsec;
    
    if (result.tv_sec > 0){
        if (result.tv_nsec < 0){
            result.tv_sec--;
            result.tv_nsec += 1000000000;
        }
    }
    else{
        if (result.tv_sec < 0){
            if (result.tv_nsec > 0){
                result.tv_sec++;
                result.tv_nsec -= 1000000000;
            }
        }
    }
    
    return result;
}

timespec Utils::timespecSum(timespec first, timespec second){
    
    struct timespec result;
    result.tv_sec = first.tv_sec + second.tv_sec;
    result.tv_nsec = first.tv_nsec + second.tv_nsec;
    
    if (result.tv_sec > 0){
        if (result.tv_nsec < 0){
            result.tv_sec--;
            result.tv_nsec += 1000000000;
        }
        else if (result.tv_nsec >= 1000000000){
            result.tv_sec++;
            result.tv_nsec -= 1000000000;
        }
    }
    else if (result.tv_sec < 0){
        if (result.tv_nsec > 0){
            result.tv_sec++;
            result.tv_nsec -= 1000000000;
        }
        else if (result.tv_nsec <= -1000000000){
            result.tv_sec--;
            result.tv_nsec += 1000000000;
        }
    }
    else{
        if (result.tv_nsec >= 1000000000){
            result.tv_sec++;
            result.tv_nsec -= 1000000000;
        }
        else if (result.tv_nsec <= -1000000000){
            result.tv_sec--;
            result.tv_nsec += 1000000000;
        }
    }
    
    return result;
}

timespec Utils::convertNSecToTimespec(long timeNSec){
    struct timespec result;
    
    result.tv_sec  = (int)(timeNSec/1000000000);
    result.tv_nsec = timeNSec % 1000000000;
    
    return result;
}