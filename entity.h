#ifndef ENTITY_HEADER_
#define ENTITY_HEADER_

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
}Player_t;

extern Player_t Joueur;

#endif /* ENTITY_HEADER_ */
