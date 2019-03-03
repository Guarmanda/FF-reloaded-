#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "fonctions_sdl.h"
#include "level_editor.h"

void showMenu(SDL_Renderer *renderer, SDL_Window* pWindow){
	/* Le fond de la fenêtre sera blanc */
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	//si on met du texte sur des image il faut juste mettre les images avant

	drawImage(renderer, 500, 100, "button.png");
	drawImage(renderer, 500, 250, "button.png");
	drawImage(renderer, 500, 400, "button.png");
	drawImage(renderer, 500, 550, "button.png");

	drawText(renderer, 525, 125, "Nouvelle partie");
	drawText(renderer, 525, 275, "Charger une partie");
	drawText(renderer, 525, 425, "Editeur de la carte");
	drawText(renderer, 525, 575, "Quitter le meilleur jeu du monde");


	/* On fait le rendu ! */
	SDL_RenderPresent(renderer);
		int running = 1;
		while(running) {
			SDL_Event e;
			while(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT: running = 0;
					break;
					case SDL_MOUSEBUTTONDOWN:
					{
						int mouse_x, mouse_y;
	          SDL_GetMouseState(&mouse_x, &mouse_y);
						//si on est dans la largeur du menu
	          if(mouse_x>500 && mouse_x<975){
							printf("ok1\n");
	            //si on est à la hauteur d'une case du sélecteur
	              int pos = mouse_y-100;
								int i=1;
	              for(int j=0; j<pos+150 ;i++, j+=150){
									printf("i=%d\n", i);
	                if(pos >= j && pos <= j+150) break;
	              }
								printf("ok2 (%d)\n", i);
								switch(i){
									case 1:
										printf("Nouvelle partie\n");
										//commencer une partie
										break;
									case 2:
										printf("Chargement partie\n");
										//charger une partie
										break;
									case 3:
										printf("Lancement editeur\n");
										showEditor(renderer, pWindow, 2, 2);
										break;
									case 4:
										running=0;
										SDL_DestroyWindow(pWindow);
										TTF_Quit();
										SDL_Quit();
										return;
										break;
								}
								printf("ok\n");
	            }

	          }
					break;
				}
			}
		}

	//Destruction de la fenetre
	SDL_DestroyWindow(pWindow);


	TTF_Quit();
		SDL_Quit();
}
