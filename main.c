#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "menu_principal.h"
#include "map.h"
#include "level_editor.h"
#include "fonctions_sdl.h"

int main(int argc, char** argv)
{
	SDL_Window* pWindow = showWindow();
	SDL_Renderer *renderer=SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	loadImages(renderer);
	//showMenu(renderer, pWindow);
	//setRandomMap();
	loadMap("Map.txt");
	showMenu(renderer, pWindow);
    return 0;
}
