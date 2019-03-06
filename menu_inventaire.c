#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "map.h"
#include "fonctions_sdl.h"
#include "menu_inventaire.h"
//http://jerom-bd.blogspot.com/2013/08/tileset-fantasy-16x16.html


void showInventory(SDL_Renderer * renderer){
  drawImage(renderer, 50, 0, "inventory.png");
  SDL_RenderPresent(renderer);

  int running = 1;
  int selected = 1;
  while(running) {
  	SDL_Event e;
  	while(SDL_PollEvent(&e)) {
  		switch(e.type) {
        case SDL_KEYDOWN:
        {
          //l'état du clavier à l'instant actuel
          const Uint8 *state = SDL_GetKeyboardState(NULL);

          //si c'est la touche d'inventaire, ou la touche échap
          if(state[SDL_SCANCODE_I] || state[SDL_SCANCODE_ESCAPE] || state[SDL_SCANCODE_ESCAPE] || state[SDL_SCANCODE_EXECUTE]){
            running = 0;
          }

          break;
        }
        case SDL_MOUSEBUTTONDOWN:
        //quand on clique, si on clique au dessus du sélecteur, on va placer une case.
        //Sinon, on regarde si on a cliqué dans une case du sélecteur.
        {
          int mouse_x, mouse_y;
          SDL_GetMouseState(&mouse_x, &mouse_y);
          //si on est dans le sélecteur

        break;
      }
      }
    }
  }
  SDL_RenderClear(renderer);
  showMap(renderer, X, Y);
  SDL_RenderPresent(renderer);

}
