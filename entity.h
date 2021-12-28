#ifndef ENTITY_HEADER_
#define ENTITY_HEADER_

#include <stdlib.h>
#include <stdio.h>

#define NB_ENNEMY 20

typedef struct Player{
    float x;
    float y;

    float xSpeed;
    float ySpeed;

    float sizeX; //Animation
    float sizeY;

    float xHitbox; // taille de la hitbox
    float yHitbox;

    int w; // offset entre x et le coin de la hitbox
    int h;

    int direction;
    int isGrounded;
    int isFalling;
}Player_t;

#include "gameplay.h"

extern Player_t Joueur;

extern Player_t * ListeEnnemies[NB_ENNEMY];

extern int EnnemiesCount;

Player_t * CreateEnnemy();
void initListeEnnemies(Player_t * ListeEnnemies[NB_ENNEMY], int * EnnemiesCount);
void removeEnnemy(Player_t * ListeEnnemies[NB_ENNEMY], Player_t * pEnnemy, int * EnnemiesCount);
void addEnnemytoList(Player_t * ListeEnnemies[NB_ENNEMY], Player_t * pEnnemy, int * EnnemiesCount);

#endif /* ENTITY_HEADER_ */
