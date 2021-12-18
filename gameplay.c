#include "gameplay.h"

void initPlayer(Player_t * pJoueur){
    pJoueur->x = 90;
    pJoueur->y = 8;
    pJoueur->isGrounded = 0;
    pJoueur->h = 2;
    pJoueur->w = 1;
    pJoueur->xSpeed = 0;
    pJoueur->ySpeed = 0;
}

int checkCollision(){
    float case_x = floorf(Joueur.x + Joueur.w - 1);
    float case_y = floorf(Joueur.y + Joueur.h);
    printf("positions : %f %f\n",Joueur.x, Joueur.y);
    printf("cases : %f %f %d\n", case_x, case_y, map[(int)case_y][(int)case_x]);
    //if (case_y >= 0 && case_y < NB_BLOCKS_Y && case_x >= 0 && case_x < NB_BLOCKS_X){
        if (map[(int)case_y][(int)case_x]){
            printf("collide\n");
            Joueur.isGrounded = 1;
            return 1;
        }
    //}
    return 0;
}

int playerMoveX(){
    //printf("pos : %f %f\n", Joueur.x, Joueur.y);
    if (Joueur.x + Joueur.w/2 >= MAP_SIZE_X || Joueur.x - Joueur.w/2 < 0){
        Joueur.xSpeed = 0;
        printf("bonk\n");
        //return 0;
    }
    else {
        (Joueur.xSpeed > 0) ? (Joueur.xSpeed -= GROUND_FRICTION * Joueur.xSpeed + GROUND_MVT/1.32) : (Joueur.xSpeed += GROUND_FRICTION * Joueur.xSpeed+ GROUND_MVT/1.32);

        Joueur.x += Joueur.xSpeed;
    }
    if (fabs(Joueur.xSpeed) < MAX_RUN_SPEED){
        Joueur.xSpeed += GROUND_MVT * (Keys[1] - Keys[3]);
    }
    return 1;
}

int playerMoveY(){
    if (checkCollision()){
        Joueur.ySpeed = -JUMP_SPEED * Keys[0];
    }
    if (fabs(Joueur.ySpeed) < MAX_Y_SPEED){
        Joueur.ySpeed += JUMP_SPEED * (Keys[2] - Keys[0]);
    }
    else {
        Joueur.ySpeed += GRAVITY;
    }
    Joueur.y += Joueur.ySpeed;
    return 1;
}

void playerFall(){

}

void gestPhysique(){
    int grounded = 0;
    playerMoveX();
    playerMoveY();
}

