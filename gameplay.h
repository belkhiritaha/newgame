#ifndef GAMPELAY_HEADER_
#define GAMEPLAY_HEADER_

#include "map.h"
#include "entity.h"
#include "gest_event.h"
#include <math.h>
#define MAX_RUN_SPEED 0.005
#define MAX_Y_SPEED 0.001
#define JUMP_SPEED 0.00001
#define GROUND_MVT 0.00001
#define GROUND_FRICTION (9/10)
#define AIR_FRICTION (9.5/10)
#define GRAVITY 0.0001

void initPlayer(Player_t * pJoueur);
void gestPhysique();

#endif /* GAMEPLAY_HEADER_ */
