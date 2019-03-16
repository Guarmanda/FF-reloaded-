/**
 * \file creationPerso.c
 * \brief Fonctions d'éditions du personnage
 * \author Karman Nathalie; Papot Alexandre; Girod Valentin
 * \date 12 mars 2019
 *
 * Contient l'affichage et la gestion du menu d'édition du personnage
 *
 */
#include <SDL2/SDL.h>
#include <string.h>
#include <fonctions_sdl.h>
#include <menu_principal.h>
#include <creationPerso.h>
#include <game.h>

/**
 * \fn void afficher_creation()
 * \brief Fonction d'affichage du menu d'édition de personnage
 */
void afficher_creation(){
	SDL_SetRenderDrawColor(renderer, 255,255,255, 255);
	SDL_RenderClear(renderer);
	for(int i=100; i<=550; i+=150){
		drawImage( 700, i, "button.png", 130, 100);
	}

	drawText( 725, 125, "Warrior", 25, 12);
	drawText( 725, 275, "Wizard", 25, 12);
	drawText( 725, 425, "Hunter", 25, 12);
	drawText( 725, 575, "Priest", 25, 12);
	drawText( 500, 650, "Appuyez su entrée pour continuer", 25, 12);

	drawImage( 300, 550, "button.png", 130, 100);
	drawImage( 500, 550, "button.png", 130, 100);

	drawText( 325, 575, "Male", 25, 12);
	drawText( 525, 575, "Female", 25, 12);

	char perso[30] = "";
	strcat(perso, PLAYER->class_char);
	strcat(perso, "_");
	strcat(perso, PLAYER->gender);
	strcat(perso, "_");
	strcat(perso, "back");
	drawImage( 350, 125, perso, 200, 200);
	drawText( 375, 375, "Name :", 25, 12);
	drawText( 450, 375, PLAYER->name, 25, 12);
	SDL_RenderPresent(renderer);
}


/**
 * \fn void creerPerso()
 * \brief Fonction de gestion de l'édition du personnage
 */
void creerPerso(){
	SDL_StartTextInput();
	int running = 1;
	char in[50]="";
	afficher_creation();
	while ( running ==1 ) {
		SDL_Event ev;
		while ( SDL_PollEvent( &ev ) ) {
			if ( ev.type == SDL_TEXTINPUT  ) {
				strcat(in, ev.text.text);
				strcpy(PLAYER->name, in);
				afficher_creation();
			} else if ( ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && strlen(in)) {
				in[strlen(in)-1]='\0';
				strcpy(PLAYER->name, in);
				afficher_creation();
			} else if ( ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE ) {
				running = 2;
			} else if ( ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_RETURN ) {
				running = 3;
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
								afficher_creation();
								break;
							case 2:
								strcpy(PLAYER->class_char, "wizard");
								afficher_creation();
								break;
							case 3:
								strcpy(PLAYER->class_char, "hunter");
								afficher_creation();
								break;
							case 4:
								strcpy(PLAYER->class_char, "priest");
								afficher_creation();
								break;
						}
				}
				if(mouse_x>300 && mouse_x<430 && mouse_y>550 && mouse_y<650){
						strcpy(PLAYER->gender, "man");
						afficher_creation();
				}
				if(mouse_x>500 && mouse_x<630 && mouse_y>550 && mouse_y<650){
						strcpy(PLAYER->gender, "woman");
						afficher_creation();
				}

			}
		}
		SDL_Delay(20);
	}
	SDL_StopTextInput();
	if(running == 2){
		showMenu();
	}
	if(running == 3){
		startGame( 500.0, 500.0);
	}
}
