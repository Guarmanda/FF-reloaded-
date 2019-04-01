#include <stdlib.h>
#include <commun.h>


int entier_aleatoire(int min, int max){

		if(min >= max)
			return 0;
		return min + rand() % (max-min);

}
