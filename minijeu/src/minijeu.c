#include "minijeu.h"

/**
 * @brief Affiche du texte a l'ecran 
 * 
 * @param text Le texte a afficher
 * @param dest Position et dimensions de destination
 * @param font Police d'ecriture
 * @param renderer Le rendu
 * @return bool_t true si on a reussi, false sinon
 */
bool_t drawText(char *text, SDL_Rect dest, TTF_Font *font, SDL_Renderer *renderer) 
{
    SDL_Color color = {0};
    SDL_Rect source = {0};
    SDL_Texture *texture;
    SDL_Surface *surface;

    color.a = 255;
    color.r = 0;
    color.g = 0;
    color.b = 0;

    surface = TTF_RenderText_Solid(font, text, color);
    if(surface == NULL) {
        fputs("erreur ouverture de la police\n", stderr);
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture == NULL) {
        fputs("erreur transformation de la surface de la police en texture\n", stderr);
        return false;
    }

    SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);
    SDL_RenderCopy(renderer, texture, &source, &dest);
    return true;
}

/**
 * @brief Permet de calculer les dimensions d'une brique par rapport a la taille de la fenetre
 * 
 * @param window la fenetre
 * @param brick la brique (SDL_Rect)
 * @param n nombre de lignes de la grille
 * @param m nombre de colonnes de la grille
 */
void brickDimensions(SDL_Rect * brick, int n, int m, SDL_Rect window_dimensions)
{
    brick->w = (window_dimensions.w * 0.6) / m;
    brick->h = (window_dimensions.h * 0.3) / n ;    
    brick->x = 0 ;
    brick->y = 0 ;
}

/**
 * @brief Affiche les briques
 * 
 * @param renderer Le rendu
 * @param bricks La grille d'entier (represente les briques)
 * @param n Nombre de lignes de la grille
 * @param m Nombre de colonnes de la grille
 * @param brick Dimensions d'une brique
 */
void drawBricks(SDL_Renderer *renderer, int ** bricks, int n, int m, SDL_Rect brick, SDL_Texture *texture) 
{
	int               i,
                      j,
                      poseX,
                      poseY;
	SDL_Rect          dest,
                      source = {0};

    dest.w = brick.w;
    dest.h = brick.h;
    poseX = brick.x;
    poseY = brick.y;
    source.w = 390;
    source.h = 130;
    source.x = 770;
    source.y = 260;

	for(i = 0; i < n; i++) 
    {
		dest.y = poseY + dest.h * i;
		for(j = 0; j < m; j++) 
        {
			dest.x = poseX + dest.w * j;
            if(bricks[i][j] == 1) 
            {
                SDL_RenderCopy(renderer, texture, &source, &dest);
            }
		}
	}
}

/**
 * @brief Calcule les dimensions du paddle
 * 
 * @param paddle Le paddle
 * @param brick Dimensions d'une brique
 * @param m nombre de colonnes de la grille (de briques vu a l'horizontal)
 */
void paddleDimensions(SDL_Rect * paddle, SDL_Rect brick, int m)
{
    paddle->w = brick.w * m * 0.25;
    paddle->h = brick.h * 0.5;
}

/**
 * @brief Affiche le paddle
 * 
 * @param renderer Le rendu
 * @param paddleDest Dimensions du paddle
 * @param texture Texture appliquee au paddle
 */
void drawPaddle(SDL_Renderer * renderer, SDL_Rect paddleDest, SDL_Texture * texture)
{
    SDL_Rect paddleSource = {0};

   	paddleSource.x = 0;
	paddleSource.y = 910;
	paddleSource.w = 347;
	paddleSource.h = 65;
    SDL_RenderCopy(renderer, texture, &paddleSource, &paddleDest);
}

/**
 * @brief Calcule les dimensions de la balle
 * 
 * @param ball La balle
 * @param brick Dimensions d'une brique 
 * @param m Nombre de colonnes de la grille (de briques vu a l'horizontal)
 */
void ballDimensions(SDL_Rect * ball, SDL_Rect brick, int m)
{
    ball->w = brick.w * m * 0.05;
    ball->h = ball->w;
}

/**
 * @brief Affiche la balle
 * 
 * @param renderer Le rendu
 * @param ball La balle
 * @param texture La texture appliquee a la balle
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

/**
 * @brief Dessine les bordure de l'espace jouable
 * 
 * @param renderer Le rendu
 * @param brick Dimensions d'une brique
 * @param m Nombre de colonnes de la grille (de briques vu a l'horizontal)
 * @param window_dimensions Dimensions de la fenetre
 */
