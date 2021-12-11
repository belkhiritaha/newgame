#include "render.h"

int TailleEcranLong;
int TailleEcranHaut;
int nbBlocks;
int score = 0;
TTF_Font *RobotoFont;

SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;

SDL_Color White = {255, 255, 255};

SDL_Rect score_rect;

char score_str[20];

SDL_Rect Message_rect;

SDL_Surface *blocks[7];


void SDL_ExitWithError(const char *message){
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}


void afficher(SDL_Renderer * renderer, int map[][MAP_SIZE_Y], SDL_Rect rect,SDL_Texture  *block_texture){
    rect.x = 0;
    rect.y = 0;
    rect.w = TailleEcranLong/NB_BLOCKS_X;
    rect.h = TailleEcranHaut/NB_BLOCKS_Y;

    for(int j = 0; j< NB_BLOCKS_Y; j++){
            for (int i = 0; i < NB_BLOCKS_X; i++)
            {
                rect.x = i * rect.w;
                rect.y = j * rect.h;
                if(map[i][j] == 1){
                    block_texture = SDL_CreateTextureFromSurface(renderer, blocks[0]);
                    SDL_RenderCopy(renderer, block_texture, NULL, &rect);
                    SDL_DestroyTexture(block_texture);
                }
            }    
        }
    SDL_RenderPresent(renderer);
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

  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    end_sdl(0, "ERROR SDL INIT");

  //récupère la taille de l'écran
  SDL_GetCurrentDisplayMode(0, &screen_dimension);
  //      printf("Taille de l'écran\n\tw : %d\n\th : %d\n", screen_dimension.w,
  //      screen_dimension.h);


  /* Création de la fenêtre, cas avec erreur */
  window = SDL_CreateWindow("newgame", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, WINDOW_W,
                            WINDOW_H, SDL_WINDOW_RESIZABLE);

  if (window == NULL)
    end_sdl(0, "ERROR WINDOW CREATION");

  /* Création du renderer (le truc dans la windows) */
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
  if (renderer == NULL)
    end_sdl(0, "ERROR RENDERER CREATION");


  // écrire (lettre chiffre) dans le render, grace à la bibliothèque TTF
  if (TTF_Init() == -1)
  {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
  }

  /* Taille de écran fournit par SDL */
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
        
    blocks[0] = IMG_Load("Res/green.png");
    SDL_Texture *block_texture = NULL;

    score_rect.x = 0;
    score_rect.y = 0;

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
                afficher(renderer, map, rect, block_texture);
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