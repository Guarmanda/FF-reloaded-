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
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <fonctions_sdl.h>
#include <level_editor.h>
#include <creationPerso.h>
#include <ncurses.h>

/**
 * \fn void showMenu()
 * \brief Gestion et affichage du menu principal
 */
void showMenu(){
	int running = -1;
	WINDOW *w;
	if(AFFICHAGE == TERMINAL){
		char list[4][30] = { "Nouvelle partie", "Charger une partie", "Editeur de niveaux", "Quitter" };
		char item[30];
		int ch, i = 0, width = 30;
		initscr(); // initialize Ncurses
		w = newwin( 20, 30, 20, 20 ); // création d'une fenêtre
		box( w, 0, 0 ); //initialisation des bordures
		//affichage des boutons
		for( i=0; i<4; i++ ) {
				if( i == 0 )
						wattron( w, A_STANDOUT ); //on surligne le premier
				else
						wattroff( w, A_STANDOUT );
				mvwprintw( w, i+1, 2, "%s", list[i] );
		}
		wrefresh( w ); // update the terminal screen
		running = 0;
		noecho(); // disable echoing of characters on the screen
		keypad( w, TRUE ); //on autorise à taper des trucs
		curs_set( 0 ); //on cache le curseur du terminal

		//détection de la touche
		while(( ch = wgetch(w)) != '\n'){
						mvwprintw( w, running+1, 2, "%s", list[running] );
						switch( ch ) {
								case KEY_UP:
														running--;
														running = ( i<0 ) ? 3 : running;
														break;
								case KEY_DOWN:
														running++;
														running = ( running>3 ) ? 0 : running;
														break;
						}
						wattron( w, A_STANDOUT );
						mvwprintw( w, running+1, 2, "%s", list[running]);
						wattroff( w, A_STANDOUT );
		}
	}

	else{

		/* Le fond de la fenêtre sera blanc */
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
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
		SDL_RenderPresent(renderer);

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
										case 1:
											printf("Nouvelle partie\n");
											running = 0;
											break;
										case 2:
											printf("Chargement partie\n");
											//charger une partie
											break;
										case 3:
											printf("Lancement editeur\n");
											running = 2;
											break;
										case 4:
											running=3;
											break;
									}
		            }

		          }
						break;
				}
			}
			//SDL_Delay(80);
		}
	}
	if(running==0){
		creerPerso();
	}
	if(running==1){

	}
	if(running==2){
		showEditor(500, 500);
	}
	if(running==3){
		if(AFFICHAGE){
			unloadImages();
			SDL_DestroyWindow(pWindow);
			SDL_DestroyRenderer(renderer);
			TTF_Quit();
			IMG_Quit();
			SDL_Quit();
		}
		else{
			curs_set(1);
	    clear();
	    endwin();
		}
	}
}