void drawLimits(SDL_Renderer *renderer, SDL_Rect brick, int m, SDL_Rect window_dimensions)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, brick.x, brick.y, brick.x, window_dimensions.h);
    SDL_RenderDrawLine(renderer, brick.x, brick.y, brick.x + brick.w * m, brick.y);
    SDL_RenderDrawLine(renderer, brick.x + brick.w * m, brick.y, brick.x + brick.w * m, window_dimensions.h);
}

/**
 * @brief Fait bouger la balle
 * 
 * @param ball La balle
 * @param speed Vitesse de la balle
 */
void moveBall(SDL_Rect *ball, SDL_Rect speed)
{
    ball->x = ball->x + speed.x;
    ball->y = ball->y + speed.y;
}

/**
 * @brief "Casse" une brique
 * 
 * @param bricks La grille des briques (entiers)
 * @param n Nombre de lignes de la grille
 * @param m Nombre de colonnes de la grille
 */
void breakBrick(int *** bricks, int n, int m) 
{
    (*bricks)[n][m] = 0;
}

bool_t ballCollision(SDL_Rect ball, SDL_Rect cell, int *** bricks, int n, int m, SDL_Rect paddle, SDL_Rect * speed)
{
    bool_t brokenBrick = false;
    int leftBall, leftBrick,
        rightBall, rightBrick,
        topBall, topBrick,
        bottomBall, bottomBrick,
        rightWall, leftWall,
        topWall,
        topPaddle;

    leftBall = ball.x + speed->x + cell.x;
    rightBall = ball.x + speed->x + ball.w + cell.x;
    topBall = ball.y + speed->y + cell.y;
    bottomBall = ball.y + speed->y - ball.h + cell.y;

    rightWall = cell.x + cell.w * m;
    leftWall = cell.x;
    topWall = cell.y;

    topPaddle = paddle.y - paddle.h;

    //Collisions murs
    if(leftBall <= leftWall || rightBall > rightWall)
    {
        speed->x = - speed->x;
    }
    //Collisions paddle
    if(topBall >= topPaddle)//&& ball.x >= paddle.x && ball.x <= paddle.x + paddle.w)
    {
        speed->y = - speed->y;
    }
    else
    {
        int ballI, ballJ;
        ballI = (ball.y-cell.y)/cell.h ;
        ballJ = (ball.x - cell.x)/cell.w ;

        //printf("%d, %d\n", ballI, ballJ);
        if(ballI < n && ballI >= 0 && (*bricks)[ballI][ballJ] == 1)
        {   
            leftBrick = cell.x + ballJ * cell.w;
            rightBrick = cell.x + (ballJ + 1) * cell.w;
            topBrick = cell.y + ballI * cell.h;
            bottomBrick = cell.y + (ballI + 1) * cell.h;
            // avec le cote droit d'une brique                                                   
            if(leftBall <= rightBrick)
            {
                speed->x = -speed->x;
            }  // avec le cote gauche d'une brique  
            if(rightBall >= leftBrick)
            {
                speed->x = -speed->x;
            }
            // Avec le bas d'une brique                                                
            if(topBall <= bottomBrick)
            {
                speed->y = -speed->y;
            }
            // Avec le haut d'une brique
            if(bottomBall >= topBrick)
            {
                speed->y = -speed->y;
            }
            breakBrick(bricks, ballI, ballJ);
            brokenBrick = true;
        }
        if(topBall <= topWall) // mur du haut
        {
            speed->y = - speed->y;
        }
        
    }
    return brokenBrick;
}

/**
 * @brief Fait bouger le paddle
 * 
 * @param paddle Le paddle
 * @param brick Dimensions d'une brique
 * @param m Nombre de colonnes de la grille (de briques vu a l'horizontal)
 * @param step Pas pour le mouvement
 */
void movePaddle(SDL_Rect* paddle, SDL_Rect brick, int m, int step) 
{
    int new_x = paddle->x + 20*step;
    if (new_x >= brick.x && new_x < brick.w*m - paddle->w) 
    {
        paddle->x = new_x;
    }
}

/**
 * @brief Met a jour le score de la partie
 * 
 * @param score Le score (entier)
 * @param remainingBricks Le nombre de briques restantes
 * @param ball La balle
 * @param winHeight La hauteur de la fenetre
 * @param brokenBrick Indique si une brique a ete cassee
 * @return bool_t true : la partie est finie, false elle continue
 */
