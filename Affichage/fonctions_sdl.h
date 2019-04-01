#include <SDL2/SDL.h>
#include <ncurses.h>

int SCREEN_HEIGHT; /*!< Hauteur de l'écran en pixels */
int SCREEN_WIDTH; /*!< Largeur de l'écran en pixels */
int SPRITE_W; /*!< Largeur d'un sprite */
SDL_Window*pWindow; /*!< Poiteur sur la fenêtre de jeu */
SDL_Renderer*renderer; /*!< Pointeur sur l'état du rendu */
int TERMINAL;
int AFFICHAGE;
WINDOW *w; //la fenêtre pour l'affichage terminal


void drawText (int , int , char *, int, int);
void drawImage (int , int , char *, int, int );
void loadImages();
void unloadImages();
void showWindow();
void fond_blanc();
void faire_rendu();
void quitter_sdl();
