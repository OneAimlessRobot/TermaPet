
#include "../Includes/preprocessorStuff.h"
//Game* initGame(char*animalName){
//
//
//initscr();
//start_color();
//halfdelay(1);
//noecho();
//curs_set(0);
//
//initWindows(game);
//initBuffers(game);
//initAllColors();
//initMenus(game);
//
//showTitleScreen(game->needs[0],game->buffs[2],0,0);
//
// pthread_create(&game->biology,NULL,petLoop,(game->an));
// pthread_detach(game->biology);
// pthread_create(&game->alert,NULL,flashingDyingAlert,game->an);
// pthread_detach(game->alert);
//
//return game;
//
//
//}

void initMenus(Game*game){

char *cmdLabels[] = {
                        "Feed",
                        "Play",
                        "Quench",
                        "Heal",
                        "Poo/Pee",
                        "Rest",
                        "(un)Pause",
                        "Home",
                  };
char *homeLabels[] = {
                    "Commands",
                    "Stats",
                    "Pet",


                  };
char *goHomeLabels[] = {
                        "Go Home",
                  };

game->pMenus=malloc(sizeof(PackagedMenu)*NUM_OF_MODES);
game->menus=malloc(sizeof(MENU*)*NUM_OF_MODES);

int nCmd = ARRAY_SIZE(cmdLabels),
    nHome = ARRAY_SIZE(homeLabels),
    nGoHome = ARRAY_SIZE(goHomeLabels);

ITEM** cmdItems = (ITEM **)calloc(nCmd + 1, sizeof(ITEM *)),
        **homeItems = (ITEM **)calloc(nHome + 1, sizeof(ITEM *)),
        **goHomeItems = (ITEM **)calloc(nGoHome + 1, sizeof(ITEM *));


    initMenu(&game->pMenus[0],&game->menus[0],nHome,game->needs[2],homeFunc,homeLabels,homeItems);

    initMenu(&game->pMenus[1],&game->menus[1],nCmd,game->needs[2],cmdFunc,cmdLabels,cmdItems);

    initMenu(&game->pMenus[2],&game->menus[2],nGoHome,game->needs[13],goHomeFunc,goHomeLabels,goHomeItems);


    initMenu(&game->pMenus[3],&game->menus[3],nGoHome,game->needs[13],goHomeFunc,goHomeLabels,goHomeItems);







}

void initWindows(Game*game){




game->needs=malloc(sizeof(WINDOW*)*(NUM_OF_WINDOWS));

game->needs[0]=newwin(TITLEH,TITLEW,HUDX,HUDY);
game->needs[1]=newwin(STATSH,STATSW,STATSX,STATSY);
game->needs[2]=newwin(MENUH,MENUW,MENUX,MENUY);
game->needs[3]= newwin(PETH,PETW,PETX,PETY);

game->needs[4]=newwin(1,strlen("SLEEPING!"),WARNINGSX,WARNINGSY);
game->needs[5]=newwin(1,strlen("BORED!"),WARNINGSX+1,WARNINGSY);
game->needs[6]=newwin(1,strlen("HUNGRY!"),WARNINGSX+2,WARNINGSY);
game->needs[7]=newwin(1,strlen("THIRSTY!"),WARNINGSX+3,WARNINGSY);
game->needs[8]=newwin(1,strlen("TIRED!"),WARNINGSX+4,WARNINGSY);
game->needs[9]=newwin(1,strlen("POO!"),WARNINGSX+5,WARNINGSY);
game->needs[10]=newwin(1,strlen("PEE!"),WARNINGSX+6,WARNINGSY);

game->needs[11]=newwin(1,strlen("DIGESTING!"),WARNINGSX+7,WARNINGSY);
game->needs[12]=newwin(1,strlen("HYDRATING!"),WARNINGSX+8,WARNINGSY);


game->needs[13]= newwin(GOHOMEH,GOHOMEW,GOHOMEX,GOHOMEY);



}

