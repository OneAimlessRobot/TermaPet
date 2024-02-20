#ifndef PET_H
#define PET_H

#define GAME_SMOOTHNESS_FACTOR 20.0f

#define AGE_UNIT_DURATION_SECONDS 1
#define AGE_TICK_DURATION (AGE_UNIT_DURATION_SECONDS*1.0f*GAME_SMOOTHNESS_FACTOR)
#define TICK_DURATION_MICROSECS (1000000/GAME_SMOOTHNESS_FACTOR)

#define BASESTAT 840

#define LEVEL_UP_STAT_MULTIPLIER 1.5f

#define DYINGCOUNTERTHIRST ((int)(5*AGE_TICK_DURATION))
#define DYINGCOUNTERHUNGER ((int)(20*AGE_TICK_DURATION))
#define DYINGCOUNTERSLEEP ((int)(100*AGE_TICK_DURATION))
#define HOLDINGPEEDYINGCOUNTER ((int)(10*AGE_TICK_DURATION))
#define HOLDINGPOODYINGCOUNTER ((int)(40*AGE_TICK_DURATION))

#define PEE_TOLERANCE_COUNTER ((int)(10*AGE_TICK_DURATION))
#define POO_TOLERANCE_COUNTER ((int)(40*AGE_TICK_DURATION))

#define DIGESTIONCOUNTER ((int)(15*AGE_TICK_DURATION))
#define SLEEPCOUNTER ((int)(30*AGE_TICK_DURATION))
#define HYDRATIONCOUNTER ((int)(5*AGE_TICK_DURATION))



#define SLEEPING_ENERGY_SCORE (400.0f/AGE_TICK_DURATION)
#define SLEEPING_HUNGER_SCORE (10.0f/AGE_TICK_DURATION)
#define SLEEPING_THIRST_SCORE (10.0f/AGE_TICK_DURATION)


#define DIGESTION_HUNGER_SCORE (125.0f/AGE_TICK_DURATION)
#define DIGESTION_THIRST_SCORE (50.0f/AGE_TICK_DURATION)

#define HYDRATION_THIRST_SCORE (250.0f/AGE_TICK_DURATION)

//
//#define SLEEPING_ENERGY_SCORE 200.0f
//#define SLEEPING_HUNGER_SCORE 10.0f
//#define SLEEPING_THIRST_SCORE 10.0f
//
//
//#define DIGESTION_HUNGER_SCORE 30.0f
//#define DIGESTION_THIRST_SCORE 15.0f
//
//#define HYDRATION_THIRST_SCORE 60.0f
//


#define PLAY_BOREDOM_SCORE 100
#define PLAY_THIRST_SCORE 200
#define PLAY_HUNGER_SCORE 100
#define PLAY_XP_SCORE 100

#define TREATMENT_SCORE 30

#define HEALTHDECAY (6.0f/AGE_TICK_DURATION)
#define ENERGYDECAY (70.0f/AGE_TICK_DURATION)
#define THIRSTDECAY (50.0f/AGE_TICK_DURATION)
#define HUNGERDECAY (20.0f/AGE_TICK_DURATION)
#define BOREDOMDECAY (50.0f/AGE_TICK_DURATION)

//
//#define HEALTHDECAY 6.0f
//#define ENERGYDECAY 12.0f
//#define THIRSTDECAY 8.0f
//#define HUNGERDECAY 4.0f
//#define BOREDOMDECAY 10.0f



typedef struct Animal{

    char* name;
    float health,
        hunger,
        boredom,
        thirst,
        energy,
        xp,

        maxHealth,
        maxHunger,
        maxBoredom,
        maxThirst,
        maxXp,
        maxEnergy;

    int
        age,
        level,

        currAgeCounter,

        digestionCounter,
        digesting,

        sleepCounter,
        sleeping,

        hydrationCounter,
        hydrating,

        dyingCounter,
        dying,


        gotPee,
        peeToleranceCounter,
        holdingPee,
        gotPoo,
        pooToleranceCounter,
        holdingPoo,

        dead;



}Animal;

void destroyAnimal(Animal*an);

void petCare(Animal* an,int option);

void petDecayLoop(Animal* an);

void spawnAnimal(Animal* an,float health,float thirst,float boredom, float hunger, float energy,char* name);

void handleDigestion(Animal * an);

void handleLearning(Animal * an);

void play(Animal * an);

void handleSleeping(Animal * an);

void handleDying(Animal * an);

void handleHydration(Animal * an);

void handleExcretion(Animal *an);


void handleBodyFunctions(Animal * an);
#endif
