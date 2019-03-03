#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "fonctions_sdl.h"

int map[1000][1000];

void showMap(SDL_Renderer *, float, float);
void setRandomMap();
void loadMap(char*);
