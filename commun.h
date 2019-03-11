#include <stdio.h>
#include <stdlib.h>
/*commande github pour push*/
#include <outils.h>
/* Definition du type booleen */
typedef enum booleen_s { FAUX , VRAI } booleen_t ;

/* Definition du type erreur */
typedef int err_t ;

/* Constantes */

#define TAILLE 32

/* Erreurs */
#define OK 0

#define ERR_DEB_MEMOIRE -100

#define ERR_LISTE_IND_ELEM  -200
