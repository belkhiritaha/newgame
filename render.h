#ifndef RENDER_HEADER_
#define RENDER_HEADER_

#include <SDL2/SDL_ttf.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "map.h"
#include "main.h"
#include "gest_event.h"

#define WINDOW_H 800
#define WINDOW_W 1000


int BouclePrincipale();
void afficher(SDL_Renderer *, SDL_Rect , SDL_Texture *, SDL_Texture *, SDL_Texture *);
void create_Win();
void end_sdl(char ok, char const * msg);


extern int TailleEcranLong;
extern int TailleEcranHaut;

SDL_Renderer * renderer;



#endif /* RENDER_HEADER_ */
