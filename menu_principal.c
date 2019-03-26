/**
 * \file menu_principal.c
 * \brief Menu principal du jeu
 * \author Karman Nathalie; Papot Alexandre; Girod Valentin
 * \date 12 mars 2019
 *
 * Menu principal
 *
 */
#include <affichage.h>
#include <level_editor.h>
#include <creationPerso.h>
#include <fonctions_affichage.h>

/**
 * \fn void showMenu()
 * \brief Gestion et affichage du menu principal
 */
void showMenu(){
	fond_blanc();
	int running; //la variable qui gère le choix du menu
	char list[4][30] = { "Nouvelle partie", "Charger une partie", "Editeur de niveaux", "Quitter" };
	running = afficher_menu(list);
	if(running==0){
		creerPerso();
	}
	if(running==1){}
	if(running==2) showEditor(500, 500);
	if(running==3){
		quitter_affichage();
	}
}
