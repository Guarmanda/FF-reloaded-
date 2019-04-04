/**
 * \file map.c
 * \brief Affichage de la carte autour du joueur
 * \author Girod Valentin Nathalie Karman Alexandre Papot
 * \date 12 mars 2019
 *
 * Contient la fonction de chargement de la carte
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <map.h>
//#include <affichage.h>

/**
 * \fn void loadMap(char* nom)
 * \brief Charge la map depuis un fichier
 * \param[in] Nom du fichier
 */
void loadMap(char* nom){
  FILE*map_file = fopen(nom, "r");
  for(int i=0; i<1000;i++){
    for(int j=0; j<1000; j++){
      int value;
      if(j==999) fscanf(map_file, "%d;\n", &value);
      else fscanf(map_file, "%d;", &value);
      map[i][j] = value;
    }
  }
}
