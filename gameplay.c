#include "gameplay.h"

int DrawJumpEffect = 0;

void initPlayer(Player_t * pJoueur, float x, float y){
    pJoueur->x = x;
    pJoueur->y = y;
    pJoueur->isGrounded = 0;
    pJoueur->h = 2;
    pJoueur->w = 1;
    pJoueur->xHitbox = 0.95;
    pJoueur->yHitbox = 1.9;
    pJoueur->xSpeed = 0;
    pJoueur->ySpeed = 0;
    pJoueur->isAttacking = 0;
    pJoueur->AttackNum = 0;
    pJoueur->tick = 420;
    pJoueur->Health = 500;
    pJoueur->isTakingDmg = 0;
}

int checkCollisionY(Player_t *pEntity){
    int case_x = floorf(pEntity->x + pEntity->xSpeed + pEntity->xHitbox - 0.5);//dont touch this
    int case_y = floorf(pEntity->y + pEntity->ySpeed + pEntity->yHitbox);
    //printf("positions : %f %f\n",pEntity->x, pEntity->y);
    //printf("cases : %f %f %d\n", case_x, case_y, map[(int)case_y][(int)case_x]);
    //if (case_y >= 0 && case_y < NB_BLOCKS_Y && case_x >= 0 && case_x < NB_BLOCKS_X){
        if (map[case_y][case_x]){
            //printf("collide\n");
            pEntity->ySpeed = 0;
            pEntity->isGrounded = 1;
            return 1;
        }
        else {
            pEntity->isGrounded = 0;
        }
    //}
    return 0;
}

int checkCollisionX(Player_t *pEntity){
    int case_right = ceilf(pEntity->x - 2/16.0);
    int case_left = floorf(pEntity->x + 2/16.0);
    int case_bot = floorf(pEntity->y + pEntity->xHitbox - 1) + 1;
    int case_top = case_bot - 1;
    int case_below = floorf(pEntity->y + pEntity->xHitbox + 2/16.0 - 1) + 1 +1;
    //printf("left = %d , pos = %f, %f , right = %d, bot= %d top= %d\n", case_left, pEntity->x,pEntity->y, case_right, case_bot, case_top);
    //printf("DESTINATION: %f\n", pEntity->x + xSpeed);
    if (map[case_bot][case_right] || map[case_top][case_right]){// || (pEntity->isFalling && pEntity->y - (int)pEntity->y > 0.7 && map[case_below][case_right])){
        pEntity->xSpeed = 0;
        return 2;
    }
    if (map[case_bot][case_left] || map[case_top][case_left]){// || (pEntity->isFalling && pEntity->y - (int)pEntity->y > 0.7 && map[case_below][case_left])){
        pEntity->xSpeed = 0;
        return 1;
    }
    return 0;
}

int PlayerMoveX(Player_t * pEntity){
    //printf("pos : %f %f\n", pEntity->x, pEntity->y);
    //printf("xSpeed = %f, ySpeed = %f\n", pEntity->xSpeed, pEntity->ySpeed);
    switch (checkCollisionX(pEntity))
    {
        case 0: //no sides collided
            if (fabs(pEntity->xSpeed) < MAX_RUN_SPEED){
                pEntity->xSpeed += GROUND_MVT * (Keys[1] - Keys[3]);
            }
            (pEntity->xSpeed > 0) ? (pEntity->xSpeed -= GROUND_MVT/1.32) : (pEntity->xSpeed += GROUND_MVT/1.32);

            pEntity->x += pEntity->xSpeed;
            break;
        
        case 2: //right side collided
            pEntity->xSpeed -= GROUND_MVT * Keys[3];
            pEntity->x += pEntity->xSpeed;
            break;

        case 1: //left side collided
           pEntity->xSpeed += GROUND_MVT * Keys[1];
            pEntity->x += pEntity->xSpeed;
            break;

        default:
            break;
    }

    return 1;
}

