/**
 * \file menu_principal.c
 * \brief Menu principal du jeu
 * \author Karman Nathalie; Papot Alexandre; Girod Valentin
 * \date 12 mars 2019
 *
 * Menu principal
 *
 */
#include <stdio.h>
#include <SDL2/SDL.h>
#include <fonctions_sdl.h>
#include <level_editor.h>
#include <creationPerso.h>
#include <ncurses.h>
#include <map.h>

/**
 * \fn void menu_terminal()
 * \brief Affichage du menu en version terminale
 */
int menu_sdl(){
	fond_blanc();
	//si on met du texte sur des image il faut juste mettre les images avant

	drawImage( 500, 100, "button.png", 475, 130);
	drawImage( 500, 250, "button.png", 475, 130);
	drawImage( 500, 400, "button.png", 475, 130);
	drawImage( 500, 550, "button.png", 475, 130);

	drawText( 525, 125, "Nouvelle partie", 25, 12);
	drawText( 525, 275, "Charger une partie", 25, 12);
	drawText( 525, 425, "Editeur de la carte", 25, 12);
	drawText( 525, 575, "Quitter le meilleur jeu du monde", 25, 12);

	/* On fait le rendu ! */
	faire_rendu();
	int running = -1;
	SDL_Event e;
	while(running==-1) {
			if (SDL_WaitEvent(&e) != 0) {
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
									case 1: running = 0; break; //nouvelle partie
									case 2: break; //charger partie
									case 3: running = 2; break; //editeur carte
									case 4: running=3; break; //quitter jeu
								}
							}

						}
					break;
			}
		}
		//SDL_Delay(80);
	}
	return running;
}


int menu_terminal(){
	int running = -1; //la variable qui gère le choix du menu
	char list[4][30] = { "Nouvelle partie", "Charger une partie", "Editeur de niveaux", "Quitter" };
	char item[30];
	int ch, i = 0, width = 30;
	box( w, 0, 0 ); //initialisation des bordures
	//affichage des boutons
	for( i=0; i<4; i++ ) {
			if( i == 0 )
					wattron( w, A_STANDOUT ); //on surligne le premier
			else
					wattroff( w, A_STANDOUT );
			mvwprintw( w, i+12, 30, "%s", list[i] );
	}
	wrefresh( w ); //mise à jour de l'écran
	running = 0;
	noecho(); //désactivation de l'écho des caratères
	keypad( w, TRUE ); //on autorise à taper des trucs
	curs_set( 0 ); //on cache le curseur du terminal

	//détection de la touche
	while(( ch = wgetch(w)) != '\n'){
					mvwprintw( w, running+12, 30, "%s", list[running] );
					switch( ch ) {
							case KEY_UP:
													running--;
													running = ( running<0 ) ? 3 : running;
													break;
							case KEY_DOWN:
													running++;
													running = ( running>3 ) ? 0 : running;
													break;
					}
					wattron( w, A_STANDOUT );
					mvwprintw( w, running+12, 30, "%s", list[running]);
					wattroff( w, A_STANDOUT );
	}
	return running;
}

/**
 * \fn void showMenu()
 * \brief Gestion et affichage du menu principal
 */
void showMenu(){
	int running; //la variable qui gère le choix du menu
	if(AFFICHAGE == TERMINAL){
		running = menu_terminal();
	}
	else{
		running = menu_sdl();
	}
	if(running==0){
		creerPerso();
	}
	if(running==1){}
	if(running==2) showEditor(500, 500);
	if(running==3){
		if(AFFICHAGE){ //si sdl
			quitter_sdl();
		}
		else{ //si terminal
			curs_set(1);
	    clear();
	    endwin();
		}
	}
}
