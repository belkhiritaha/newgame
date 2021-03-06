#ifndef GAMPELAY_HEADER_
#define GAMEPLAY_HEADER_

#include "map.h"
#include "entity.h"
#include "gest_event.h"
#include <math.h>
#define MAX_RUN_SPEED 0.007
#define ENNEMY_MAX_RUN_SPEED 0.005
#define MAX_Y_SPEED 0.001
#define JUMP_SPEED 0.0048
#define GROUND_MVT 0.00006
#define ENNEMY_GROUND_MVT 0.00003
#define GRAVITY 0.000008

extern int DrawJumpEffect;
extern int AttackNum;

void initPlayer(Player_t * pJoueur, float x, float y);
void gestPhysique();

#endif /* GAMEPLAY_HEADER_ */
