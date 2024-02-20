#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <menu.h>
#include "../Includes/auxFuncs.h"
#include "../Includes/embeded.h"
#include "../Includes/petEngine.h"
#include "../Includes/graphicalDefines.h"
#include "../Includes/engine.h"
#include "../Includes/factorized.h"

void showTitleScreen(WINDOW* logo,char* buff,int x,int y){

    wbkgdset(logo,COLOR_PAIR(30));
    makeWinWithText(logo,buff,x,y);
    wrefresh(logo);
    usleep((int)(TICK_DURATION_MICROSECS*GAME_SMOOTHNESS_FACTOR)*3);
    werase(logo);
    wrefresh(logo);
    delwin(logo);


}

void initMenu(PackagedMenu*pMenu,MENU**menu,int nRows,WINDOW** win,void*func,char**labels,ITEM**items){

pMenu->funcPtr=func;
pMenu->nRows=nRows;

for(int i = 0; i < nRows; ++i)
	{
	items[i] = new_item(labels[i],labels[i]);
		/* Set the user pointer */
		set_item_userptr(items[i], func);
	}

items[nRows] = (ITEM *)NULL;

*menu = new_menu((ITEM **)items);

menu_opts_off(*menu, O_SHOWDESC);

keypad(win, TRUE);

set_menu_win(*menu,win);
set_menu_sub(*menu, derwin(win, SUBMENUH, SUBMENUW, SUBMENUX, SUBMENUY));

set_menu_mark(*menu,"");

pMenu->menu=*menu;
pMenu->labelArr=labels;


}


void destroyMenu(PackagedMenu*pMenu){

	unpost_menu(pMenu->menu);
	for(int i = 0; i < pMenu->nRows; ++i)
		free_item(menu_items(pMenu->menu)[i]);
	free_menu(pMenu->menu);



}