int EntityMoveX(Player_t *pEntity){
    int MoveLeft = 0;
    int MoveRight = 0;
    (pEntity->x - Joueur.x > 0) ? (pEntity->direction = 0):(pEntity->direction = 1);
    if (fabs(pEntity->x - Joueur.x) < 4.5){
        if (fabs(pEntity->x - Joueur.x) > 1.5){
            if (pEntity->x - Joueur.x < 0){
                MoveRight = 1;
                MoveLeft = 0;
            }
            else {
                MoveLeft = 1;
                MoveRight = 0;
            }
            pEntity->isAttacking = 0;
        }
        else {
            if (!pEntity->isTakingDmg){
                pEntity->isAttacking = 1;
            }
            MoveRight = 0;
            MoveLeft = 0;
        }
    }

    switch (checkCollisionX(pEntity))
    {
        case 0: //no sides collided
            if (fabs(pEntity->xSpeed) < ENNEMY_MAX_RUN_SPEED){
                pEntity->xSpeed += ENNEMY_GROUND_MVT * (MoveRight - MoveLeft);
            }
            (pEntity->xSpeed > 0) ? (pEntity->xSpeed -= ENNEMY_GROUND_MVT/1.32) : (pEntity->xSpeed += ENNEMY_GROUND_MVT/1.32);

            pEntity->x += pEntity->xSpeed;
            break;
        
        case 2: //right side collided
            pEntity->xSpeed -= ENNEMY_GROUND_MVT * MoveLeft;
            pEntity->x += pEntity->xSpeed;
            break;

        case 1: //left side collided
           pEntity->xSpeed += ENNEMY_GROUND_MVT * MoveRight;
            pEntity->x += pEntity->xSpeed;
            break;

        default:
            break;
    }

    return 1;
}

int EntityMoveY(Player_t *pEntity){
    int Jump = 0;
    (checkCollisionX(pEntity)) ? (Jump = 1) : (Jump = 0);
    if (checkCollisionY(pEntity)){
        pEntity->ySpeed -= JUMP_SPEED * Jump;
    }
    else{
        pEntity->ySpeed += GRAVITY;
    }
    pEntity->y += pEntity->ySpeed;
    return 1;
}

int PlayerMoveY(Player_t * pEntity){
    //printf("ySpeed = %f\n", pEntity->ySpeed);
    if (checkCollisionY(pEntity)){
        pEntity->ySpeed -= JUMP_SPEED * (Keys[0]);
        if (Keys[0]){
            DrawJumpEffect = 1;
        }
    }
    else{
        DrawJumpEffect = 0;
        pEntity->ySpeed += GRAVITY;
    }
   pEntity->y += pEntity->ySpeed;
    return 1;
}

void checkAttack(Player_t * pEnnemy){
    if (fabs(pEnnemy->x - Joueur.x) < 1.3 && fabs(pEnnemy->y - Joueur.y) < 1.5 && Joueur.AttackNum > 1){
        if (pEnnemy->Health > 0){
            pEnnemy->Health -= 1;
            pEnnemy->isTakingDmg = 1;
            pEnnemy->isAttacking = 0;
        }
        else {
            printf("dead\n");
            removeEnnemy(ListeEnnemies, pEnnemy, &EnnemiesCount);
        }
    }
    else {
        pEnnemy->isTakingDmg = 0;
    }
}

void incAttack(Player_t * pEntity){
    //printf("%d %d %d\n", *pJoueurAttack, *pAttackNum, *tick);
    if (pEntity->isAttacking == 0){
        pEntity->AttackNum = 0;
        pEntity->tick = 420;
    }
    else {
        if (pEntity->tick == 420){
            pEntity->tick  = SDL_GetTicks()/250;
        }
        if (pEntity->AttackNum < 3){
            pEntity->AttackNum = SDL_GetTicks()/250 - pEntity->tick;
        }
    }
}


void gestPhysique(){
    incAttack(&Joueur);
    //printf("%p\n", Ennemy);
    for (int i = 0; i < EnnemiesCount ; i++){
        Player_t * Ennemy = ListeEnnemies[i];
        incAttack(Ennemy);
        checkAttack(Ennemy);
        EntityMoveX(Ennemy);
        EntityMoveY(Ennemy);
    }
    PlayerMoveX(&Joueur);
    PlayerMoveY(&Joueur);

}

