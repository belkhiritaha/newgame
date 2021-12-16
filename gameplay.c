#include "gameplay.h"

void initPlayer(Player_t * pJoueur){
    pJoueur->x = 90;
    pJoueur->y = 0;
    pJoueur->isGrounded = 0;
    pJoueur->h = 2;
    pJoueur->w = 1;
}

int playerMoveX(){
    printf("%f %f\n", Joueur.xSpeed, Joueur.ySpeed);
    if (fabs(Joueur.xSpeed) < MAX_RUN_SPEED){
        Joueur.xSpeed += GROUND_MVT * (Keys[1] - Keys[3]);
    }
    if (Joueur.xSpeed == 0 || Joueur.x >= MAP_SIZE_X || Joueur.x < 0){
        return 0;
    }
    else {
        (Joueur.xSpeed > 0) ? (Joueur.xSpeed -= GROUND_FRICTION * Joueur.xSpeed + GROUND_MVT/3) : (Joueur.xSpeed += GROUND_FRICTION * Joueur.xSpeed+ GROUND_MVT/3);

        Joueur.x += Joueur.xSpeed;
    }
    return 1;
}

int playerMoveY(){
    if (fabs(Joueur.ySpeed) < MAX_Y_SPEED){
        Joueur.ySpeed -= JUMP_SPEED * Keys[0];
    }
    if (Joueur.ySpeed == 0){
        return 0;
    }
    else {
        (Joueur.ySpeed < 0) ? (Joueur.ySpeed -= AIR_FRICTION * Joueur.ySpeed - GRAVITY) : (Joueur.ySpeed += AIR_FRICTION * Joueur.ySpeed + GRAVITY);
    }
    return 1;
}


void checkCollision(float posX, float posY){

}

void playerFall(){

}

void gestPhysique(){
    int grounded = 0;
    playerMoveX();
    playerMoveY();
}

