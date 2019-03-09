#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

int SCREEN_HEIGHT;
int SCREEN_WIDTH;

void drawText (SDL_Renderer *, int , int , char *, int, int);

void drawImage (SDL_Renderer *, int , int , char *, int, int );

void loadImages(SDL_Renderer *);

void unloadImages();

SDL_Window* showWindow();
