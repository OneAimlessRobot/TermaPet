#ifndef FACTORIZED_H
#define FACTORIZED_H

void showTitleScreen(WINDOW* logo,char* buff,int x,int y);
void initMenu(PackagedMenu* pMenu,MENU**menu,int nRows,WINDOW** win,void* func,char**labels,ITEM**items);

void destroyMenu(PackagedMenu*pMenu);

#endif





//
//char* makeNamedFormattedString(int size){
//
//
//char* buff=malloc(1000);
//memset(buff,0,1000);
//
// sprintf(buff,"vida maxima: %d\ntedio maximo:%d\nsede maxima:%d\nfome maxima:%d\nenergia maxima:%d\n",
//            an->maxHealth,
//            an->maxBoredom,
//            an->maxThirst,
//            an->maxHunger,
//            an->maxEnergy);
//
//return buff;
//
//}
