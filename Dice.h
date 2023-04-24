#pragma once
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
class Dice{
public:
    Dice(){
        /* initialize random seed: */
        srand (time(NULL));
    }
    int roll(int max=6, int min=1){
        return rand() % max + min;
    }
};