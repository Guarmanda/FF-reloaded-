/**
 * \file creationPerso.c
 * \brief Fonctions d'éditions du personnage
 * \author Karman Nathalie; Papot Alexandre; Girod Valentin
 * \date 12 mars 2019
 *
 * Contient l'affichage et la gestion du menu d'édition du personnage
 *
 */
#include <affichage.h>
#include <creationPerso.h>
#include <game.h>

/**
 * \fn void creerPerso()
 * \brief Fonction de gestion de l'édition du personnage
 */
void creerPerso(){
	afficher_creation(PLAYER->name, PLAYER->class_char, PLAYER->gender);
	startGame( 500.0, 500.0);
}
