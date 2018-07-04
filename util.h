/**
    @file util.h
    @author Ben Fisher

    Header file containing declarations for miscellaneous functions,
    such as generating random integers and delaying the program.
*/
#include <stdlib.h>
#include <time.h>

#ifndef UTIL
#define UTIL

/**
    Generates a random integer between min and max.

    @param min the min random number
    @param max the max random number
    
    @return random number between min and max
*/
int randInt(int min, int max);

/**
    Delays the program for the given amount of milliseconds.

    @param delay the time the program should be delayed for
*/
void delayMs(float delay);

#endif /* UTIL */