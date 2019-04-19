/**
 * \file map_menace.c
 * \brief map qui génère les chances, en pourcentage, d'être attaqué
 * \author Karman Nathalie, Papot Alexandre
 * \date 29 avril 2019
 *
 *
 *
 */
 #include <map_menace.h>

 /**
  * \fn int est_dans_village(int x, int y)
  * \brief vérifie les coordonnées du joueur : si il est dans la zone du village
  * \param[in] x, coord x
  * \param[in] y, coord y
  * \return 1 si c est vrai, sinon 0
  */
int est_dans_village(int x, int y) {
   return ( (x >= borne_min_village && x <= borne_max_village) && (y >= borne_min_village &&  y <= borne_max_village) );
}
/**
 * \fn int est_dans__biome_terre(int x, int y)
 * \brief vérifie les coordonnées du joueur : si il est en bas à droite
 * \param[in] x, coord x
 * \param[in] y, coord y
 * \return 1 si c est vrai, sinon 0
 */
int est_dans__biome_terre(int x, int y) {    /* partie en bas à droite */
   return ( x >= 500 &&  y < 500);
}
/**
 * \fn int est_dans__biome_neige(int x, int y)
 * \brief vérifie les coordonnées du joueur : si il est en bas à gauche
 * \param[in] x, coord x
 * \param[in] y, coord y
 * \return 1 si c est vrai, sinon 0
 */
int est_dans__biome_neige(int x, int y){  /* partie en bas à gauche */
   return ( x < 500 &&  y <= 500);
}
/**
 * \fn int est_dans__biome_feu(int x, int y)
 * \brief vérifie les coordonnées du joueur : si il est en haut à droite
 * \param[in] x, coord x
 * \param[in] y, coord y
 * \return 1 si c est vrai, sinon 0
 */
int est_dans__biome_feu(int x, int y) { /*en haut à droite*/
   return ( x >= 500 &&  y >= 500);
}
/**
 * \fn int est_dans__biome_foudre(int x, int y)
 * \brief vérifie les coordonnées du joueur : si il est en haut à gauche
 * \param[in] x, coord x
 * \param[in] y, coord y
 * \return 1 si c est vrai, sinon 0
 */
int est_dans__biome_foudre(int x, int y) {  /*en haute à gauche*/
   return ( x < 500 &&  y > 500);
}


/**
 * \fn void init_menaces()
 * \brief initialise le tableau global des menaces en pourcentage
 * \param[in] void
 */
void init_menaces(){

   int i,j;

   for(i=0; i<1000; i++){
      for(j=0; j<1000; j++){

         if(est_dans_village(i,j))
            map_threat[i][j]=0;
         else if(est_dans__biome_terre(i,j) && !est_dans_village(i,j) )
            map_threat[i][j]=50;
          else if(est_dans__biome_feu(i,j) && !est_dans_village(i,j))
             map_threat[i][j]=60;
          else if(est_dans__biome_neige(i,j) && !est_dans_village(i,j))
            map_threat[i][j]=70;
         else if(est_dans__biome_foudre(i,j) && !est_dans_village(i,j))
            map_threat[i][j]=80;

      }
   }

}
