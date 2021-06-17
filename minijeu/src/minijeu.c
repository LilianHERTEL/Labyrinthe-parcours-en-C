#include "minijeu.h"

/**
 * @brief Permet de calculer les dimensions d'une cellule par rapport a la taille de la fenetre
 * 
 * @param window la fenetre
 * @param cell la cellule (SDL_Rect)
 * @param n nombre de lignes de la grille
 * @param m nombre de colonnes de la grille
 */
void cellDimensions(SDL_Rect * cell, int n, int m, SDL_Rect window_dimensions)
{
    cell->w = (window_dimensions.w * 0.6) / m;
    cell->h = (window_dimensions.h * 0.3) / n ;    
    cell->x = 0 ;
    cell->y = 0 ;
}

/**
 * @brief Affiche les briques
 * 
 * @param renderer 
 * @param grille 
 * @param n 
 * @param m 
 * @param cell
 */
void drawBricks(SDL_Renderer *renderer, int ** bricks, int n, int m, SDL_Rect cell, SDL_Texture *texture) 
{
	int               i,
                      j,
                      poseX,
                      poseY;
	SDL_Rect          rectangle,
                      source = {0};

    rectangle.w = cell.w;
    rectangle.h = cell.h;
    poseX = cell.x;
    poseY = cell.y;
    source.w = 390;
    source.h = 130;

	for(i = 0; i < n; i++) {
		rectangle.y = poseY + rectangle.h * i;
		for(j = 0; j < m; j++) {
			rectangle.x = poseX + rectangle.w * j;
            if(bricks[i][j] == 1) {
                source.x = 770;
                source.y = 260;
                SDL_RenderCopy(renderer, texture, &source, &rectangle);
            }
		}
	}
}

void paddleDimensions(SDL_Rect * paddle, SDL_Rect cell, int m)
{
    paddle->w = cell.w * m * 0.25;
    paddle->h = cell.h * 0.5;
}

/**
 * @brief Affiche le paddle
 * 
 * @param renderer 
 * @param paddleDest 
 * @param texture
 */
void drawPaddle(SDL_Renderer * renderer, SDL_Rect paddleDest, SDL_Texture *texture)
{
    SDL_Rect paddleSource = {0};

   	paddleSource.x = 0;
	paddleSource.y = 910;
	paddleSource.w = 347;
	paddleSource.h = 65;
    SDL_RenderCopy(renderer, texture, &paddleSource, &paddleDest);
}

void ballDimensions(SDL_Rect * ball, SDL_Rect cell, int m)
{
    ball->w = cell.w * m * 0.05;
    ball->h = ball->w;
}

/**
 * @brief Affiche la balle
 * 
 * @param renderer 
 * @param paddleDest 
 * @param texture
 */
void drawBall(SDL_Renderer * renderer, SDL_Rect ball, SDL_Texture *texture)
{
    SDL_Rect source = {0};

   	source.x = 1402;
	source.y = 652;
	source.w = 65;
	source.h = 65;
    SDL_RenderCopy(renderer, texture, &source, &ball);
}

void drawLimits(SDL_Renderer *renderer, SDL_Rect cell, int m, SDL_Rect window_dimensions)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, cell.x, cell.y, cell.x, window_dimensions.h);
    SDL_RenderDrawLine(renderer, cell.x, cell.y, cell.x + cell.w * m, cell.y);
    SDL_RenderDrawLine(renderer, cell.x + cell.w * m, cell.y, cell.x + cell.w * m, window_dimensions.h);
}

void moveBall(SDL_Rect *ball, SDL_Rect speed)
{
    ball->x = ball->x + speed.x;
    ball->y = ball->y + speed.y;
}