bool_t updateScore(int * score, int * remainingBricks, SDL_Rect ball, int winHeight, bool_t brokenBrick) 
{
    bool_t gameIsOver = false;
    if (ball.y > winHeight)
    {
        gameIsOver = true;
        puts("GAME OVER\n");
    }
    if (brokenBrick) 
    {
        (*score)++;
        (*remainingBricks)--;
    }
    if (*remainingBricks <= 0) 
    {
        gameIsOver = true;
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
void gameLoop(SDL_Window * window, SDL_Renderer * renderer, int ** bricks, int n, int m, int nbBricks, TTF_Font *font, SDL_Texture *texture)
{
    SDL_bool  program_on = SDL_TRUE,                          // Booleen pour dire que le programme doit continuer
              paused = SDL_FALSE;                             // Booleen pour dire que le programme est en pause
    SDL_Rect  mouse = {0},
              cell = {0},
              window_dimensions = {0},
              paddle = {0},
              ball = {0},
              speed = {0};
    
    bool_t gameIsOver = false,
           brokenBrick = false;

    speed.x = 18;
    speed.y = -18;
              
    int score = 0;
    char score_s[15];
    int remainingBricks = nbBricks;
    SDL_Rect text, title;
    

	//SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
	//SDL_QueryTexture(texture, NULL, NULL, NULL/*&paddleSource.w*/, /*&paddleSource.h*/NULL);
    // Initialisation des coordonnees
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    brickDimensions(&cell, n, m, window_dimensions);
    paddleDimensions(&paddle, cell, m);
    ballDimensions(&ball, cell, m);
    paddle.x = (cell.w * m - paddle.w) / 2; 
    paddle.y = window_dimensions.h - paddle.h;
    ball.x = (cell.w * m - ball.w) / 2; 
    ball.y = paddle.y - ball.h;
    title.x = 7 * window_dimensions.w / 10;
    title.y = window_dimensions.h / 10;
    text.x = 6 * window_dimensions.w / 10;
    text.y = window_dimensions.h / 3;
    text.w = window_dimensions.w / 7;
    text.h = window_dimensions.h / 15;
    title.w = window_dimensions.w / 4;
    title.h = window_dimensions.h / 10;

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
                        brickDimensions(&cell, n, m, window_dimensions);
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
                    //Calcul des coordonnees par rapport a l'emplacement du jeu
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
        //printf("%d,%d\n",mouse.x, mouse.y);

        drawBricks(renderer, bricks, n, m, cell, texture); 
        drawLimits(renderer, cell, m, window_dimensions); 
        brokenBrick = ballCollision(ball, cell, &bricks, n, m, paddle, &speed);
        gameIsOver = updateScore(&score, &remainingBricks, ball, window_dimensions.h, brokenBrick);

        moveBall(&ball, speed);
        drawPaddle(renderer, paddle, texture);
        drawBall(renderer, ball, texture);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        sprintf(score_s, "%s%d", "Score : ", score);
        if(!(drawText("CASSE-BRIQUES", title, font, renderer) && drawText(score_s, text, font, renderer))) {
        	SDL_DestroyTexture(texture);
        	quitSDL(0, "(gameloop) Erreur de texture", window, renderer);
        	//sortir proprement
        }
             
        if (!paused) 
        {      
	        SDL_RenderPresent(renderer);  
            SDL_RenderClear(renderer);                        
            //nextIteration(&grid, n, m, rule);             // la vie continue... 
        }
        SDL_Delay(50);                                  
    }
    SDL_DestroyTexture(texture);

    if (remainingBricks == 0) {
        /* GERER VICTOIRE A FAIRE */
    }
    else {
        printf("SCORE : %d\n", score);
        /* GERER DEFAITE A FAIRE */
    }
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

    TTF_Font         *font;
    SDL_Texture      *texture;
    SDL_Window       * window = NULL;
    SDL_Renderer     * renderer = NULL;
    SDL_DisplayMode    screen;
    int             ** bricks,
                       nbBricks,
                       n = 3,
                       m = 10;

    /* INITIALISATIONS */

    if (initializeSDL() == false) 
    {
        quitSDL(0, "ERROR SDL INIT", window, renderer);
        exit(EXIT_FAILURE); 
    }

    if(TTF_Init() != 0) {
        quitSDL(0, "ERROR TTF INIT", window, renderer);
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

    font = TTF_OpenFont("../res/font.ttf", 500);
    if(font == NULL) {
        quitSDL(0, " error font\n", window, renderer);
        exit(EXIT_FAILURE);
    }

	texture = loadTextureFromImage("../res/sprites.png", renderer);
    if(texture == NULL) {
        quitSDL(0, " error texture\n", window, renderer);
        exit(EXIT_FAILURE);
    }

    /*TRAITEMENT*/

    bricks = allocGrid(n, m);
    if(bricks)
    {
        bricks = createRandomGrid(bricks, n, m, &nbBricks);
        gameLoop(window, renderer, bricks, n, m, nbBricks, font, texture);
    }

    TTF_Quit();
    quitSDL(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}