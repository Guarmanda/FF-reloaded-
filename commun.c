#include <stdlib.h>
#include <commun.h>


int entier_aleatoire(int min, int max, int*alea){
	if(min >= max)
		return 1;
	*alea = min+rand()%(max-min);
	return 0;
}
