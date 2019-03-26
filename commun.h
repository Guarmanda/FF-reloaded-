#ifndef __COMMUN_H__
#define __COMMUN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Definition du type string */
typedef char* string;

/* Definition du type erreur */
typedef int err_t ;

/* Constantes */

const err_t OK;
const err_t KO;

#define TAILLE_STR 32 /*taille par défaut des chaines de char */

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

#define END_OF_GAME 666 /*fin du jeu*/

#endif
