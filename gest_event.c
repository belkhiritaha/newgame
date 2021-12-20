#include "gest_event.h"

int Keys[NB_KEYS];
int JoueurAttack = 0;

void initKeys(int Keys[NB_KEYS]){
    for (int i = 0; i < 4; i++){
        Keys[i] = 0;
    }
}

void * gestInput(SDL_Renderer * renderer){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
            switch(event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    JoueurAttack = 1;
                    break;

                case SDL_MOUSEBUTTONUP:
                    JoueurAttack = 0;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_z:
                        Keys[0] = 1;
                        continue;
                    
                    case SDLK_q:
                        Keys[3] = 1;
                        Joueur.direction = 0;
                        continue;
                    
                    case SDLK_d:
                        Keys[1] = 1;
                        Joueur.direction = 1;
                        continue;

                    case SDLK_s:
                        Keys[2] = 1;
                        continue;

                    case SDLK_x:
                        EtapeActuelleDuJeu = 0;
                        running = 0;
                        break;
                    
                    default:
                        continue;
                    }
                
                case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_z:
                        Keys[0] = 0;
                        continue;
                    
                    case SDLK_q:
                        Keys[3] = 0;
                        continue;
                    
                    case SDLK_d:
                        Keys[1] = 0;
                        continue;

                    case SDLK_s:
                        Keys[2] = 0;
                        continue;
                    
                    default:
                        continue;
                    }
                
                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
                        TailleEcranHaut = event.window.data2;
                        TailleEcranLong = event.window.data1;
                    }
                    break;

                case SDL_QUIT:
                    running = 0;
                    EtapeActuelleDuJeu = 0;
                    break;

                default:
                    break;
                }
            }
    gestPhysique();
    SDL_Delay(1);
    return NULL;
}

void * gestMenu(){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    EtapeActuelleDuJeu = 1;

                case SDL_QUIT:
                    running = 0;
                    EtapeActuelleDuJeu = 0;
                    break;

                default:
                    break;
                }
            }
    SDL_Delay(1);
    return NULL;
}