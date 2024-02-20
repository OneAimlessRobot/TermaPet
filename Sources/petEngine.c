#include <unistd.h>
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <menu.h>
#include "../Includes/auxFuncs.h"
#include "../Includes/petEngine.h"

void handleBodyFunctions(Animal * an){
if(!an->dying){
        if(an->sleeping){


        handleSleeping(an);

        }
        else{



            if(an->hydrating){
                handleHydration(an);
            }

            if(an->digesting){
                handleDigestion(an);

            }



        }


    if(an->gotPee||an->gotPoo){
        handleExcretion(an);

    }
    }
else{
    an->dyingCounter--;
    if(an->dyingCounter<=0){

        an->dead=1;
    }
}

    if(!(an->health>0)||!(an->energy>0)||!(an->thirst>0)||!(an->hunger>0)||!an->peeToleranceCounter||!an->pooToleranceCounter){
    if(!an->dying){

        an->dyingCounter=INT_MAX;
        an->dying=1;
    }
    handleDying(an);
    }

}

void handleDying(Animal * an){


    if(!(an->health>0)){

        an->dead=1;
        return;
    }
    if(!(an->energy>0)){

        an->dyingCounter=min(an->dyingCounter,DYINGCOUNTERSLEEP);

    }
    if(!(an->hunger>0)){
        an->dyingCounter=min(an->dyingCounter,DYINGCOUNTERHUNGER);


    }
    if(an->gotPoo){
        an->dyingCounter=min(an->dyingCounter,HOLDINGPOODYINGCOUNTER);

    }

    if(an->gotPee){

        an->dyingCounter=min(an->dyingCounter,HOLDINGPEEDYINGCOUNTER);

    }
    if(!(an->thirst>0)){

        an->dyingCounter=min(an->dyingCounter,DYINGCOUNTERTHIRST);


    }





}
void handleLearning(Animal * an){


    incAndTruncateNum(&an->xp,1,an->maxXp,PLAY_XP_SCORE);

    if(an->xp==an->maxXp){
        an->level++;

        multNumByFactor(&an->maxXp,1,LEVEL_UP_STAT_MULTIPLIER);

        multNumByFactor(&an->maxBoredom,1,LEVEL_UP_STAT_MULTIPLIER);

        multNumByFactor(&an->maxEnergy,1,LEVEL_UP_STAT_MULTIPLIER);

        multNumByFactor(&an->maxHealth,1,LEVEL_UP_STAT_MULTIPLIER);

        multNumByFactor(&an->maxHunger,1,LEVEL_UP_STAT_MULTIPLIER);

        multNumByFactor(&an->maxThirst,1,LEVEL_UP_STAT_MULTIPLIER);


    }




}
void handleExcretion(Animal *an){


if(an->gotPoo){

    incAndTruncateInt(&an->pooToleranceCounter,0,0,1);
}
if(an->gotPee){

    incAndTruncateInt(&an->peeToleranceCounter,0,0,1);


}
}
void handleSleeping(Animal * an){

    an->health+=HEALTHDECAY;
   an->thirst+=THIRSTDECAY;
   an->hunger+=HUNGERDECAY;
    an->energy+=SLEEPING_ENERGY_SCORE;
    an->sleepCounter--;
    if(an->energy>an->maxEnergy){

        an->energy=an->maxEnergy;
        an->sleepCounter=SLEEPCOUNTER;
        an->sleeping=0;

    }
    else if(an->sleepCounter==0){

    an->sleepCounter=SLEEPCOUNTER;
    an->sleeping=0;
    }


}

void play(Animal * an){


    incAndTruncateNum(&an->boredom,1,an->maxBoredom,PLAY_BOREDOM_SCORE);
    incAndTruncateNum(&an->energy,0,0,2*PLAY_BOREDOM_SCORE);
    incAndTruncateNum(&an->thirst,0,0,PLAY_THIRST_SCORE);
    incAndTruncateNum(&an->hunger,0,0,PLAY_HUNGER_SCORE);

    handleLearning(an);

}

