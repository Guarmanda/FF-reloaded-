#ifndef __COMMUN_H__
#define __COMMUN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Constantes */

#define TAILLE_STR 32 /*taille par défaut des chaines de char */

int entier_aleatoire(int min, int max, int* alea);


/* Definition du type booleen */
typedef enum booleen_s { FAUX , VRAI } booleen_t ;

/* Definition du type erreur */
typedef int err_t ;
/* Erreurs !!! à definir plus tard*/
#define OK 0
#define ERR_DEB_MEMOIRE -100
#define ERR_LISTE_IND_ELEM  -200






#endif
