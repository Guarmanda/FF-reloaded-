/**
 * \file map.c
 * \brief Affichage de la carte autour du joueur
 * \author Girod Valentin
 * \date 12 mars 2019
 *
 * Contient les fonctions de chargement et d'affichage de la carte
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fonctions_sdl.h>
#include <creationPerso.h>
#include <map.h>


/**
 * \fn void showMap(float x, float y)
 * \brief Gère l'affichage de la map et du joueur
 * \param[in] Abscisse du joueur
 * \param[in] Ordonnée du joueur
 */
void showMap(float x, float y){
  //le nombre de sprites à afficher, tout comme la position du joueur, dépend de la taille de l'écran
  float nbSpriteX = SCREEN_WIDTH/125;
  float nbSpriteY = SCREEN_HEIGHT/125;

  //on veux savoir quelle sprite de joueur afficher
  char sprite[30] = "";
	strcat(sprite, PLAYER->class_char);
	strcat(sprite, "_");
	strcat(sprite, PLAYER->gender);
	strcat(sprite, "_");
  if (X>x) strcat(sprite, "left");
  else if (X<x) strcat(sprite, "right");
  else if (Y>y) strcat(sprite, "forward");
  else if (Y<y) strcat(sprite, "back");
  else strcat(sprite, "back");

  //on rend accessible les nouvelles coordonnées du joueur pour les monstres/quetes
  X=x;
  Y=y;

  //il faut empêcher tout débordement de la map
  float x_player=x;
  float y_player=y;
  if(y_player>=nbSpriteY/2) y_player = nbSpriteY/2;
  if(x_player>=nbSpriteX/2) x_player = nbSpriteX/2;

  if(y-nbSpriteY/2<0) y=nbSpriteY/2;
  if(x-nbSpriteX/2<0) x=nbSpriteX/2;
  if(y+nbSpriteY/2+2>999) y=999-(nbSpriteY/2+2);
  if(x+nbSpriteX/2+2>999) x=999-(nbSpriteX/2+2);

  //puis afficher la portion de la map ou le joueur est présent
  for(int i=y-nbSpriteY/2; i<y+(nbSpriteY/2)+2;i++){
    for(int j=x-nbSpriteX/2; j<x+(nbSpriteX/2)+2; j++){
        float x2 = j-(x-nbSpriteX/2);
        float y2 = i-(y-nbSpriteY/2);
      //chaque nombre dans la matrice corresponds à une sprite
      switch(map[i][j]){
        //avant d'afficher le joueur, on gère tout ce qui passe sous ses pieds
        case 5:
              drawImage( x2*125, y2*125, "map_grass.png", 125, 125); break;
        case 1:
              drawImage( x2*125, y2*125, "map_grass.png", 125, 125);
              drawImage( x2*125, y2*125, "map_tree1.png", 125, 125); break;
        case 3:
              drawImage( x2*125, y2*125, "map_grass.png", 125, 125);
              drawImage( x2*125, y2*125, "map_tree2.png", 125, 125); break;
        case 6:
              drawImage( x2*125, y2*125, "map_grass.png", 125, 125);
              drawImage( x2*125, y2*125, "map_house.png", 125, 125); break;
        case 2:
              drawImage( x2*125, y2*125, "map_water.png", 125, 125);
              drawImage( x2*125, y2*125, "map_grass_water.png", 125, 125); break;
        //gestion des routes et virages
        case 4: drawImage( x2*125, y2*125, "map_path.png", 125, 125);
                if(map[i-1][j] == 4 && map[i+1][j]==4 && map[i][j+1]==4 && map[i][j-1]==4){
                  break;}
                if(map[i-1][j] == 4 && map[i+1][j]==4 && map[i][j+1]==4){
                  drawImage( x2*125, y2*125, "map_grass_path6.png", 125, 125);}
                else if(map[i-1][j] == 4 && map[i+1][j]==4 && map[i][j-1]==4){
                  drawImage( x2*125, y2*125, "map_grass_path4.png", 125, 125);}
                else if(map[i][j-1] == 4 && map[i][j+1]==4 && map[i-1][j]==4){
                  drawImage( x2*125, y2*125, "map_grass_path5.png", 125, 125);}
                else if(map[i][j-1] == 4 && map[i][j+1] ==4 && map[i+1][j]==4){
                  drawImage( x2*125, y2*125, "map_grass_path3.png", 125, 125);}
                else if(map[i][j-1] == 4 && map[i][j+1]==4){
                  drawImage( x2*125, y2*125, "map_grass_path2.png", 125, 125);}
                else if(map[i-1][j] == 4 && map[i+1][j]==4){
                  drawImage( x2*125, y2*125, "map_grass_path1.png", 125, 125);}
                else if(map[i][j+1] == 4 && map[i+1][j]==4){
                  drawImage( x2*125, y2*125, "map_grass_path7.png", 125, 125);}
                else if(map[i][j-1] == 4 && map[i-1][j]==4){
                  drawImage( x2*125, y2*125, "map_grass_path9.png", 125, 125);}
                else if(map[i-1][j] == 4 && map[i][j+1]==4){
                  drawImage( x2*125, y2*125, "map_grass_path10.png", 125, 125);}
                else if(map[i][j-1] == 4 && map[i+1][j]==4){
                  drawImage( x2*125, y2*125, "map_grass_path8.png", 125, 125);}
                break;
      }
    }
  }
  //puis on affiche le joueur si il est aux mêmes coordonnée
  drawImage( (x_player*125+(x-(int)x))-30, (y_player*125+(y-(int)y))-30, sprite, 60,60);

}


/*void setRandomMap(){
  time_t t;
  srand((unsigned) time(&t));
  for(int i=0; i<1000;i++){
    for(int j=0; j<1000; j++){
      //map[i][j]=rand()%6+1;
      map[i][j]=5;
    }
  }
}*/

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
