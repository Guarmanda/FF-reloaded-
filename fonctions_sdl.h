#include <SDL2/SDL.h>

int SCREEN_HEIGHT; /*!< Hauteur de l'écran en pixels */
int SCREEN_WIDTH; /*!< Largeur de l'écran en pixels */
SDL_Window*pWindow; /*!< Poiteur sur la fenêtre de jeu */
SDL_Renderer*renderer; /*!< Pointeur sur l'état du rendu */
int TERMINAL;
int AFFICHAGE;



void drawText (int , int , char *, int, int);
void drawImage (int , int , char *, int, int );
void loadImages();
void unloadImages();
void showWindow();
