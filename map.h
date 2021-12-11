#ifndef MAP_HEADER_
#define MAP_HEADER_

#define NB_BLOCKS_X 10
#define NB_BLOCKS_Y 10

#define MAP_SIZE_X 100
#define MAP_SIZE_Y 20


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "gest_event.h"
#include "map.h"


int map[MAP_SIZE_X][MAP_SIZE_Y];

void initMap(int tab[][MAP_SIZE_Y]);



#endif /* MAP_HEADER_ */
