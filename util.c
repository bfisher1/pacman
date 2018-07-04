#include "util.h"
int randInt(int min, int max){
    return rand() % (max - min) + min;
}
