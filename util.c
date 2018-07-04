/**
    @file util.c
    @author Ben Fisher

    Implementation file containing definitions for miscellaneous functions,
    such as generating random integers and delaying the program.
*/
#include "util.h"
int randInt(int min, int max){
    return rand() % (max - min) + min;
}

void delayMs(float delay) {
    clock_t start = clock();
    while ( 1000.0 * ((float) (clock() - start)) / CLOCKS_PER_SEC <= delay );
}