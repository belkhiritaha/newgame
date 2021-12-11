#include "map.h"

void initMap(int map[][MAP_SIZE_Y]){
    int i;
    int j;
    for (i=0; i<MAP_SIZE_X; ++i){
        for (j=0; j<MAP_SIZE_Y; ++j){
            map[i][j] = 0;
        }
    }
    for (j=0; j<MAP_SIZE_Y; ++j){
        for (i = MAP_SIZE_Y/2; i > 0; i--)
        {
            map[j][i] = 1;
        }
        
    }
}
