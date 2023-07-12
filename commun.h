
#ifndef COMMUN_H
#define COMMUN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  /*fonction sleep nécessaire*/
#include <string.h>
#include <time.h>

/**
 * \def string
 * \brief définit le type char* en tant que \a string
 */
/* Definition du type string */
typedef char* string;

/* Constantes */

#define OK_state 1
#define KO_state 0

/**
 * \def map_size_x
 * \brief taille de la map coordonnée x
 */
#define map_size_x 1000
/**
 * \def map_size_y
 * \brief taille de la map coordonnée y
 */
#define map_size_y 1000
/**
 * \def TAILLE_STR
 * \brief taille par défaut des \a char* qui sont pas allouées dynamiquement
 */
#define TAILLE_STR 50 /*taille par défaut des chaines de char */

/**
 * \def MAX_ETATS
 * \brief nombre max d'états physiques et psychologiques que les personnages peuvent avoir
 */
#define MAX_ETATS 7

/*---------------------------variables globales-----------------------*/
/**
 * \var position_x
 * \brief position x du joueur en global
 */
//int position_x;
/**
 * \var position_y
 * \brief position y du joueur en global
 */
//int position_y;

int entier_aleatoire(int min, int max);
void clear_screen(void);

/*manipulation des chaines de caractère et saisie au clavier*/
int creer_string(string* , string);
int supprimer_string(string *string_param);
void viderBuffer();
int lire(char *chaine, int longueur);

/* Definition du type booleen */
typedef enum booleen_s { FAUX , VRAI } booleen_t ;


#define ERR_RAND -110      /*erreur sur les valeurs random*/

#define ERR_DEB_MEMOIRE -100
#define ERR_LISTE_IND_ELEM  -200

/*----------------------------les define qui sont utilisés par etat_jeu-------------------------- */
/**
 * \def EN_COMBAT
 * \brief définit l'état du jeu comme étant en combat
 */
#define EN_COMBAT VRAI /*pdt le jeu*/
/**
 * \def HORS_COMBAT
 * \brief définit l'état du jeu comme étant dans le jeu mais pas en combat
 */
#define HORS_COMBAT FAUX /*pdt le jeu*/
/**
 * \def END_OF_GAME
 * \brief définit la fin du jeu et le retour sur l'écran d'accueil
 */
#define END_OF_GAME 666 /*fin du jeu*/

#endif
