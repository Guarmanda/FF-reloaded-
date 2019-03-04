#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

int SCREEN_HEIGHT;
int SCREEN_WIDTH;

void drawText (SDL_Renderer *, int , int , char *);

void drawImage (SDL_Renderer *, int , int , char * );

void loadImages(SDL_Renderer *);

SDL_Window* showWindow();
