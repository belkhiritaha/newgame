#include "render.h"

int TailleEcranLong;
int TailleEcranHaut;
int nbBlocks;
int score = 0;
TTF_Font *RobotoFont;

SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;

SDL_Color White = {255, 255, 255};

SDL_Rect Message_rect;


SDL_Surface *jump_surface;
SDL_Surface *background;
SDL_Surface *blocks[7];
SDL_Surface *character_sprite[10];
SDL_Surface *king_sprite[10];
SDL_Surface *character_sprite_attack[4];
SDL_Surface *king_sprite_attack[4];
SDL_Texture * sprite_texture;


void SDL_ExitWithError(const char *message){
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void DrawHealthBar(SDL_Renderer* renderer, Player_t * pEntity ,float x, float y){
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = 50 * pEntity->Health/200;
    rect.h = 5;
    SDL_SetRenderDrawColor(renderer, 0,255,0,255);
    SDL_RenderFillRect(renderer,&rect);
}

void DrawEnnemies(SDL_Renderer* renderer, SDL_Texture* ennemy_texture, float posX, float posY, Player_t * Ennemy){
    int tick = SDL_GetTicks()/500;
    SDL_Rect rect;
    rect.w = (TailleEcranLong/NB_BLOCKS_X) * Joueur.w;
    rect.h =(TailleEcranHaut/NB_BLOCKS_Y) * Joueur.h;
    rect.x = TailleEcranLong/2 - rect.w + (Ennemy->x - posX) * 100;
    rect.y = TailleEcranHaut/2 - (TailleEcranHaut/NB_BLOCKS_Y) + (Ennemy->y - posY) * 80;
    DrawHealthBar(renderer, Ennemy, rect.x, rect.y);
    SDL_Rect sprt_rect;
    //printf("%f %f \n", Ennemy->x, posX);
    if (Ennemy->x + Ennemy->w > posX - 5 && Ennemy->x - Ennemy->w < posX + 5  && Ennemy->y + Ennemy->h > posY - 5 && Ennemy->y - Ennemy->h < posY + 5){
        if (Ennemy->isGrounded){
            if (fabs(Ennemy->xSpeed) < 0.003){
                sprt_rect.h = 54;
                sprt_rect.w = 31;
                sprt_rect.x = 31 * (tick % 8);
                sprt_rect.y = 0;
                sprite_texture = SDL_CreateTextureFromSurface(renderer, king_sprite[0]);
            }
            else {
                sprt_rect.h = 53;
                sprt_rect.w = 45;
                sprt_rect.x = 45 * (tick % 8);
                sprt_rect.y = 0;
                sprite_texture = SDL_CreateTextureFromSurface(renderer, king_sprite[1]);
            }
        }
        else {
            if (Ennemy->ySpeed > 0){
                sprt_rect.h = 52;
                sprt_rect.w = 44;
                sprt_rect.x = 44 * (tick % 2);
                sprt_rect.y = 0;
                sprite_texture = SDL_CreateTextureFromSurface(renderer, king_sprite[3]);
            }
            else {
                sprt_rect.h = 54;
                sprt_rect.w = 41;
                sprt_rect.x = 41 * (tick % 2);
                sprt_rect.y = 0;
                sprite_texture = SDL_CreateTextureFromSurface(renderer, king_sprite[2]);
            }
            
        }
        if (Ennemy->isAttacking){
            sprt_rect.h = 68;
            sprt_rect.w = 44;
            sprt_rect.x = 0;
            sprt_rect.y = 0;
            sprite_texture = SDL_CreateTextureFromSurface(renderer, king_sprite_attack[Ennemy->AttackNum]);
        }
        else if (Ennemy->isTakingDmg){
            sprt_rect.h = 55;
            sprt_rect.w = 48;
            sprt_rect.x = 48 * (SDL_GetTicks()/250 - Joueur.tick);
            sprt_rect.y = 0;
            sprite_texture = SDL_CreateTextureFromSurface(renderer, king_sprite[5]);
        }
        SDL_RenderCopyEx(renderer, sprite_texture, &sprt_rect, &rect, 0, NULL, SDL_FLIP_HORIZONTAL *(1 - Ennemy->direction));
        SDL_DestroyTexture(sprite_texture);
    }
}

void DrawPlayer(SDL_Renderer* renderer ,SDL_Rect rect , SDL_Texture* sprite_texture){
    for (int i = 0; i < EnnemiesCount; i++){
        Player_t * Ennemy = ListeEnnemies[i];
        DrawEnnemies(renderer, sprite_texture, Joueur.x, Joueur.y, Ennemy);
    }
    int tick = SDL_GetTicks()/500;
    SDL_Rect sprt_rect;
    sprt_rect.h = 50;
    sprt_rect.w = 45;
    sprt_rect.x = 45 * (tick % 8);
    sprt_rect.y = 0;
    rect.w = (TailleEcranLong/NB_BLOCKS_X) * Joueur.w;
    rect.h =(TailleEcranHaut/NB_BLOCKS_Y) * Joueur.h;
    rect.x = TailleEcranLong/2 - rect.w;
    rect.y = TailleEcranHaut/2 - (TailleEcranHaut/NB_BLOCKS_Y);
    if (Joueur.isGrounded){
        if (fabs(Joueur.xSpeed) < 0.003){
            sprt_rect.h = 56;
            sprt_rect.w = 35;
            sprt_rect.x = 35 * (tick % 4);
            sprt_rect.y = 0;
            sprite_texture = SDL_CreateTextureFromSurface(renderer, character_sprite[0]);
        }
        else {
            //tick += (int)((MAX_RUN_SPEED) / Joueur.xSpeed);
            sprt_rect.h = 50;
            sprt_rect.w = 45;
            sprt_rect.x = 45 * (tick % 8);
            sprt_rect.y = 0;

            sprite_texture = SDL_CreateTextureFromSurface(renderer, character_sprite[1]);
        }
    }
    else{
        if (Joueur.ySpeed > 0){
            sprt_rect.h = 55;
            sprt_rect.w = 37;
            sprt_rect.x = 37 * (tick % 2);
            sprt_rect.y = 0;

            sprite_texture = SDL_CreateTextureFromSurface(renderer, character_sprite[3]);
        }
        else {
            sprt_rect.h = 56;
            sprt_rect.w = 36;
            sprt_rect.x = 36 * (tick % 2);
            sprt_rect.y = 0;

            sprite_texture = SDL_CreateTextureFromSurface(renderer, character_sprite[2]);        
        }
    }

    if (DrawJumpEffect){
        rect.y += 30;
        SDL_Texture* jump_texture;
        jump_texture = SDL_CreateTextureFromSurface(renderer, jump_surface);
        SDL_RenderCopy(renderer, jump_texture, NULL, &rect);
        SDL_DestroyTexture(jump_texture);
        rect.y -= 30;
    }

    if (Joueur.isAttacking){
        if (Joueur.AttackNum == 2){
            rect.x+= 50 * (Joueur.direction - 1);
            rect.h *=2;
            rect.w *=2;
            rect.y-=160;
        }
        else {
            rect.w *=1.5;
        }
        sprite_texture = SDL_CreateTextureFromSurface(renderer, character_sprite_attack[Joueur.AttackNum]);
        SDL_RenderCopyEx(renderer, sprite_texture, NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL*(1-Joueur.direction));
    }
    else {
        SDL_RenderCopyEx(renderer, sprite_texture, &sprt_rect, &rect, 0, NULL, SDL_FLIP_HORIZONTAL*(1-Joueur.direction));
    }
    SDL_DestroyTexture(sprite_texture);

}


void afficher(SDL_Renderer * renderer, SDL_Rect rect,SDL_Texture  *block_texture, SDL_Texture *sprite_texture, SDL_Texture *bg_texture){
    bg_texture = SDL_CreateTextureFromSurface(renderer, background);
    block_texture = SDL_CreateTextureFromSurface(renderer, blocks[0]);
//////////////// affichage background
    SDL_Rect parallax;
    parallax.h = 1080;
    parallax.w = 910;
    parallax.x = 10 * Joueur.x;
    parallax.y = 0;
    rect.h = TailleEcranHaut;
    rect.w = TailleEcranLong;
    rect.x = 0;
    rect.y = 0;
    SDL_RenderCopy(renderer, bg_texture, &parallax, &rect);
//////////////// affichage map 
    float side_padding = (Joueur.x - (int)Joueur.x);
    float top_padding = 1 - (Joueur.y  -(int)Joueur.y);
    rect.w = (TailleEcranLong/NB_BLOCKS_X);
    rect.h = (TailleEcranHaut/NB_BLOCKS_Y);
    rect.x =  -side_padding * rect.w;
    rect.y = (top_padding- 1) * rect.h;
    int offset_y;
    int offset_x;
    for(int y = 0; y<NB_BLOCKS_Y + 4; y++){
            for (int x = 0; x < NB_BLOCKS_X +5; x++)
            {
                offset_x = x + Joueur.x - 4;
                offset_y = y + Joueur.y - 4;
                //printf("offset_x = %d, offset_y = %d\n", offset_x, offset_y);
                //printf("%d %d\n", rect.x, rect.y);
                
                if (offset_y >= 0 && offset_y < MAP_SIZE_Y && offset_x >= 0 && offset_x < MAP_SIZE_X){
                    if(map[offset_y][offset_x] == 1){
                        SDL_RenderCopy(renderer, block_texture, NULL, &rect);
                    }
                }
                rect.x = rect.x + rect.w;
            }
        rect.x = -side_padding * rect.w;
        rect.y = rect.y + rect.h;
        //rect.y = 0;// top_padding * rect.h;
    }
//////////////// affichage joueur
    DrawPlayer(renderer, rect, sprite_texture);
////////////////
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(block_texture); 
    SDL_DestroyTexture(sprite_texture);
    SDL_DestroyTexture(bg_texture);
}

void end_sdl(char ok, char const * msg) {
  SDL_Window * window = NULL;
  SDL_Renderer * renderer = NULL;
  char msg_formated[255];
  int l;

  if (!ok){
    strncpy(msg_formated, msg, 250);
    l = strlen(msg_formated);
    strcpy(msg_formated+l, " : %s\n");

    SDL_Log(msg_formated, SDL_GetError());
  }

  if(renderer != NULL){
    SDL_DestroyRenderer(renderer);
  }
  if(window != NULL){
    SDL_DestroyWindow(window);
  }
  SDL_Quit();

  if (!ok) {exit(EXIT_FAILURE);}
}


void create_Win() {
  SDL_DisplayMode screen_dimension;

  /* Initialisation de la SDL  + gestion de l'??chec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    end_sdl(0, "ERROR SDL INIT");

  //r??cup??re la taille de l'??cran
  SDL_GetCurrentDisplayMode(0, &screen_dimension);
  //      printf("Taille de l'??cran\n\tw : %d\n\th : %d\n", screen_dimension.w,
  //      screen_dimension.h);


  /* Cr??ation de la fen??tre, cas avec erreur */
  window = SDL_CreateWindow("newgame", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, WINDOW_W,
                            WINDOW_H, SDL_WINDOW_RESIZABLE);

  if (window == NULL)
    end_sdl(0, "ERROR WINDOW CREATION");

  /* Cr??ation du renderer (le truc dans la windows) */
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
  if (renderer == NULL)
    end_sdl(0, "ERROR RENDERER CREATION");


  // ??crire (lettre chiffre) dans le render, grace ?? la biblioth??que TTF
  if (TTF_Init() == -1)
  {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
  }

  /* Taille de ??cran fournit par SDL */
  SDL_GetWindowSize(window, &TailleEcranLong, &TailleEcranHaut);

  RobotoFont = TTF_OpenFont("Roboto-Black.ttf", 50);
  
}




void DrawMenu(SDL_Renderer * renderer, SDL_Rect rect){

}


void *BoucleGestInput(void *arg){
    while(EtapeActuelleDuJeu){
      switch(EtapeActuelleDuJeu){
          case 1 : gestInput(renderer);break;
          //case 2 : gestMenu();break;
          default:printf("Cette etape du jeu n'existe pas...\n");break;
      }
    }
    return NULL;
}


int BouclePrincipale()
{
    create_Win();
        
    blocks[0] = IMG_Load("Res/block.png");
    jump_surface = IMG_Load("Res/jump_effect.png");
    character_sprite[0] = IMG_Load("Res/idle_spritesheet.png");
    character_sprite[1] = IMG_Load("Res/run_spirtesheet.png");
    character_sprite[2] = IMG_Load("Res/jump_spritesheet.png");
    character_sprite[3] = IMG_Load("Res/fall_spritesheet.png");
    character_sprite[4] = IMG_Load("Res/player_walk2.png");
    character_sprite[5] = IMG_Load("Res/player_walk3.png");

    king_sprite[0] = IMG_Load("Res/king_idle_spritesheet.png");
    king_sprite[1] = IMG_Load("Res/king_run_spritesheet.png");
    king_sprite[2] = IMG_Load("Res/king_jump_spritesheet.png");
    king_sprite[3] = IMG_Load("Res/king_fall_spritesheet.png");
    king_sprite[4] = IMG_Load("Res/king_attack_spritesheet.png");
    king_sprite[5] = IMG_Load("Res/king_takingdmg_spritesheet.png");
    background = IMG_Load("Res/Cartoon_Forest_BG_03.png");

    character_sprite_attack[0] = IMG_Load("Res/attack0.png");
    character_sprite_attack[1] = IMG_Load("Res/attack1.png");
    character_sprite_attack[2] = IMG_Load("Res/attack2.png");
    character_sprite_attack[3] = IMG_Load("Res/attack3.png");

    king_sprite_attack[0] = IMG_Load("Res/king_attack0.png");
    king_sprite_attack[1] = IMG_Load("Res/king_attack1.png");
    king_sprite_attack[2] = IMG_Load("Res/king_attack2.png");
    king_sprite_attack[3] = IMG_Load("Res/king_attack3.png");
    SDL_Texture *bg_texure = NULL;
    SDL_Texture *block_texture = NULL;
    SDL_Texture *sprite_texture = NULL;

    Message_rect.x = 0; 
    Message_rect.y = 0; 
    Message_rect.w = 200;
    Message_rect.h = 100; 

    nbBlocks = 0;

    ////// thread gest input
    pthread_t threadGest;
    int RetourDuThreadGest = pthread_create(&threadGest, NULL, BoucleGestInput, NULL);
    if (RetourDuThreadGest){
        return 1;
    }
    ////// fin thread gest input
    SDL_Rect rect;

    while (running) {
        switch(EtapeActuelleDuJeu){
            case 2:
               // DrawMenu();
                break;
            case 1:
                afficher(renderer, rect, block_texture, sprite_texture, bg_texure);
                //SDL_Delay(10);
                SDL_RenderClear(renderer);
                break;
                //case 420:WinOrange();break;
                //case 421:WinVert();break;
            default:return 0;break;
        }
    }
    /* on referme proprement */
    end_sdl(1, "Normal ending");
    pthread_exit(NULL);
    return EXIT_SUCCESS;
}