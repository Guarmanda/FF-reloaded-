/**
 * \file map.c
 * \brief Affichage de la carte autour du joueur
 * \author Girod Valentin
 * \date 12 mars 2019
 *
 * Contient la fonction de chargement de la carte
 *
 */
#include <stdio.h>
#include "map.h"
#include <stdlib.h>

//#include <affichage.h>

int ** map; /*!< Matrice de la map, contenant les valeurs des sprites (0 à 6) */
//les coordonnees du joueur, accessibles de n'importe
float X; /*!< Abscisse du joueur pour usage externe (quêtes, monstres,...) */
float Y; /*!< Ordonnée du joueur pour usage externe */

int ** getMap(){
  return map;
}

float getX(){
  return X;
}

float getY(){
  return Y;
}

void setX(float x){
  X = x;
}

void setY(float y){
  Y = y;
}


/**
 * \fn void loadMap(char* nom)
 * \brief Charge la map depuis un fichier
 * \param[in] Nom du fichier
 */
void loadMap(char* nom){
  //log
  printf("Chargement de la map...\n");
  map =  (int **)malloc(1000 * sizeof(int*));
  for(int i = 0; i < 1000; i++) map[i] = (int *)malloc(1000 * sizeof(int));
  FILE*map_file = fopen(nom, "r");
  for(int i=0; i<1000;i++){
    for(int j=0; j<1000; j++){
      int value;
      if(j==999) fscanf(map_file, "%d;\n", &value);
      else fscanf(map_file, "%d;", &value);
      map[i][j] = value;
    }
  }
  printf("Chargement de la map terminé\n");
}
