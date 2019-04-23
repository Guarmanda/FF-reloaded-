#include <commun.h>
/* Definition du type string */

int map_threat[1000][1000]; /* Matrice de la map, contenant les pourcentages de chance de tomber dans un combat*/


#define borne_max_village 535
#define borne_min_village 465
/**/
void init_menaces(void);
int est_dans_village(int , int ) ;
int est_dans__biome_terre(int , int ) ;
int est_dans__biome_neige(int , int );
int est_dans__biome_foudre(int , int ) ;
int est_dans__biome_feu(int , int );
