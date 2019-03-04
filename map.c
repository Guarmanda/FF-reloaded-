#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "fonctions_sdl.h"
#include "map.h"



void showMap(SDL_Renderer * renderer, float x, float y){

  //il faut empêcher tout débordement de la map
  int x_player=x;
  int y_player=y;
  if(y-3<0) y=3;
  if(x-5<0) x=5;
  if(y+3>1000) y=996;
  if(x+6>1000) x=993;
  for(int i=y-3; i<y+3;i++){
    for(int j=x-5; j<x+6; j++){
        int x2 = j-(x-5);
        int y2 = i-(y-3);
      //chaque nombre dans la matrice corresponds à une sprite
      switch(map[i][j]){
        case 5: drawImage(renderer, x2*125, y2*125, "map_grass.png"); break;
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
        case 1: drawImage(renderer, x2*125, y2*125, "map_grass.png");
                drawImage(renderer, x2*125, y2*125, "map_tree1.png"); break;
        case 3: drawImage(renderer, x2*125, y2*125, "map_grass.png");
                drawImage(renderer, x2*125, y2*125, "map_tree2.png"); break;
        case 6: drawImage(renderer, x2*125, y2*125, "map_grass.png");
                drawImage(renderer, x2*125, y2*125, "map_house.png"); break;

      }
    }
  }
  if(y_player>=3) y_player = 3;
  if(x_player>=5) x_player = 5;
  drawImage(renderer, x_player*125+125/4, y_player*125+125/4, "player1.png");
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
