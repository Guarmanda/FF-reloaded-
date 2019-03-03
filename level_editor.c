#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "fonctions_sdl.h"
#include "map.h"
#include "level_editor.h"
#include "menu_principal.h"

void showEditor(SDL_Renderer * renderer, SDL_Window*pWindow, int x, int y){
  showMap(renderer, x, y);
  //x_select: les coordonées du seleteur de façon à le centrer sur l'écran
  int x_select = (SCREEN_WIDTH-1200)/2;
  drawImage(renderer, x_select, SCREEN_HEIGHT-200, "item_selector.png");
  SDL_RenderPresent(renderer);

  int running = 1;
  int selected = 1;
  while(running) {
  	SDL_Event e;
  	while(SDL_PollEvent(&e)) {
  		switch(e.type) {
        //et là, on peut bouger sur la map. \o/
        case SDL_KEYDOWN:
        {
          const Uint8 *state = SDL_GetKeyboardState(NULL);
          if (state[SDL_SCANCODE_RIGHT]) x+=1;
          else if (state[SDL_SCANCODE_UP]) y-=1;
          else if (state[SDL_SCANCODE_DOWN]) y+=1;
          else if (state[SDL_SCANCODE_LEFT]) x-=1;
          if(x<0) x=0;
          if(y<0) y=0;
          if(x>1000) x=999;
          if(y>1000) y=999;
          SDL_RenderClear(renderer);
          showMap(renderer, x, y);
          drawImage(renderer, x_select, SCREEN_HEIGHT-200, "item_selector.png");
          SDL_RenderPresent(renderer);
          break;
        }
        case SDL_MOUSEBUTTONDOWN:
        //quand on clique, si on clique au dessus du sélecteur, on va placer une case.
        //Sinon, on regarde si on a cliqué dans une case du sélecteur.
        {
          int mouse_x, mouse_y;
          SDL_GetMouseState(&mouse_x, &mouse_y);
          //si on est dans le sélecteur
          if(mouse_y>SCREEN_HEIGHT-165){
            printf("%d, %d\n", mouse_x, mouse_y);
            //si on est à la hauteur d'une case du sélecteur
            if(mouse_y>SCREEN_HEIGHT-150 && mouse_y<SCREEN_HEIGHT){
              //la position de x sur l'image
              int pos = mouse_x-(x_select+245);
              for(int j=0,i = 1; j<pos+85 ;i++, j+=100){
                if(pos >= j && pos <= j+85){
                  //i corresponds au numéro de la case du sprite sélectionné,
                  //et aussi au numéro du sprite dans la matrice de la map,
                  //et ça c'est pratique
                  printf("%d\n", i);
                  if(i==8){
                    remove("Map.txt");
                    FILE *map_file = fopen("Map.txt", "w");
                    for(int i=0; i<1000; i++){
                      for(int j=0; j<1000; j++){
                        fprintf(map_file, "%d;", map[i][j]);
                      }
                      fprintf(map_file, "\n");
                    }

                    fclose(map_file);
                  }
                  if(i==9){
                    running=0;
                    showMenu(renderer, pWindow);
                  }
                  selected = i;
                }
              }
            }
          }
          //sinon on détecte la bonne position du sprite pour l'afficher sur l'écran, et on l'enregistre
          else{
            int h=y-3;
            for(int j=0; j+125<mouse_y;j+=125, h++);
            int w=x-5;
            for(int j=0; j+125<mouse_x;j+=125, w++);

            //une fois qu'on a trouvé les bonnes coordonées on modifie la map pour l'afficher en direct
            map[h][w]= selected;
            SDL_RenderClear(renderer);
            showMap(renderer, x, y);
            drawImage(renderer, x_select, SCREEN_HEIGHT-200, "item_selector.png");
            SDL_RenderPresent(renderer);
          }
        break;
      }
      }
    }
  }
}
