#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include "fonctions_sdl.h"
#include "menu_principal.h"
#include "creationPerso.h"

#define true 1
#define false 0

//affichage de toute la création de perso
void afficher_creation(SDL_Renderer * renderer){
	SDL_SetRenderDrawColor(renderer, 255,255,255, 255);
	SDL_RenderClear(renderer);
	for(int i=100; i<=550; i+=150){
		drawImage(renderer, 700, i, "button.png", 130, 100);
	}

	drawText(renderer, 725, 125, "Warrior", 25, 12);
	drawText(renderer, 725, 275, "Wizard", 25, 12);
	drawText(renderer, 725, 425, "Hunter", 25, 12);
	drawText(renderer, 725, 575, "Priest", 25, 12);

	drawImage(renderer, 300, 550, "button.png", 130, 100);
	drawImage(renderer, 500, 550, "button.png", 130, 100);

	drawText(renderer, 325, 575, "Male", 25, 12);
	drawText(renderer, 525, 575, "Female", 25, 12);

	char perso[30] = "";
	strcat(perso, PLAYER->class_char);
	strcat(perso, "_");
	strcat(perso, PLAYER->sex);
	strcat(perso, "_");
	strcat(perso, "back");
	drawImage(renderer, 350, 125, perso, 200, 200);
	drawText(renderer, 375, 375, "Name :", 25, 12);
	drawText(renderer, 450, 375, PLAYER->name, 25, 12);
	SDL_RenderPresent(renderer);
}


//gestion du menu de création de personnage
int creerPerso(SDL_Renderer * renderer, SDL_Window* pWindow){
	SDL_StartTextInput();
	int running = true;
	char in[50]="";
	afficher_creation(renderer);
	while ( running ) {
		SDL_Event ev;
		while ( SDL_PollEvent( &ev ) ) {
			if ( ev.type == SDL_TEXTINPUT  ) {
				strcat(in, ev.text.text);
				strcpy(PLAYER->name, in);
				afficher_creation(renderer);
			} else if ( ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && strlen(in)) {
				in[strlen(in)-1]='\0';
				strcpy(PLAYER->name, in);
				afficher_creation(renderer);
			} else if ( ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE ) {
				running = false;
			}
			if(ev.type== SDL_MOUSEBUTTONDOWN)
			{
				int mouse_x, mouse_y;
				SDL_GetMouseState(&mouse_x, &mouse_y);
				//si on est dans la largeur du menu
				if(mouse_x>700 && mouse_x<830){
					//si on est à la hauteur d'une case du sélecteur
						int pos = mouse_y-100;
						int i=1;
						for(int j=0; j<pos+150 ;i++, j+=150){
							if(pos >= j && pos <= j+150) break;
						}
						switch(i){
							case 1:
								strcpy(PLAYER->class_char, "warrior");
								afficher_creation(renderer);
								break;
							case 2:
								strcpy(PLAYER->class_char, "wizard");
								afficher_creation(renderer);
								break;
							case 3:
								strcpy(PLAYER->class_char, "hunter");
								afficher_creation(renderer);
								break;
							case 4:
								strcpy(PLAYER->class_char, "priest");
								afficher_creation(renderer);
								break;
						}
				}
				if(mouse_x>300 && mouse_x<430 && mouse_y>550 && mouse_y<650){
						strcpy(PLAYER->sex, "man");
						afficher_creation(renderer);
				}
				if(mouse_x>500 && mouse_x<630 && mouse_y>550 && mouse_y<650){
						strcpy(PLAYER->sex, "woman");
						afficher_creation(renderer);
				}

			}
		}
}

SDL_StopTextInput();
showMenu(renderer, pWindow);
}
