#include "map.h"
#include <stdio.h>
void initMap(int map[][MAP_SIZE_X]){
    int i;
    int j;
    for (i=0; i<MAP_SIZE_Y; ++i){
        for (j=0; j<MAP_SIZE_X; ++j){
            map[i][j] = 0;
        }
    }
    for (i=MAP_SIZE_Y/2; i < MAP_SIZE_Y; ++i){
        for (j= 0; j < MAP_SIZE_X; ++j){
            map[i][j] = 1;
        }
    }
}
