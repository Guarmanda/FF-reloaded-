
#include "commun.h"

/* Definition du type string */




#define borne_max_village 535
#define borne_min_village 465
/**/
void init_menaces(void);
int est_dans_village(int , int ) ;
int est_dans__biome_terre(int , int ) ;
int est_dans__biome_neige(int , int );
int est_dans__biome_foudre(int , int ) ;
int est_dans__biome_feu(int , int );

int ** getMapThreat();