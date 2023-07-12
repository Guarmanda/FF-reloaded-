/**
 * \file menu_principal.c
 * \brief Menu principal du jeu
 * \author Girod Valentin
 * \date 12 mars 2019
 *
 * Menu principal
 *
 */
#include <affichage.h>
#include "level_editor.h"
#include <fonctions_affichage.h>
#include "game.h"


/**
 * \fn void showMenu()
 * \brief Gestion et affichage du menu principal
 */
void showMenu(){
	setPersonnage(creation_char());
	character_t * Personnage = getPersonnage();
	fond_blanc();
	int running; //la variable qui gère le choix du menu
	char list[4][30] = { "Nouvelle partie", "Charger une partie", "Editeur de niveaux", "Quitter" };
	running = afficher_menu(list);
	if(running==0){
		printf("Nouvelle partie\n");
		init_menaces();
		printf("menaces init\n");
	  init_tab_sort();
		printf("sorts init\n");
		printf("name: %s\n", Personnage->name);
		printf("class: %s\n", Personnage->class_char);
		printf("gender: %s\n", Personnage->gender);
		afficher_creation(Personnage->name, Personnage->class_char, Personnage->gender);
		printf("creation affichee\n");
		startGame( 500.0, 500.0);
	}
	if(running==1){}
	if(running==2) showEditor(500, 500);
	if(running==3){
		delete_player(&Personnage);
	  suppr_tab_sort();
		quitter_affichage();
	}
}
