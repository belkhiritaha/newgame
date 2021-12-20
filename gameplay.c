#include "gameplay.h"

int DrawJumpEffect = 0;

void initPlayer(Player_t * pJoueur){
    pJoueur->x = 87;
    pJoueur->y = 7;
    pJoueur->isGrounded = 0;
    pJoueur->h = 2;
    pJoueur->w = 1;
    pJoueur->xHitbox = 0.95;
    pJoueur->yHitbox = 1.9;
    pJoueur->xSpeed = 0;
    pJoueur->ySpeed = 0;
}

int checkCollisionY(){
    int case_x = floorf(Joueur.x + Joueur.xSpeed + Joueur.xHitbox - 0.5);//dont touch this
    int case_y = floorf(Joueur.y + Joueur.ySpeed + Joueur.yHitbox);
    int case_below = floorf(Joueur.y + Joueur.xHitbox + 2/16.0 - 1) + 1 +1;
    //printf("positions : %f %f\n",Joueur.x, Joueur.y);
    //printf("cases : %f %f %d\n", case_x, case_y, map[(int)case_y][(int)case_x]);
    //if (case_y >= 0 && case_y < NB_BLOCKS_Y && case_x >= 0 && case_x < NB_BLOCKS_X){
        if (map[case_y][case_x]){
            //printf("collide\n");
            Joueur.ySpeed = 0;
            Joueur.isGrounded = 1;
            return 1;
        }
        else {
            Joueur.isGrounded = 0;
        }
    //}
    return 0;
}

int checkCollisionX(float xSpeed){

    int case_right = ceilf(Joueur.x - 2/16.0);
    int case_left = floorf(Joueur.x + 2/16.0);
    int case_bot = floorf(Joueur.y + Joueur.xHitbox - 1) + 1;
    int case_top = case_bot - 1;
    int case_below = floorf(Joueur.y + Joueur.xHitbox + 2/16.0 - 1) + 1 +1;
    printf("left = %d , pos = %f, %f , right = %d, bot= %d top= %d\n", case_left, Joueur.x,Joueur.y, case_right, case_bot, case_top);
    //printf("DESTINATION: %f\n", Joueur.x + xSpeed);
    if (map[case_bot][case_right] || map[case_top][case_right]){
        if ( !Joueur.isGrounded && Joueur.y - (int)Joueur.y > 0.2 && map[case_below][case_right]){
            Joueur.xSpeed =  0;
        }
        else {
            Joueur.xSpeed = 0;
        }
        return 2;
    }
    if (map[case_bot][case_left] || map[case_top][case_left]){
        if ( !Joueur.isGrounded && Joueur.y - (int)Joueur.y > 0.2 && map[case_below][case_left]){
            Joueur.xSpeed = 0;
        }
        else {
            Joueur.xSpeed = 0;
        }
    }
    return 0;
}

int playerMoveX(){
    //printf("pos : %f %f\n", Joueur.x, Joueur.y);
    switch (checkCollisionX(Joueur.xSpeed))
    {
        case 0: //no sides collided
            if (fabs(Joueur.xSpeed) < MAX_RUN_SPEED){
                Joueur.xSpeed += GROUND_MVT * (Keys[1] - Keys[3]);
            }
            (Joueur.xSpeed > 0) ? (Joueur.xSpeed -= GROUND_MVT/1.32) : (Joueur.xSpeed += GROUND_MVT/1.32);

            Joueur.x += Joueur.xSpeed;
            break;
        
        case 2: //right side collided
            Joueur.xSpeed -= GROUND_MVT * Keys[3];
            Joueur.x += Joueur.xSpeed;
            break;

        case 1: //left side collided
            Joueur.xSpeed += GROUND_MVT * Keys[1];
            Joueur.x += Joueur.xSpeed;
            break;

        default:
            break;
    }

    return 1;
}

int playerMoveY(){
    //printf("ySpeed = %f\n", Joueur.ySpeed);
    if (checkCollisionY()){
        Joueur.ySpeed -= JUMP_SPEED * (Keys[0]);
        if (Keys[0]){
            DrawJumpEffect = 1;
        }
    }
    else{
        DrawJumpEffect = 0;
        Joueur.ySpeed += GRAVITY;
    }
    Joueur.y += Joueur.ySpeed;
    return 1;
}

void gestPhysique(){
    playerMoveX();
    playerMoveY();
}

