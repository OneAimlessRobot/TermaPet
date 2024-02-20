#ifndef AUX_H
#define AUX_H

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define NUM_OF_BUFFERS 8
#define NUM_OF_WINDOWS 14
#define NUM_OF_DIFERENT_MENUS 3
#define NUM_OF_MODES 4

int getRandomInteger(int min, int max);

void incAndTruncateNum(float* var,int sign,float value,float inc);

void incAndTruncateInt(int* var,int sign,int value,int inc);

void multNumByFactor(float* var,int sign,float fact);

void multIntByFactor(int* var,int sign,int fact);

int min(int num1, int num2);

typedef struct PackagedMenu{

MENU* menu;
void* funcPtr;
int nRows;
char**labelArr;

}PackagedMenu;

#endif