void handleHydration(Animal * an){

    an->thirst+=HYDRATION_THIRST_SCORE;
    an->hydrationCounter--;
    if(an->thirst>=an->maxThirst){

        an->thirst=an->maxThirst;
        an->hydrationCounter=HYDRATIONCOUNTER;
        an->hydrating=0;
        an->gotPee=1;

    }
    else if(an->hydrationCounter==0){

        an->hydrationCounter=HYDRATIONCOUNTER;
        an->hydrating=0;
        an->gotPee=1;

    }
}


void handleDigestion(Animal * an){

    an->hunger+=DIGESTION_HUNGER_SCORE;
    incAndTruncateNum(&an->thirst,1,an->maxThirst,DIGESTION_THIRST_SCORE);
    an->digestionCounter--;
    if(an->hunger>=an->maxHunger){

        an->hunger=an->maxHunger;
        an->digestionCounter=DIGESTIONCOUNTER;
        an->gotPoo=1;
        an->digesting=0;
    an->pooToleranceCounter=POO_TOLERANCE_COUNTER;


    }
    else if(an->digestionCounter==0){

        an->digestionCounter=DIGESTIONCOUNTER;
        an->digesting=0;
        an->gotPoo=1;
    an->pooToleranceCounter=POO_TOLERANCE_COUNTER;


    }



}


void spawnAnimal(Animal * an,float health,float thirst,float boredom,float hunger, float energy,char* name){

an->health=an->maxHealth=health;
an->hunger=an->maxHunger=hunger;
an->thirst=an->maxThirst=thirst;
an->boredom=an->maxBoredom=boredom;
an->energy=an->maxEnergy=energy;
an->maxXp=BASESTAT;
an->sleepCounter=SLEEPCOUNTER;
an->digestionCounter=DIGESTIONCOUNTER;
an->hydrationCounter=HYDRATIONCOUNTER;

an->peeToleranceCounter=PEE_TOLERANCE_COUNTER;
an->pooToleranceCounter=POO_TOLERANCE_COUNTER;

an->dyingCounter=INT_MAX-1;

an->digesting=an->hydrating=an->dying=an->dead=an->gotPee=an->gotPoo=an->sleeping=an->xp=an->level=an->age=an->currAgeCounter=0;
an->name=name;

}

void petCare(Animal* an,int option){
    switch(option){

    case(0):
    if(!an->sleeping&&!an->gotPoo){
        an->digesting=1;
        an->dying=0;
        }
    break;
    case(1):
    if(!an->dying&&!an->sleeping){

            play(an);
    }
    break;
    case(2):
    if(!an->sleeping&&!an->gotPee){
    an->hydrating=1;

        an->dying=0;
        }
    break;
    case(3):
    if(!an->sleeping){
        incAndTruncateNum(&an->health,1,an->maxHealth,TREATMENT_SCORE);

        }
    break;
    case(4):
    if(an->gotPee){

        an->gotPee=0;
    an->peeToleranceCounter=PEE_TOLERANCE_COUNTER;
    }
    if(an->gotPoo){

        an->gotPoo=0;
    an->pooToleranceCounter=POO_TOLERANCE_COUNTER;
    }
        an->dying=0;
        an->sleeping=0;
    break;
    case(5):
    if(!an->sleeping){
        an->sleeping=1;
        an->digesting=0;
        an->hydrating=0;
        an->dying=0;
        }
    else{
        an->sleeping=0;
        }
    break;
    default:
    break;
    }
    }
void petDecayLoop(Animal* an){

    handleBodyFunctions(an);
    usleep((int)(TICK_DURATION_MICROSECS));
    incAndTruncateNum(&an->boredom,0,0,BOREDOMDECAY);
    incAndTruncateNum(&an->health,0,0,HEALTHDECAY);
    incAndTruncateNum(&an->hunger,0,0,HUNGERDECAY);
    incAndTruncateNum(&an->thirst,0,0,THIRSTDECAY);
    incAndTruncateNum(&an->energy,0,0,ENERGYDECAY);
    an->currAgeCounter++;
    if(an->currAgeCounter==(int)AGE_TICK_DURATION){

        an->age++;
        an->currAgeCounter=0;

    }
    }
void destroyAnimal(Animal*an){

    free(an->name);
    free(an);


}

