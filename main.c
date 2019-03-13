/**
 * \file main.c
 * \brief Main
 * \author Papot Alexandre, Girod Valentin
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

	PLAYER = creation_char();
	showWindow();
	loadImages();
	charger_quetes();
	//showMenu(renderer, pWindow);
	loadMap("Map.txt");
	showMenu();
    return 0;
}
