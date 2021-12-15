#include "gameplay.h"

void initPlayer(Player_t * pJoueur){
    pJoueur->x = 90;
    pJoueur->y = 10;
    pJoueur->isGrounded = 0;
    pJoueur->h = 2;
    pJoueur->w = 1;
}

int playerMoveX(float xSpeed){
    if (xSpeed == 0){
        return 0;
    }
    else {
        int blockXmax = (int)(Joueur.x - Joueur.w/NB_BLOCKS_X);
        int blockXmin = (int)(Joueur.x + Joueur.w/NB_BLOCKS_Y);
        //printf("block min: %d block max: %d\n", blockXmin, blockXmax);
    }
    return 0;
}

void checkCollision(float posX, float posY){

}

void playerFall(){

}

void gestPhysique(){
    int grounded = 0;
    playerMoveX(Joueur.xSpeed);
}

