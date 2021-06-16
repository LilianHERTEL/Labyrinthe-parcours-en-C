#include "animation.h"

/**
 * @brief Permet de fermer toute la sdl et d'indiquer un message d'erreur si il y en a une
 * 
 * @param ok 0 : erreur, 1 :normal
 * @param msg message de fin
 * @param window fenetre a fermer
 * @param renderer rendu a fermer
 */
void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer)
{                           
  char msg_formated[255];                                         
  int l;                                                          

  if (!ok) 
  {                                                      
         strncpy(msg_formated, msg, 250);                                 
         l = strlen(msg_formated);                                        
         strcpy(msg_formated + l, " : %s\n");                     
         SDL_Log(msg_formated, SDL_GetError());                   
  }                                                               

  if (renderer != NULL) SDL_DestroyRenderer(renderer);                            
  if (window != NULL)   SDL_DestroyWindow(window); 

  IMG_Quit();
  SDL_Quit();                                                            
}


void placerImage(SDL_Texture* my_texture,SDL_Window* window,SDL_Renderer* renderer, float zoom, float destX, float destY) 
{
  SDL_Rect  source = {0},                // Rectangle définissant la zone de la texture à récupérer
            window_dimensions = {0},     // Rectangle définissant la fenêtre
            destination = {0};           // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);         
  SDL_QueryTexture(my_texture, NULL, NULL,&source.w, &source.h); 

  destination.w = source.w * zoom;      
  destination.h = source.h * zoom;        
  destination.x = destX;  
  destination.y = destY;  

  SDL_RenderCopy(renderer, my_texture, &source, &destination);            
}

void animation(SDL_Texture *sol,SDL_Texture * fond, SDL_Texture * perso, SDL_Window * window, SDL_Renderer * renderer)
{
  SDL_Rect    source = {0},                // Rectangle définissant la zone totale de la planche
              window_dimensions = {0},     // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
              destination = {0},           // Rectangle définissant où la zone_source doit être déposée dans le renderer
              state = {0};                 // Rectangle de la vignette en cours dans la planche 
  int         offset_y,
              offset_x,
              x,
              speed = 15, 
              nb_images = 9;               // 9 Images sur la premiere ligne de la planche     
  float       zoom = 2;  

  SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
  SDL_QueryTexture(perso, NULL, NULL, &source.w, &source.h);  

  // Dimensions de la vignette dans la planche
  offset_x = source.w / nb_images, 
  offset_y = source.h / 3;                 // 3 lignes sur la planche
  // Dimensions de la vignette
  state.w = offset_x;             
  state.h = offset_y;             
  // Dimensions du sprite a l'ecran
  destination.w = offset_x * zoom;       
  destination.h = offset_y * zoom;     
  // Position du debut de l'animation 
  destination.y = window_dimensions.h - offset_y*zoom;

  for (x = 0; x < window_dimensions.w - destination.w; x += speed) 
  {
    destination.x = x;              // Position x de la vignette (elle bouge horizontalement)
    state.x += offset_x;            // Vignette suivante
    state.x %= source.w;            // Pour revenir a la vignette du debut        
    
    SDL_RenderClear(renderer);      
    placerImage(fond, window, renderer, 3.5, 0 - x*0.8, - window_dimensions.w/2);
    placerImage(sol, window, renderer, 4, 0 - x * 1.5, window_dimensions.h - 150 );
    SDL_RenderCopy(renderer, perso, &state, &destination);  
    SDL_RenderPresent(renderer);        
    SDL_Delay(80);              
  }
  SDL_RenderClear(renderer);       
}


int main(int argc, char **argv) 
{
  (void)argc;
  (void)argv;

  SDL_Window       * window = NULL;
  SDL_Renderer     * renderer = NULL;
  SDL_DisplayMode    screen;
  SDL_Texture      * perso,
                   * fond,
                   * sol;

  /* INITIALISATIONS */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) 
  {
      end_sdl(0, "ERROR SDL INIT", window, renderer);
      exit(EXIT_FAILURE); 
  }

  if(SDL_GetCurrentDisplayMode(0, &screen) != 0)
  {
      end_sdl(0, "ERROR GET_DISPLAY_MODE", window, renderer);
      exit(EXIT_FAILURE); 
  }

  window = SDL_CreateWindow("Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                              screen.w * 0.8, screen.h * 0.8, SDL_WINDOW_RESIZABLE);
  if (window == NULL) 
  {
      end_sdl(0, "ERROR WINDOW CREATION", window, renderer);
      exit(EXIT_FAILURE); 
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) 
  {
      end_sdl(0, "ERROR RENDERER CREATION", window, renderer);
      exit(EXIT_FAILURE); 
  }

  /*TRAITEMENT*/

  //Creation de toutes les textures
  perso = IMG_LoadTexture(renderer,"../img/adventurer_tilesheet.png");
  if (perso == NULL) 
  {
    end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    exit(EXIT_FAILURE);
  }

  fond = IMG_LoadTexture(renderer,"../img/background.png");
  if (fond == NULL) 
  {
    SDL_DestroyTexture(perso); 
    end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    exit(EXIT_FAILURE);
  }

  sol = IMG_LoadTexture(renderer,"../img/groundDirt.png");
  if (sol == NULL) 
  {
    SDL_DestroyTexture(perso); 
    SDL_DestroyTexture(fond); 
    end_sdl(0, "Echec du chargement de l'image dans la texture", window, renderer);
    exit(EXIT_FAILURE);
  }

  //Jouer l'animation
  animation(sol, fond, perso, window, renderer);

  //Destruction des textures utilisees
  SDL_DestroyTexture(perso); 
  SDL_DestroyTexture(fond); 
  SDL_DestroyTexture(sol); 

  end_sdl(1, "Normal ending", window, renderer);
  return EXIT_SUCCESS;
}