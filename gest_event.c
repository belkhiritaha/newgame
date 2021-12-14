#include "gest_event.h"

void * gestInput(SDL_Renderer * renderer){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
            switch(event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    printf("Click\n");
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_z:
                        Joueur.y -=0.1;
                        printf("player x = %f  y = %f",Joueur.x ,Joueur.y);
                        printf("move up\n");
                        continue;
                    
                    case SDLK_q:
                        Joueur.x -= 1;
                        printf("player x = %f  y = %f",Joueur.x ,Joueur.y);
                        printf("move left\n");
                        continue;
                    
                    case SDLK_d:
                        printf("player x = %f  y = %f",Joueur.x ,Joueur.y);
                        Joueur.x +=1;
                        printf("move right\n");
                        continue;

                    case SDLK_s:
                        Joueur.y +=1;
                        printf("player x = %f  y = %f",Joueur.x ,Joueur.y);
                        printf("move down\n");
                        continue;

                    case SDLK_x:
                        EtapeActuelleDuJeu = 0;
                        running = 0;
                        break;
                    
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