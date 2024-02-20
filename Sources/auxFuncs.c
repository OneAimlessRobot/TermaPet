
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <menu.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include "../Includes/auxFuncs.h"
int getRandomInteger(int min, int max) {
    // Seed the random number generator with the current time.
    srand(time(NULL));

    // Generate a random number between 0 and RAND_MAX.
    int random = rand();

    // Scale the random number to fit within the specified range.
    int result = (random % (max - min + 1)) + min;

    return result;
}
void incAndTruncateNum(float* var,int sign,float value,float inc){

    if(sign){
        *var+=inc;
        if(*var>value){
            *var=value;
        return;

        }
    }
    if(!sign){

        *var-=inc;
        if(*var<value){
            *var=value;
        return;
        }

    }

}



void incAndTruncateInt(int* var,int sign,int value,int inc){

    if(sign){
        *var+=inc;
        if(*var>value){
            *var=value;
        return;

        }
    }
    if(!sign){

        *var-=inc;
        if(*var<value){
            *var=value;
        return;
        }

    }

}

int min(int num1, int num2)
{
    // using the conditional operator to calcualte the min
    return (num1 > num2) ? num2 : num1;
}



void multNumByFactor(float* var,int sign,float fact){


    if(sign){

        *var*=fact;


    }
    else{

        *var*=1/fact;

    }

}

void multIntByFactor(int* var,int sign,int fact){



    if(sign){

        *var*=fact;


    }
    else{
        float newFact=(float)fact;
        float newValue=(float)(*var);
        newValue*=1/newFact;
        *var=(int)newValue;

    }
}
