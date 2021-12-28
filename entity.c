#include "entity.h"

Player_t Joueur;
Player_t * ListeEnnemies[NB_ENNEMY];

int EnnemiesCount = 0;

void initListeEnnemies(Player_t * ListeEnnemies[NB_ENNEMY], int * EnnemiesCount){
    while (*EnnemiesCount < NB_ENNEMY){
        ListeEnnemies[*EnnemiesCount] = CreateEnnemy();
        initPlayer(ListeEnnemies[*EnnemiesCount], rand() % 100, 5);
        *EnnemiesCount+= 1;
    }
}

void removeEnnemy(Player_t * ListeEnnemies[NB_ENNEMY], Player_t * pEnnemy, int * EnnemiesCount){
    for (int i = 0; i < *EnnemiesCount; i++){
        if (ListeEnnemies[i] == pEnnemy){
            for (int j = i; j < *EnnemiesCount- 1; j++){
                ListeEnnemies[j] = ListeEnnemies[j+1];
            }
            *EnnemiesCount-= 1;
        }
    }
}

void addEnnemytoList(Player_t * ListeEnnemies[NB_ENNEMY], Player_t * pEnnemy, int * EnnemiesCount){
    ListeEnnemies[*EnnemiesCount] = pEnnemy;
    *EnnemiesCount+= 1;
}


Player_t * CreateEnnemy(){
    Player_t * Ennemy = malloc(sizeof(Player_t));
    return Ennemy;
}
