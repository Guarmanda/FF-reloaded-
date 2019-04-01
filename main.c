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
#include <fonctions_affichage.h>
#include <creationPerso.h>
#include <quete.h>
#include <inventaire.h>


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
	//on initialise l'affichage. Selon qu'on lance le programme terminal ou le programme sdl,
	//le programme aura été compilé avec les fonctions correspondantes.
	init_affichage();
	inventaire = create_or_delete_inventory();
	//on créer le joueur, il choisira certaines de ses statistiques au début de la partie
	PLAYER = creation_char();
	charger_quetes();
	loadMap("Map.txt");
	showMenu();
    return 0;
}
