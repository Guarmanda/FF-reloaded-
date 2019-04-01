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
	Inventaire = create_or_delete_inventory();
	fill_up_inventory(Inventaire, create_object(8));
  fill_up_inventory(Inventaire, create_object(7));
  fill_up_inventory(Inventaire, create_object(6));
  fill_up_inventory(Inventaire, create_object(8));
	fill_up_inventory(Inventaire, create_object(1));
  fill_up_inventory(Inventaire, create_object(2));
  fill_up_inventory(Inventaire, create_object(3));
  fill_up_inventory(Inventaire, create_object(4));
	fill_up_inventory(Inventaire, create_object(8));
	fill_up_inventory(Inventaire, create_object(7));
	fill_up_inventory(Inventaire, create_object(6));
	fill_up_inventory(Inventaire, create_object(8));
	fill_up_inventory(Inventaire, create_object(1));
	fill_up_inventory(Inventaire, create_object(2));
	fill_up_inventory(Inventaire, create_object(3));
	fill_up_inventory(Inventaire, create_object(4));
	init_affichage();

	//on créer le joueur, il choisira certaines de ses statistiques au début de la partie
	PLAYER = creation_char();
	charger_quetes();
	loadMap("Map.txt");
	showMenu();
    return 0;
}