void ballCollision(SDL_Rect ball, SDL_Rect cell, int ** bricks, int n, int m, SDL_Rect paddle, SDL_Rect * speed)
{
    //Collisions murs
    if(ball.x + speed->x <= cell.x)
    {
        speed->x = - speed->x;
    }
    if(ball.x + ball.w + speed->x > cell.x + cell.w * m)
    {
        speed->x = -speed->x;
    }
    //Collisions paddle
    if(ball.y + speed->y > paddle.y - paddle.h && ball.x >= paddle.x && ball.x <= paddle.x + paddle.w)
    {
        speed->y = - speed->y;
    }
    //Collisions briques
    if(ball.y + speed->y < cell.y + cell.h * n - 1)
    {
        int ballI, ballJ;
        ballI = (ball.y-cell.y)/cell.h ;
        ballJ = (ball.x - cell.x)/cell.w ;
        printf("%d, %d\n", ballI, ballJ);
        if(ballI < n && ballI >= 0 && bricks[ballI][ballJ] == 1)
        {
            if(ball.x + speed->x < ballJ * cell.w + cell.x + cell.w || ball.x + speed->x > ballJ* cell.w + cell.x)
            {
                speed->x = -speed->x;
            }
            if(ball.y + speed-> y < ballI * cell.h + cell.y + cell.h || ball.y + speed-> y > ballI * cell.h + cell.y)
            {
                speed->y = -speed->y;
            }
        }
        if(ball.y + speed->y <= cell.y) // mur du haut
        {
            speed->y = - speed->y;
        }
    }
}

void movePaddle(SDL_Rect* paddle, SDL_Rect cell, int m, int step) {
    int new_x = paddle->x + 20*step;
    if (new_x >= cell.x && new_x < cell.w*m - paddle->w) {
        paddle->x = new_x;
    }
}

void breakBrick(int ** bricks, int n, int m) {
    bricks[n, m] = 0;
}

bool_t updateScore(int* score, int* remainingBricks, SDL_Rect ball, int winHeight) {
    bool_t gameIsOver = false;
    if (ball.y > winHeight)
    {
        //gameIsOver = true;
        printf("GAME OVER\n");
    }
    

    return gameIsOver;
}

/**
 * @brief Boucle de jeu du casse-briques
 * 
 * @param window 
 * @param renderer 
 * @param grid 
 * @param n 
 * @param m 
 * @param rule 
 */
