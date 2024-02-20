#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

enum modes{home,commands,stats,pet,activities};

#include "graphicalDefines.h"
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <menu.h>
#include "embeded.h"
#include "auxFuncs.h"
#include "petEngine.h"
#include "engine.h"
#include "factorized.h" //Contains all global things (Including windows and color pairs)
#include "../game.h"

#endif
