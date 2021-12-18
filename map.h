#ifndef MAP_HEADER_
#define MAP_HEADER_

#define NB_BLOCKS_X 10
#define NB_BLOCKS_Y 10

#define MAP_SIZE_X 100
#define MAP_SIZE_Y 20

#include "main.h"

extern int map[MAP_SIZE_Y][MAP_SIZE_X];

void initMap();
void printMap();



#endif /* MAP_HEADER_ */
