#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "fonctions_sdl.h"
#include "level_editor.h"
#include "creationPerso.h"

void showMenu(SDL_Renderer *renderer, SDL_Window* pWindow){
	/* Le fond de la fenêtre sera blanc */
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	//si on met du texte sur des image il faut juste mettre les images avant

	drawImage(renderer, 500, 100, "button.png", 475, 130);
	drawImage(renderer, 500, 250, "button.png", 475, 130);
	drawImage(renderer, 500, 400, "button.png", 475, 130);
	drawImage(renderer, 500, 550, "button.png", 475, 130);

	drawText(renderer, 525, 125, "Nouvelle partie", 25, 12);
	drawText(renderer, 525, 275, "Charger une partie", 25, 12);
	drawText(renderer, 525, 425, "Editeur de la carte", 25, 12);
	drawText(renderer, 525, 575, "Quitter le meilleur jeu du monde", 25, 12);


	/* On fait le rendu ! */
	SDL_RenderPresent(renderer);
		int running = 1;
		while(running==1) {
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
	            //si on est à la hauteur d'une case du sélecteur
	              int pos = mouse_y-100;
								int i=1;
	              for(int j=0; j<pos+150 ;i++, j+=150){
	                if(pos >= j && pos <= j+150) break;
	              }
								switch(i){
									case 1:
										printf("Nouvelle partie\n");
										running = 2;
										break;
									case 2:
										printf("Chargement partie\n");
										//charger une partie
										break;
									case 3:
										printf("Lancement editeur\n");
										running = 4;
										break;
									case 4:
										running=5;
										break;
								}
	            }

	          }
					break;
				}
			}
		}
		if(running==2){
			creerPerso(renderer, pWindow);
		}
		if(running==3){

		}
		if(running==4){
			showEditor(renderer, pWindow, 2, 2);
		}
		if(running==5){
			unloadImages();
			SDL_DestroyWindow(pWindow);
			SDL_DestroyRenderer(renderer);
			TTF_Quit();
			IMG_Quit();
			SDL_Quit();
		}
}
