#include "gameplay.h"

void initPlayer(Player_t * pJoueur){
    pJoueur->x = 87;
    pJoueur->y = 7;
    pJoueur->isGrounded = 0;
    pJoueur->h = 2;
    pJoueur->w = 1;
    pJoueur->xSpeed = 0;
    pJoueur->ySpeed = 0;
}

int checkCollisionY(){
    int case_x1;
    if (Joueur.x - (int)Joueur.x < 0.5){
        case_x1 = floorf(Joueur.x + Joueur.w + Joueur.ySpeed) - 1;
    }
    else {
        case_x1 = floorf(Joueur.x + Joueur.w + Joueur.ySpeed );
    }
    int case_y = floorf(Joueur.y + Joueur.h + Joueur.ySpeed );
    int case_ytop = case_y - Joueur.h;
    //printf("positions : %f %f\n",Joueur.x, Joueur.y);
    //printf("cases : %d %d %d\n", case_x1, case_y, map[case_y][case_x1]);
    //if (case_y >= 0 && case_y < NB_BLOCKS_Y && case_x >= 0 && case_x < NB_BLOCKS_X){
        if (map[case_y][case_x1]){
            //printf("collide\n");
            return 1;
        }
        else {
            if (map[case_ytop][case_x1]){
                Joueur.ySpeed = 0;
                return 2;
            }
            Joueur.isGrounded = 0;
        }
    //}
    return 0;
}

int checkCollisionX(float xSpeed){
    float case_right = ceilf(Joueur.x + Joueur.w - 1);
    float case_left = floorf(Joueur.x - Joueur.xSpeed);
    float case_bot = floorf(Joueur.y + Joueur.h - 1);
    float case_top = case_bot - 1;
    //printf("left = %f , pos = %f , right = %f, bot= %f\n", case_left, Joueur.x, case_right, case_bot);
    //printf("DESTINATION: %f\n", Joueur.x + xSpeed);
    if (map[(int)case_bot][(int)case_right] || map[(int)case_top][(int)case_right]){
        printf("right\n");
        return 2;
    }
    if (map[(int)case_bot][(int)case_left] || map[(int)case_top][(int)case_left]){
        printf("left\n");
        return 1;
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
            (Joueur.xSpeed > 0) ? (Joueur.xSpeed -= GROUND_FRICTION * Joueur.xSpeed + GROUND_MVT/1.32) : (Joueur.xSpeed += GROUND_FRICTION * Joueur.xSpeed+ GROUND_MVT/1.32);

            Joueur.x += Joueur.xSpeed;
            break;
        
        case 2: //right side collided
            Joueur.xSpeed = -0.001;
            Joueur.xSpeed -= GROUND_MVT * Keys[3];
            Joueur.x += Joueur.xSpeed;
            break;

        case 1: //left side collided
            Joueur.xSpeed = +0.001;
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

    switch (checkCollisionY())
    {
    case 1: // Ground collision
        Joueur.ySpeed = 0;
        Joueur.ySpeed = -0.00005;
        Joueur.isGrounded = 1;
        Joueur.ySpeed -= JUMP_SPEED * Keys[0];
        break;

    case 2: // Aie ma tête !
        Joueur.ySpeed = 0;
        Joueur.isGrounded = 1;
        break;

    case 0: //falling
        Joueur.ySpeed += GRAVITY;
        break;

    default:
        break;
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

