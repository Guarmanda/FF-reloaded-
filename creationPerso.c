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
#include <creationPerso.h>
#include <game.h>

/**
 * \fn void afficher_creation()
 * \brief Fonction d'affichage du menu d'édition de personnage
 */
void afficher_creation(){
	fond_blanc();
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
	char perso[30];
	//on définit le nom de l'image du perso en fonction de ses caractéristiques
	sprintf(perso, "%s_%s_back", PLAYER->class_char, PLAYER->gender);
	drawImage( 350, 125, perso, 200, 200);
	drawText( 375, 375, "Name :", 25, 12);
	drawText( 450, 375, PLAYER->name, 25, 12);
	faire_rendu();
}

/**
 * \fn void creerPerso_terminal()
 * \brief Fonction de gestion de l'édition du personnage en terminal
 */
void creerPerso_terminal(){
	int running = -1; //la variable qui gère le choix du menu
	char classe[4][30] = { "Warrior", "Wizard", "Hunter", "Priest" };
	char genre[2][6] = { "Man", "Woman" };
	char item[30];
	int ch, i = 0, width = 30;
	wclear(w);
	initscr(); // initialize Ncurses
	box( w, 0, 0 ); //initialisation des bordures
	//affichage des boutons
	for( i=0; i<4; i++ ) {
			if( i == 0 )
					wattron( w, A_STANDOUT ); //on surligne le premier
			else
					wattroff( w, A_STANDOUT );
			mvwprintw( w, i+12, 30, "%s", classe[i] );
	}
	for( i=0; i<2; i++ ) {
		if( i == 0 )
				wattron( w, A_STANDOUT ); //on surligne le premier
		else
			wattroff( w, A_STANDOUT );
		mvwprintw( w, i+12, 50, "%s", genre[i] );
	}
	mvwprintw( w, 12, 10, "Nom: %s        ", PLAYER->name);
	mvwprintw( w, 13, 10, "Classe: %s     ", PLAYER->class_char);
	mvwprintw( w, 14, 10, "Genre: %s      ", PLAYER->gender);
	wrefresh( w ); //mise à jour de l'écran
	int classe_ind = 0;
	int genre_ind = 0;
	noecho(); //désactivation de l'écho des caratères
	keypad( w, TRUE ); //on autorise à taper des trucs
	curs_set( 0 ); //on cache le curseur du terminal

	//détection de la touche
	while(( ch = wgetch(w)) != '\n'){
					mvwprintw( w, classe_ind+12, 30, "%s", classe[classe_ind] );
					mvwprintw( w, genre_ind+12, 50, "%s", genre[genre_ind] );
					switch( ch ) {
							case KEY_UP:
													classe_ind--;
													classe_ind = ( classe_ind<0 ) ? 3 : classe_ind;
													break;
							case KEY_DOWN:
													classe_ind++;
													classe_ind = ( classe_ind>3 ) ? 0 : classe_ind;
													break;
							case KEY_LEFT:
													genre_ind--;
													genre_ind = ( genre_ind<0 ) ? 1 : genre_ind;
													break;
							case KEY_RIGHT:
													genre_ind++;
													genre_ind = ( genre_ind>1 ) ? 0 : genre_ind;
													break;
					}
					wattron( w, A_STANDOUT );
					mvwprintw( w, classe_ind+12, 30, "%s", classe[classe_ind]);
					mvwprintw( w, genre_ind+12, 50, "%s", genre[genre_ind]);
					sprintf(PLAYER->class_char,"%s", classe[classe_ind]);
					sprintf(PLAYER->gender, "%s", genre[genre_ind]);
					wattroff( w, A_STANDOUT );
					mvwprintw( w, 12, 10, "Nom: %s        ", PLAYER->name);
					mvwprintw( w, 13, 10, "Classe: %s     ", PLAYER->class_char);
					mvwprintw( w, 14, 10, "Genre: %s      ", PLAYER->gender);
	}
}


/**
 * \fn void creerPerso()
 * \brief Fonction de gestion de l'édition du personnage
 */
void creerPerso(){
	int running;
	if(AFFICHAGE){
		SDL_StartTextInput();
		running = 1;
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
	}
	else{
		creerPerso_terminal();
	}
	startGame( 500.0, 500.0);
}
