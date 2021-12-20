#ifndef GEST_HEADER_
#define GEST_HEADER_

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "render.h"
#include "main.h"
#define NB_KEYS 10

void * gestInput(SDL_Renderer * renderer);
void initKeys(int Keys[NB_KEYS]);
extern int Keys[NB_KEYS];
extern int JoueurAttack;


#endif /* GEST_HEADER_ */
