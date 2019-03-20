/**
 * \file main.c
 * \brief Main
 * \author Karman Nathalie, Papot Alexandre, Girod Valentin
 * \date 12 mars 2019
 *
 * Démmarre le jeu
 *
 */
#include <stdio.h>
#include <menu_principal.h>
#include <map.h>
#include <fonctions_sdl.h>
#include <creationPerso.h>
#include <quete.h>
#include <fonctions_terminal.h>


/**
 * \fn int main(int argc, char** argv)
 * \brief Main du programme.
 *
 * \param[in] Nombre d'arguments
 * \param[in] Arguments du main
 * \return 0
 */
int main(int argc, char** argv)
{
	//on créer le joueur, il choisira certaines de ses statistiques au début de la partie
	AFFICHAGE = 1;
	for(int i = 0; i< argc; i++){
		printf("%s\n", argv[i]);
	}
	if(argc == 2 && strcmp(argv[1], "-terminal") == 0){
		AFFICHAGE = 0;
		initscr(); // initialize Ncurses
		w = newwin( 24, 80, 0, 0 ); // création d'une fenêtre
		//initialisation des couleurs terminal
		if (has_colors() == FALSE) {
        endwin();
        puts("Vottre terminal ne supporte pas les couleurs");
        exit(1);
    }
    start_color();
    init_colorpairs();
		SCREEN_WIDTH = 80;
		SCREEN_HEIGHT = 24;
		SPRITE_W = 1;
	}
	else{
		showWindow();
		loadImages();
		SPRITE_W = 125;
	}
	PLAYER = creation_char();
	charger_quetes();
	//showMenu(renderer, pWindow);
	loadMap("Map.txt");
	showMenu();
    return 0;
}