void gameLoop(SDL_Window * window, SDL_Renderer * renderer, int ** bricks, int n, int m)
{
	SDL_Texture *texture;									// texture des sprites du jeu
    SDL_bool  program_on = SDL_TRUE,                          // Booléen pour dire que le programme doit continuer
              paused = SDL_FALSE;                             // Booléen pour dire que le programme est en pause
    SDL_Rect  mouse = {0},
              paddleSource = {0},
              paddleDest = {0},
              cell = {0},
              window_dimensions = {0},
              paddle = {0},
              ball = {0},
              speed = {0};
    
    bool_t gameIsOver = false;

    speed.x = 20;
    speed.y = -20;
              
    int score = 0;
    int remainingBricks = n*m;

	texture = loadTextureFromImage("../res/sprites.png", renderer);
	//SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
	//SDL_QueryTexture(texture, NULL, NULL, NULL/*&paddleSource.w*/, /*&paddleSource.h*/NULL);
    // Initialisation des coordonnees
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    cellDimensions(&cell, n, m, window_dimensions);
    paddleDimensions(&paddle, cell, m);
    ballDimensions(&ball, cell, m);
    paddle.x = (cell.w * m - paddle.w) / 2; 
    paddle.y = window_dimensions.h - paddle.h;
    ball.x = (cell.w * m - ball.w) / 2; 
    ball.y = paddle.y - ball.h;

    while (program_on && !gameIsOver) 
    {                                   // La boucle des évènements
        SDL_Event event;                // Evènement à traiter

        while (program_on && SDL_PollEvent(&event) && !gameIsOver) 
        {                               // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
                                        // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type) 
            {      
                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_RESIZED)
                    {
                        // Calcul des dimensions d'une cellule quand la fenetre change de taille
                        SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
                        cellDimensions(&cell, n, m, window_dimensions);
                        paddleDimensions(&paddle, cell, m);
                        ballDimensions(&ball,cell, m);
                    }
                    break;
                case SDL_QUIT:                         
                    program_on = 0;                   
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) 
                    {             
                        case SDLK_LEFT:                                // 'fleche gauche'
                        	//bouger la plateforme a gauche
                            movePaddle(&paddle, cell, m, -1);
                        	break;
                        case SDLK_RIGHT:
                        	//bouger la plateforme a droite
                            movePaddle(&paddle, cell, m, 1);
                        	break;
                        case SDLK_SPACE:                            // 'SPC'
                            paused = !paused;                       // basculement pause/unpause
                            break;
                        case SDLK_ESCAPE:                           // 'ESCAPE'  
                        case SDLK_q:                                // 'q'
                            program_on = 0;
                            break;
                        default:                      
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:     
                    SDL_GetMouseState(&mouse.x, &mouse.y);
                    //Calcul des coordonnees par rapport a l'emplacement du labyrinthe
                    //mouse.x = (mouse.x - cell.x) / cell.w;
                    //mouse.y = (mouse.y - cell.y) / cell.h;
                    if (SDL_BUTTON(SDL_BUTTON_LEFT) ) 
                    {                       
                        //change_state(&grid, n, m, mouse.x, mouse.y);
                    } 
                    else if (SDL_BUTTON(SDL_BUTTON_RIGHT) ) 
                    {                                           
                        //change_state(&grid, n, m, mouse.x, mouse.y);          
                    }
                    break;
                default:                                            
                    break;
            }
        }
        // Changement du fond en fonction de la position de la souris
        SDL_GetMouseState(&mouse.x, &mouse.y);
        int ballI, ballJ;
        ballI = (mouse.y-cell.y)/cell.h;
        ballJ = (mouse.x - cell.x)/cell.w ;
        printf("%d,%d\n",ballI, ballJ);

        drawBricks(renderer, bricks, n, m, cell, texture); 
        drawLimits(renderer, cell, m, window_dimensions); 
        ballCollision(ball, cell, bricks, n, m, paddle, &speed);
        gameIsOver = updateScore(&score, &remainingBricks, ball, window_dimensions.h);

        moveBall(&ball, speed);
        drawPaddle(renderer, paddle, texture);
        drawBall(renderer, ball, texture);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
             
        if (!paused) 
        {      
	        SDL_RenderPresent(renderer);  
            SDL_RenderClear(renderer);                        
            //nextIteration(&grid, n, m, rule);             // la vie continue... 
        }
        SDL_Delay(50);                                  
    }
    SDL_DestroyTexture(texture);
}

/**
 * @brief Affiche le casse-briques
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv) 
{
    (void)argc;
    (void)argv;

    SDL_Window       * window = NULL;
    SDL_Renderer     * renderer = NULL;
    SDL_DisplayMode    screen;
    int             ** bricks,
                       n = 3,
                       m = 10;

    /* INITIALISATIONS */

    if (initializeSDL() == false) 
    {
        quitSDL(0, "ERROR SDL INIT", window, renderer);
        exit(EXIT_FAILURE); 
    }

    if(SDL_GetCurrentDisplayMode(0, &screen) != 0)
    {
        quitSDL(0, "ERROR GET_DISPLAY_MODE", window, renderer);
        exit(EXIT_FAILURE); 
    }

    window = SDL_CreateWindow("Minijeu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                screen.w * 0.8, screen.h * 0.8, SDL_WINDOW_RESIZABLE);
    if (window == NULL) 
    {
        quitSDL(0, "ERROR WINDOW CREATION", window, renderer);
        exit(EXIT_FAILURE); 
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) 
    {
        quitSDL(0, "ERROR RENDERER CREATION", window, renderer);
        exit(EXIT_FAILURE); 
    }

    /*TRAITEMENT*/

    bricks = allocGrid(n, m);
    if(bricks)
    {
        bricks = createRandomGrid(bricks, n, m);
        gameLoop(window, renderer, bricks, n, m);
    }

    quitSDL(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}
