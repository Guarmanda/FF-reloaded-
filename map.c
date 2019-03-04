#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "fonctions_sdl.h"
#include "map.h"



void showMap(SDL_Renderer * renderer, float x, float y){
  //le nombre de sprites à afficher, tout comme la position du joueur, dépend de la taille de l'écran
  float nbSpriteX = SCREEN_WIDTH/125;
  float nbSpriteY = SCREEN_HEIGHT/125;

  //il faut empêcher tout débordement de la map
  float x_player=x;
  float y_player=y;
  if(y_player>=nbSpriteY/2) y_player = nbSpriteY/2;
  if(x_player>=nbSpriteX/2) x_player = nbSpriteX/2;

  if(y-nbSpriteY/2<0) y=nbSpriteY/2;
  if(x-nbSpriteX/2<0) x=nbSpriteX/2;
  if(y+nbSpriteY/2+2>1000) y=999-(nbSpriteY/2+2);
  if(x+nbSpriteX/2+2>1000) x=999-(nbSpriteX/2+2);

  //puis afficher la portion de la map ou le joueur est présent
  for(int i=y-nbSpriteY/2; i<y+(nbSpriteY/2)+2;i++){
    for(int j=x-nbSpriteX/2; j<x+(nbSpriteX/2)+2; j++){
        float x2 = j-(x-nbSpriteX/2);
        float y2 = i-(y-nbSpriteY/2);
      //chaque nombre dans la matrice corresponds à une sprite
      switch(map[i][j]){
        //avant d'afficher le joueur, on gère tout ce qui passe sous ses pieds
        case 5:
        case 1:
        case 3:
        case 6:
                drawImage(renderer, x2*125, y2*125, "map_grass.png"); break;
        case 2: drawImage(renderer, x2*125, y2*125, "map_water.png");
                drawImage(renderer, x2*125, y2*125, "map_grass_water.png"); break;
        //gestion des routes et virages
        case 4: drawImage(renderer, x2*125, y2*125, "map_path.png");
                if(map[i-1][j] == 4 && map[i+1][j]==4 && map[i][j+1]==4 && map[i][j-1]==4){
                  break;}
                if(map[i-1][j] == 4 && map[i+1][j]==4 && map[i][j+1]==4){
                  drawImage(renderer, x2*125, y2*125, "map_grass_path6.png");}
                else if(map[i-1][j] == 4 && map[i+1][j]==4 && map[i][j-1]==4){
                  drawImage(renderer, x2*125, y2*125, "map_grass_path4.png");}
                else if(map[i][j-1] == 4 && map[i][j+1]==4 && map[i-1][j]==4){
                  drawImage(renderer, x2*125, y2*125, "map_grass_path5.png");}
                else if(map[i][j-1] == 4 && map[i][j+1] ==4 && map[i+1][j]==4){
                  drawImage(renderer, x2*125, y2*125, "map_grass_path3.png");}
                else if(map[i][j-1] == 4 && map[i][j+1]==4){
                  drawImage(renderer, x2*125, y2*125, "map_grass_path2.png");}
                else if(map[i-1][j] == 4 && map[i+1][j]==4){
                  drawImage(renderer, x2*125, y2*125, "map_grass_path1.png");}
                else if(map[i][j+1] == 4 && map[i+1][j]==4){
                  drawImage(renderer, x2*125, y2*125, "map_grass_path7.png");}
                else if(map[i][j-1] == 4 && map[i-1][j]==4){
                  drawImage(renderer, x2*125, y2*125, "map_grass_path9.png");}
                else if(map[i-1][j] == 4 && map[i][j+1]==4){
                  drawImage(renderer, x2*125, y2*125, "map_grass_path10.png");}
                else if(map[i][j-1] == 4 && map[i+1][j]==4){
                  drawImage(renderer, x2*125, y2*125, "map_grass_path8.png");}
                break;
      }
    }
  }
  //puis on affiche le joueur si il est aux mêmes coordonnées
  drawImage(renderer, x_player*125+(x-(int)x), y_player*125+(y-(int)y), "player1.png");
  for(int i=y-nbSpriteY/2; i<y+(nbSpriteY/2)+2;i++){
    for(int j=x-nbSpriteX/2; j<x+(nbSpriteX/2)+2; j++){
      float x2 = j-(x-nbSpriteX/2);
      float y2 = i-(y-nbSpriteY/2);
      //puis ce qui passe au dessus de lui.
      switch(map[i][j]){
        case 1: drawImage(renderer, x2*125, y2*125, "map_tree1.png"); break;
        case 3: drawImage(renderer, x2*125, y2*125, "map_tree2.png"); break;
        case 6: drawImage(renderer, x2*125, y2*125, "map_house.png"); break;

      }
    }
  }
}


void setRandomMap(){
  time_t t;
  srand((unsigned) time(&t));
  for(int i=0; i<1000;i++){
    for(int j=0; j<1000; j++){
      map[i][j]=rand()%6+1;
    }
  }
}

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
