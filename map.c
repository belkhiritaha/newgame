#include "map.h"
#include <stdio.h>

int map[MAP_SIZE_Y][MAP_SIZE_X];

void initMap(){
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
    map[0][99] = 1;
    map[1][99] = 1;
    map[2][99] = 1;
    map[3][99] = 1;
    map[4][99] = 1;

    map[9][90] = 1;
    map[0][90] = 1;
    map[1][90] = 1;
    map[2][90] = 1;
    map[3][90] = 1;

    map[9][85] = 1;
    map[8][84] = 1;
    map[7][83] = 1;
    map[8][82] = 1;
    map[9][81] = 1;

    map[9][78] = 1;
    map[5][78] = 1;
}

void printMap(){
    int i;
    int j;
    int case_x = (int)Joueur.x;
    int case_y = (int)Joueur.y;
    printf("%d %d\n", case_x, case_y);
    for (i=0; i<MAP_SIZE_Y; ++i){
        for (j=0; j<MAP_SIZE_X; ++j){
            if ( i == case_y && j == case_x){
                printf("2");
            }
            else{
                printf("%d", map[i][j]);
            }
        }
        printf("\n");
    }
}