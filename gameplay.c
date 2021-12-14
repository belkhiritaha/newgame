#include "gameplay.h"

void initPlayer(Player_t * pJoueur){
    pJoueur->x = 0;
    pJoueur->y = 5;
    pJoueur->isGrounded = 0;
    pJoueur->h = 2;
    pJoueur->w = 1;
}

