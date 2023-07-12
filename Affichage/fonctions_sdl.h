#include "SDL2/include/SDL2/SDL.h"
void drawText (int , int , char *, int, int);
void drawImage (int , int , char *, int, int );
void loadImages();
void unloadImages();
void showWindow();
void fond_blanc();
void faire_rendu();
void quitter_sdl();

int getScreenHeight();

int getScreenWidth();

int getSpriteW();

SDL_Window* getWindow();

SDL_Renderer* getRenderer();

void * getFenetre();
float getVitessePerso();

void setVitessePerso(float vitesse);


