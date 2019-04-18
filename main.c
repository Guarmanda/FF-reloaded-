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
#include <quete.h>
#include <inventaire.h>
#include <perso_commun.h>
#include <unistd.h>


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
	create_inventory();
	fill_up_inventory(create_loot(8));
  fill_up_inventory(create_loot(7));
  fill_up_inventory(create_loot(6));
  fill_up_inventory(create_loot(8));
	fill_up_inventory(create_loot(1));
  fill_up_inventory(create_loot(2));
  fill_up_inventory(create_loot(3));
  fill_up_inventory(create_loot(4));
	fill_up_inventory(create_loot(8));
	fill_up_inventory(create_loot(7));
	fill_up_inventory(create_loot(6));
	fill_up_inventory(create_loot(8));
	fill_up_inventory(create_loot(1));
	fill_up_inventory(create_loot(2));
	fill_up_inventory(create_loot(3));
	fill_up_inventory(create_loot(4));
	//on créer le joueur, il choisira certaines de ses statistiques au début de la partie
	Personnage = creation_char();
	init_affichage();
	charger_quetes();
	loadMap("Map.txt");
	showMenu();
    return 0;
}