void initBuffers(Game*game){

game->buffs= malloc(sizeof(char*)*NUM_OF_BUFFERS);

    game->buffs[0]=getASCII(_binary_dead_res_end,_binary_dead_res_start);
    game->buffs[1]=getASCII(_binary_pet_res_end,_binary_pet_res_start);
    game->buffs[2]=getASCII(_binary_title_res_end,_binary_title_res_start);
    game->buffs[3]=animalStatHud(*(game->an));
    game->buffs[4]=getASCII(_binary_pethurt_res_end,_binary_pethurt_res_start);
    game->buffs[5]=getASCII(_binary_petholding_res_end,_binary_petholding_res_start);
    game->buffs[6]=getASCII(_binary_petinpain_res_end,_binary_petinpain_res_start);
    game->buffs[7]=getASCII(_binary_pethappy_res_end,_binary_pethappy_res_start);



}

void initAllColors(){

 init_pair(30,COLOR_GREEN,COLOR_BLACK); //Title color
 init_pair(31,COLOR_WHITE,COLOR_BLACK); //default
 init_pair(32,COLOR_BLACK,COLOR_RED); //DEATH color
 init_pair(33,COLOR_RED,COLOR_BLACK);//commands highlight color

init_pair(1,COLOR_BLACK,COLOR_WHITE);//sleeping color //
init_pair(2,COLOR_WHITE,COLOR_RED);//hungry color //
init_pair(3,COLOR_WHITE,COLOR_CYAN);//thirsty color //
init_pair(4,COLOR_BLACK,COLOR_MAGENTA);//tired //
init_pair(5,COLOR_WHITE,COLOR_BLACK);//poo //
init_pair(6,COLOR_BLACK,COLOR_YELLOW);//pee //
init_pair(7,COLOR_BLACK,COLOR_BLACK);//neutral //
init_pair(8,COLOR_MAGENTA,COLOR_MAGENTA);//bored //
init_pair(9,COLOR_RED,COLOR_CYAN);//Pet color
init_pair(10,COLOR_GREEN,COLOR_WHITE);//digesting //
init_pair(11,COLOR_WHITE,COLOR_GREEN);//hydrating

}
void gameLoop(Game* game){



	while(game->online && !game->an->dead)
	{

        clearAll(game);
		refreshAll(game);
		doupdate();
		updateGraphics(game);
		refreshAll(game);
		        doupdate();

        input(game);
        postCurrMenu(game);

	}

    destroyGame(game);


}
void destroyGame(Game*game){



nocbreak();

if(game->online){
bkgd(COLOR_PAIR(32));
makeWinWithText(stdscr,game->buffs[0],0,0);
refresh();
getch();
}
erase();
refresh();
bkgd(COLOR_PAIR(31));
makeWinWithText(stdscr,"Adeus! Espero que se lembrem de fazer com que isto grave no futuro!\n",0,0);
refresh();
getch();

killAllWindows(game);
killAllBuffs(game);
killMenus(game);
destroyAnimal(game->an);
endwin();


}
void input(Game*game){

    int slot=game->mode;
    int c=(int) wgetch(menu_win(game->menus[slot]));
        switch(c)
	    {	case KEY_DOWN:
		        menu_driver((game->menus[slot]), REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver((game->menus[slot]), REQ_UP_ITEM);
				break;
			case 10:
			{	ITEM *cur;
				void (*p)(Game*,int);
				cur = current_item(game->menus[slot]);
				p = item_userptr(cur);
				p(game,item_index(cur));
				pos_menu_cursor(game->menus[slot]);
				break;
			}
			case 'q':
			{
                game->online=0;
                break;
			}
            default:
                break;
		}

}


void cmdFunc(Game*game,int option){
    beep();
    if(option < 6){
    if(!(game->paused)){
    petCare(game->an,option);
    }
    }
    else if(option==6){

        if(game->paused){
            game->paused=0;
        }
        else{
            game->paused=1;
        }
    }
    else if(option==7){

        game->mode=0;

    }

}

void homeFunc(Game*game,int option){

game->mode=option+1;


}


void goHomeFunc(Game*game,int option){

    game->mode=0;


}
void updateGraphics(Game* game){

enum modes currMode;

currMode=game->mode;
switch(currMode){
case commands:


    displayHud(game);
break;
case stats:

    statsGraphics(game);

break;

case pet:

    petGraphics(game);

break;
default:
break;



}

}


void postCurrMenu(Game*game){

    for(int i=0;i<NUM_OF_MODES-2;i++){
        if(i==game->mode){
            post_menu(game->menus[i]);
            }
        else{
            unpost_menu(game->menus[i]);
        }
        }




}


void petGraphics(Game* game){
if(game->paused){

    wbkgd(game->needs[3],COLOR_PAIR(31));
    makeWinWithText(game->needs[3],game->buffs[1],0,0);

 }
 else if(game->an->dying){
    wbkgd(game->needs[3],COLOR_PAIR(32));
    if(!(game->an->energy>0)){
    makeWinWithText(game->needs[3],game->buffs[1],0,0);
    }
    if(game->an->gotPee||game->an->gotPoo){
    makeWinWithText(game->needs[3],game->buffs[5],0,0);
    }
    else{

    makeWinWithText(game->needs[3],game->buffs[6],0,0);

    }
}
 else{
    wbkgd(game->needs[3],COLOR_PAIR(9));
    if(game->an->gotPee||game->an->gotPoo){
    makeWinWithText(game->needs[3],game->buffs[5],0,0);
    }
    else if(game->an->sleeping){
    makeWinWithText(game->needs[3],game->buffs[1],0,0);
    }
    else{
    makeWinWithText(game->needs[3],game->buffs[7],0,0);
    }


 }
}

void statsGraphics(Game* game){


 free(game->buffs[3]);
 game->buffs[3]=animalStatHud(*(game->an));
    wbkgd(game->needs[1],COLOR_PAIR(31));
 makeWinWithText(game->needs[1],game->buffs[3],0,0);
}
void displayHud(Game * game){
    if(!(game->an->boredom>0)){
    wbkgd(game->needs[5],COLOR_PAIR(8));
     makeWinWithText(game->needs[5],"BORED!\n",0,0);

    }
    else{

    wbkgd(game->needs[5],COLOR_PAIR(7));

     makeWinWithText(game->needs[5],"      \n",0,0);

    }


    if(!(game->an->hunger>0)){
    wbkgd(game->needs[6],COLOR_PAIR(2));
     makeWinWithText(game->needs[6],"HUNGRY!\n",0,0);

    }
    else{

    wbkgd(game->needs[6],COLOR_PAIR(7));
     makeWinWithText(game->needs[6],"       \n",0,0);


    }

    if(!(game->an->thirst>0)){
    wbkgd(game->needs[7],COLOR_PAIR(3));
     makeWinWithText(game->needs[7],"THIRSTY!\n",0,0);

    }
    else{

    wbkgd(game->needs[7],COLOR_PAIR(7));
     makeWinWithText(game->needs[7],"       \n",0,0);


    }

    if(!(game->an->energy>0)){
    wbkgd(game->needs[8],COLOR_PAIR(4));
     makeWinWithText(game->needs[8],"TIRED!\n",0,0);

    }
    else{

    wbkgd(game->needs[8],COLOR_PAIR(7));
     makeWinWithText(game->needs[8],"      \n",0,0);


    }

    if(game->an->gotPoo){
    wbkgd(game->needs[9],COLOR_PAIR(5));
     makeWinWithText(game->needs[9],"POO!\n",0,0);

    }
    else{
    wbkgd(game->needs[9],COLOR_PAIR(7));

     makeWinWithText(game->needs[9],"    \n",0,0);


    }
    if(game->an->gotPee){

    wbkgd(game->needs[10],COLOR_PAIR(6));
     makeWinWithText(game->needs[10],"PEE!\n",0,0);

    }
    else{

    wbkgd(game->needs[10],COLOR_PAIR(7));
     makeWinWithText(game->needs[10],"    \n",0,0);


    }
    if(game->an->sleeping){

    wbkgd(game->needs[4],COLOR_PAIR(1));
        makeWinWithText(game->needs[4],"SLEEPING!\n",0,0);

    }
    else{
    wbkgd(game->needs[4],COLOR_PAIR(7));

        makeWinWithText(game->needs[4],"         \n",0,0);


    }
    if(game->an->digesting){

    wbkgd(game->needs[11],COLOR_PAIR(10));
        makeWinWithText(game->needs[11],"DIGESTING!\n",0,0);

    }
    else{
    wbkgd(game->needs[11],COLOR_PAIR(7));

        makeWinWithText(game->needs[11],"          \n",0,0);


    }
    if(game->an->hydrating){

    wbkgd(game->needs[12],COLOR_PAIR(11));
        makeWinWithText(game->needs[12],"HYDRATING\n",0,0);

    }
    else{
    wbkgd(game->needs[12],COLOR_PAIR(7));

        makeWinWithText(game->needs[12],"         \n",0,0);


    }

}

void flashingDyingAlert(Game* game){

    while(!game->an->dead){
        if(game->an->dying){

            usleep((int)(TICK_DURATION_MICROSECS*GAME_SMOOTHNESS_FACTOR));

            flash();
        }

    }



}
void clearAll(Game* game){

enum modes currMode;

currMode=game->mode;
switch(currMode){

case home:

for(int i=1;i<NUM_OF_WINDOWS-1;i++){
wbkgdset(game->needs[i],COLOR_PAIR(7));
if(i!=2){

    werase(game->needs[i]);
    wprintw(game->needs[i],"");
    touchwin(game->needs[i]);
}
}
break;

case commands:
for(int i=1;i<NUM_OF_WINDOWS-1;i++){
wbkgdset(game->needs[i],COLOR_PAIR(7));
if(i==1||i==3||i==11){

    werase(game->needs[i]);
    wprintw(game->needs[i],"");
    touchwin(game->needs[i]);
}
}


break;

case stats:

for(int i=2;i<NUM_OF_WINDOWS-1;i++){
wbkgdset(game->needs[i],COLOR_PAIR(7));

    werase(game->needs[i]);
    wprintw(game->needs[i],"");
    touchwin(game->needs[i]);

}

break;

case pet:
for(int i=1;i<NUM_OF_WINDOWS-1;i++){
wbkgdset(game->needs[i],COLOR_PAIR(7));
if(i!=3){

    werase(game->needs[i]);
    wprintw(game->needs[i],"");
    touchwin(game->needs[i]);

}
}
break;


default:
break;



}
}
void refreshAll(Game*game){


enum modes currMode;

currMode=game->mode;
switch(currMode){

case home:
wnoutrefresh(game->needs[2]);

break;

case commands:
wnoutrefresh(game->needs[2]);

for(int i=4;i<NUM_OF_WINDOWS-1;i++){

wnoutrefresh(game->needs[i]);

}


break;

case stats:
wnoutrefresh(game->needs[1]);


break;

case pet:
wnoutrefresh(game->needs[3]);


break;

default:
break;



}

}

void killMenus(Game*game){


for(int i=0;i<NUM_OF_DIFERENT_MENUS;i++){
destroyMenu(&game->pMenus[i]);
}

}
void killAllWindows(Game*game){


for(int i=0;i<NUM_OF_WINDOWS;i++){

    delwin(game->needs[i]);

}
free(game->needs);

}
void killAllBuffs(Game*game){

    for(int i=0;i<NUM_OF_BUFFERS;i++){

        free(game->buffs[i]);

    }
    free(game->buffs);

}

void petLoop(Game*game){

while(1){
    if(!(game->paused)){
        petDecayLoop(game->an);
        }
    }




}
