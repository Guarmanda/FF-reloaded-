#ifndef _MAPMENACE_H_
#define _MAPMENACE_H_
#include <commun.h>


/**
 * \var map_threat[][]
 * \brief carte du jeu mise en global,
 * \details elle contient les chances de tomber en combat en pourcentage
 */
int map_threat[map_size_x][map_size_y]; /* Matrice de la map, contenant les pourcentages de chance de tomber dans un combat*/

/**
 * \def borne_max_village
 * \brief macro qui définit les frontières à droite et en haut du village avec les autres biomes
 */
#define borne_max_village 525
/**
 * \def borne_min_village
 * \brief macro qui définit les frontières à gauche et en bas du village avec les autres biomes
 */
#define borne_min_village 475
/**/
void init_menaces(void);
int est_dans_village(int , int ) ;
int est_dans__biome_terre(int , int ) ;
int est_dans__biome_neige(int , int );
int est_dans__biome_foudre(int , int ) ;
int est_dans__biome_feu(int , int );

#endif
