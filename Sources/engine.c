
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <menu.h>
#include "../Includes/auxFuncs.h"
#include "../Includes/graphicalDefines.h"
#include "../Includes/petEngine.h"
#include "../Includes/engine.h"

void printASCII(const char *end, const char *start)
{
    char buff[end-start+1];
    int i=0;
    for (; i < (end - start); i++)
    {

        buff[i]=start[i];
    }
    buff[i]='\0';
    mvprintw(0,0,buff);
}

char* getASCII(const char *end, const char *start)
{
    char* buff=malloc(end-start+1);
    int i=0;
    for (; i < (end - start); i++)
    {

        buff[i]=start[i];
    }
    buff[i]='\0';
    return buff;
}

void makeWinWithText(WINDOW* win,char* text,int x, int y){


    mvwprintw(win,x,y,text);


}


char* generateStatBar(float stat,float maxStat,const char* title){

    int i=0;
    int step= round(maxStat/STATBARSIZES);
    float cursor=0;
    char *bar=malloc(1128),value[100];
    sprintf(value," %.2f",stat);
    memcpy(bar+i,title,strlen(title));
    i+=strlen(title);
    memcpy(bar+i,value,strlen(value));
    i+=strlen(value);
    bar[i++]='\n';
    bar[i++]='[';
    for(;cursor<stat;cursor+=step,i++){
    bar[i]='|';


    }
    for(;cursor<maxStat;cursor+=step,i++){
    bar[i]=' ';


    }
    bar[i++]=']';
    bar[i++]='\n';
    bar[i++]='\0';
    return bar;

}
char* animalStatHud(Animal animal){

    char* health= generateStatBar(animal.health,animal.maxHealth,"hp:"),
    * boredom= generateStatBar(animal.boredom,animal.maxBoredom,"mood:"),
    * thirst= generateStatBar(animal.thirst,animal.maxThirst,"h20:"),
    * hunger= generateStatBar(animal.hunger,animal.maxHunger,"food:"),
    * energy= generateStatBar(animal.energy,animal.maxEnergy,"stm:"),
    * xp= generateStatBar(animal.xp,animal.maxXp,"XP:"),
    * age= malloc(1000),
    * level= malloc(1000);
 memset(age,0,1000);
 memset(level,0,1000);
 sprintf(age,"TEMPO:%d\n",animal.age);
 sprintf(level,"LEVEL:%d\n",animal.level);
    int totallen= strlen(health)+strlen(boredom)+strlen(xp)+strlen(thirst)+strlen(hunger)+strlen(age)+strlen(level)+1024;
    char* buff=malloc(totallen);
    memset(buff,0,totallen);
    sprintf(buff,"%s%s%s%s%s%s%s%s%s",health,boredom,thirst,hunger,energy,age,xp,level,animal.name);
    free(age);
    free(level);
    free(health);
    free(boredom);
    free(thirst);
    free(energy);
    free(hunger);
    free(xp);
    return buff;
}

