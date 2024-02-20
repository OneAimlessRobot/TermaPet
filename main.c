#include "Includes/preprocessorStuff.h"

int main(int argc, char** argv){

char* name=malloc(1024);
memset(name,0,1024);

if(argc<2){

    strcpy(name,"Francisco");


}
else{


    strcpy(name,argv[1]);


}

Game game;
game.an=malloc(sizeof(Animal));

game.mode=0;
game.paused=0;
game.online=1;
int baseStat=840;
spawnAnimal(game.an,baseStat,baseStat,baseStat,baseStat,baseStat*4,name);

game.buffs= malloc(sizeof(char*)*NUM_OF_BUFFERS);
game.needs=malloc(sizeof(WINDOW*)*(NUM_OF_WINDOWS));

game.pMenus=malloc(sizeof(PackagedMenu)*NUM_OF_MODES);
game.menus=malloc(sizeof(MENU*)*NUM_OF_MODES);

initscr();
start_color();
halfdelay(1);
noecho();
curs_set(0);

initWindows(&game);
initBuffers(&game);
initMenus(&game);
initAllColors();


showTitleScreen(game.needs[0],game.buffs[2],0,0);

 pthread_create(&game.biology,NULL,petLoop,(&game));
 pthread_detach(game.biology);
 pthread_create(&game.alert,NULL,flashingDyingAlert,&(game));
 pthread_detach(game.alert);

    gameLoop(&game);

return 0;
}
