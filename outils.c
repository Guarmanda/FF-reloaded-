#include <stdlib.h>
#include "outils.h"

/**
 * \fn int_aleatoire(int min, int max, int*alea)
 * \brief Fonction qui affecte une valeur aleatoire comprise entre deux valeurs entieres
 * \param[in] Entier minimum
 * \param[in] Entier maximum
 * \param[out] Pointeur sur entier, recevra la valeur aleatoire
 */

int int_aleatoire(int min, int max, int*alea){
	if(min >= max)
		return 1;
	*alea = min+rand()%(max-min);
	return 0;
}
