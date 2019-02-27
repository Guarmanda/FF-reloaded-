#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "fonctions_sdl.h"

void showMenu(SDL_Window* pWindow){
	//Le pointeur vers la surface incluse dans la fenetre
	SDL_Renderer *renderer=SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	// Le pointeur vers notre police

	if( pWindow )
	{
		int running = 1;
		while(running) {
			SDL_Event e;
			while(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT: running = 0;
					break;
					case SDL_WINDOWEVENT:
						switch(e.window.event){
							case SDL_WINDOWEVENT_EXPOSED:
							case SDL_WINDOWEVENT_SIZE_CHANGED:
							case SDL_WINDOWEVENT_RESIZED:
							case SDL_WINDOWEVENT_SHOWN:
								/* Le fond de la fenêtre sera blanc */
								SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
								SDL_RenderClear(renderer);
								//si on met du texte sur des image il faut juste mettre les images avant

								drawImage(renderer, 500, 150, "button.png");
								drawImage(renderer, 500, 300, "button.png");
								drawImage(renderer, 500, 450, "button.png");

								drawText(renderer, 525, 175, "Nouvelle partie");
								drawText(renderer, 525, 325, "Charger une partie");
								drawText(renderer, 525, 475, "Quitter le meilleur jeu du monde");


								/* On fait le rendu ! */
								SDL_RenderPresent(renderer);
							break;
						}
					break;
					case SDL_MOUSEBUTTONDOWN:

						drawText(renderer, 50, 50, "Je détecte les clicks, sa mère");
						SDL_RenderPresent(renderer);
					break;
				}
			}
		}
	}

	//Destruction de la fenetre
	SDL_DestroyWindow(pWindow);


	TTF_Quit();
		SDL_Quit();
}
