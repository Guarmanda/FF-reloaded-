#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "menu_principal.h"
#include "fonctions_sdl.h"

int main(int argc, char** argv)
{
	SDL_Window* pWindow = showWindow();
	showMenu(pWindow);
	printf("hey");
    return 0;
}
