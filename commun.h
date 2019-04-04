#ifndef __COMMUN_H__
#define __COMMUN_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  /*fonction sleep nécessaire*/
#include <string.h>
#include <time.h>
#include <ncurses.h>

/* Definition du type string */
typedef char* string;

/* Definition du type erreur */
typedef int err_t ;

/* Constantes */

const err_t OK_state;
const err_t KO_state;

#define map_size_x 1000
#define map_size_y 1000

int position_x;
int position_y;

#define TAILLE_STR 40 /*taille par défaut des chaines de char */
#define TAILLE_TAB_SORT 20
#define MAX_SORTS 7
#define MAX_ETATS 7

int entier_aleatoire(int min, int max);
string creer_string(string string_param);
err_t supprimer_string(string *string_param);
void modifier_string(string *string_old, string string_new);
void viderBuffer();
int lire(char *chaine, int longueur);
/* Definition du type booleen */
typedef enum booleen_s { FAUX , VRAI } booleen_t ;

/* Erreurs !!! à definir au fur et à mesure*/

#define ERR_RAND -110      /*erreur sur les valeurs random*/

#define ERR_DEB_MEMOIRE -100
#define ERR_LISTE_IND_ELEM  -200

int etat_jeu;/*variable globale qui vérifie qu on est bien dans le jeu*/
#define EN_COMBAT VRAI /*pdt le jeu*/
#define END_OF_GAME 666 /*fin du jeu*/

#endif
