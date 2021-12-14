#include "gameplay.h"

void initPlayer(Player_t * pJoueur){
    pJoueur->x = 20;
    pJoueur->y = 0;
    pJoueur->isGrounded = 0;
    pJoueur->h = 2;
    pJoueur->w = 1;
}

