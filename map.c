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
#include <ncurses.h>
#include <fonctions_terminal.h>


/**
 * \fn void showMap(float x, float y)
 * \brief Gère l'affichage de la map et du joueur en SDL
 * \param[in] Abscisse du joueur
 * \param[in] Ordonnée du joueur
 */
void showMap_sdl(float x, float y){
  //le nombre de sprites à afficher, tout comme la position du joueur, dépend de la taille de l'écran
  float nbSpriteX = SCREEN_WIDTH/SPRITE_W;
  float nbSpriteY = SCREEN_HEIGHT/SPRITE_W;

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
      char sprite1[40] = ""; //on définit le nom du sprite de couche inférieure
      char sprite2[40] = ""; //et celui de couche supérieure
      switch(map[i][j]){
        //avant d'afficher le joueur, on gère tout ce qui passe sous ses pieds
        case 5: sprintf(sprite1, "map_grass.png"); break;
        case 1: sprintf(sprite1, "map_grass.png");
                sprintf(sprite2, "map_tree1.png"); break;
        case 3: sprintf(sprite1, "map_grass.png");
                sprintf(sprite2, "map_tree2.png"); break;
        case 6: sprintf(sprite1, "map_grass.png");
                sprintf(sprite2, "map_house.png"); break;
        case 2: sprintf(sprite1, "map_water.png");
                sprintf(sprite2, "map_grass_water.png"); break;
        //gestion des routes et virages
        case 4: sprintf(sprite1, "map_path.png");
                if(map[i-1][j] == 4 && map[i+1][j]==4 && map[i][j+1]==4 && map[i][j-1]==4) break;
                char path = ' ';
                if(map[i-1][j] == 4 && map[i+1][j]==4 && map[i][j+1]==4){
                  path = '6';
                }else if(map[i-1][j] == 4 && map[i+1][j]==4 && map[i][j-1]==4){
                  path = '4';
                }else if(map[i][j-1] == 4 && map[i][j+1]==4 && map[i-1][j]==4){
                  path = '5';
                }else if(map[i][j-1] == 4 && map[i][j+1] ==4 && map[i+1][j]==4){
                  path = '3';
                }else if(map[i][j-1] == 4 && map[i][j+1]==4){
                  path = '2';
                }else if(map[i-1][j] == 4 && map[i+1][j]==4){
                  path = '1';
                }else if(map[i][j+1] == 4 && map[i+1][j]==4){
                  path = '7';
                }else if(map[i][j-1] == 4 && map[i-1][j]==4){
                  path = '9';
                }else if(map[i-1][j] == 4 && map[i][j+1]==4){
                  path = '0';
                }else if(map[i][j-1] == 4 && map[i+1][j]==4){
                  path = '8';
                }
                if(path != ' '){
                  sprintf(sprite2, "map_grass_path%c", path);
                }
                break;
      }
      //on affiche les sprites
      drawImage( x2*SPRITE_W, y2*SPRITE_W, sprite1, SPRITE_W, SPRITE_W);
      if(sprite2[0]){
        //on affiche le deuxieme sprite si il existe
        drawImage( x2*SPRITE_W, y2*SPRITE_W, sprite2, SPRITE_W, SPRITE_W);
      }
    }
  }
  //puis on affiche le joueur si il est aux mêmes coordonnée
  drawImage( (x_player*SPRITE_W+(x-(int)x))-30, (y_player*SPRITE_W+(y-(int)y))-30, sprite, 60,60);

}

/**
 * \fn void showMap(float x, float y)
 * \brief Gère l'affichage de la map et du joueur en terminal
 * \param[in] Abscisse du joueur
 * \param[in] Ordonnée du joueur
 */
void showMap_terminal(float x, float y){
  //on rend accessible les nouvelles coordonnées du joueur pour les monstres/quetes
  X=x;
  Y=y;

  for(int i=y-11; i<=y+12;i++){
    for(int j=x-40; j<x+40; j++){
      int x2 = j-(x-40);
      int y2 = i-(y-12);
      switch(map[i][j]){
        case 1:
        case 3://arbres
          setcolor(10, 2);
          mvaddstr( y2, x2, "T" ); break;
        case 2://eau
          setcolor(14, 3);
          mvaddstr(  y2, x2, "~" ); break;
        case 4://routes
          setcolor(8, 0);
          mvaddstr(  y2, x2, "#" ); break;
        case 6://maisons
          setcolor(14, 4);
          mvaddstr(  y2, x2, "M" ); break;
        case 5://herbe
          setcolor(2, 2);
          mvaddstr(  y2, x2, " "); break;
      }
    }
  }//joueur
  setcolor(15, 7);
  mvaddstr(  11, 39, "P");
}

void showMap(float x, float y){

  if(AFFICHAGE){
    showMap_sdl(x, y);
  }
  else{
    showMap_terminal(x, y);
  }
}


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
