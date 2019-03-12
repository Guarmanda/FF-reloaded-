#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <menu_principal.h>
#include <map.h>
#include <fonctions_sdl.h>
#include <creationPerso.h>

/**
 * \fn int main(int argc, char** argv)
 * \brief Main du programme.
 *
 * \param[in] Nombre d'arguments
 * \param[in] Arguments du main
 * \return 0
 */

int main(int argc, char** argv){
	//on créer le joueur, il choisira certaines de se statistiques au début de la partie

	PLAYER = creation_char();
	SDL_Window* pWindow = showWindow();
	SDL_Renderer *renderer=SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	loadImages(renderer);
	//showMenu(renderer, pWindow);
	//setRandomMap();
	loadMap("Map.txt");
	showMenu(renderer, pWindow);
    return 0;
}
