#ifndef ENGINE_H
#define ENGINE_H
int getRandomInteger(int min, int max);


void printASCII(const char *end, const char *start);

char* animalStatHud(Animal animal);
char* generateStatBar(float stat,float maxStat,const char* title);
void makeWinWithText(WINDOW* win,char* text,int x, int y);
char* getASCII(const char *end, const char *start);

#endif
