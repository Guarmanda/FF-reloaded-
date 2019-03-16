/**
 * \file game.c
 * \brief Fonction principale du jeu
 * \author Karman Nathalie; Papot Alexandre; Girod Valentin
 * \date 12 mars 2019
 *
 * Contient le loop du jeu
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <fonctions_sdl.h>
#include <map.h>
#include <menu_principal.h>
#include <menu_inventaire.h>
#include <math.h>
#include <quete.h>

static float VITESSE_PERSO = 0.015; /*!< Vitesse du personnage (plus le jeu est optimisé en mémoire vive, moins il va vite, et plus il faut augmenter cette valeur) */

/**
 * \fn void startGame(float x, float y)
 * \brief Commence/charge une partie à des coordonnées données
 * \param[in] Abscisse du début de partie
 * \param[in] Ordonnée du début de partie
 */
void startGame(float x, float y){
  //si on est à des coordonnées trop petites pour l'écran, on adapte
  int nbSpriteX = SCREEN_WIDTH/125;
  int nbSpriteY = SCREEN_HEIGHT/125;
  if(y-nbSpriteY/2<0) y=nbSpriteY/2;
  if(x-nbSpriteX/2<0) x=nbSpriteX/2;
  if(y+nbSpriteY/2+2>1000) y=999-(nbSpriteY/2+2);
  if(x+nbSpriteX/2+2>1000) x=999-(nbSpriteX/2+2);
  showMap( x, y);
  //x_select: les coordonées du seleteur de façon à le centrer sur l'écran
  int x_select = (SCREEN_WIDTH-1200)/2;
  SDL_RenderPresent(renderer);
  int running = 1;
  int selected = 1;
  while(running) {
    //Au départ la gestion du clavier se faisait avec un event qui détectait l'appuis d'une touche
    //mais dès que j'ai mis cette partie du code ici sans utiliser l'event, les déplacements sont devenus bien
    //plus fluides, rapides, et surtout la latence au moment de l'appuis sur une touche a disparue
    //(quand on restait appuyé sur une touche, le permonnage restait une seconde immobile, comme quand on écrit
    //un caractère en continu)
    //l'état du clavier à l'instant actuel
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    //si c'est une touche de mouvement
    if(state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN]){
      //on gère les colisions et la vitesse du perso
      //on a besoin de regarder à quel endroit de la map on est et ce qu'il y a après
      if (state[SDL_SCANCODE_RIGHT] && (map[(int)(floor(y))][(int)(floor(x+VITESSE_PERSO))]==4 || map[(int)(floor(y))][(int)(floor(x+VITESSE_PERSO))]==5)) x+=VITESSE_PERSO;
      else if (state[SDL_SCANCODE_UP] && (map[(int)(floor(y-VITESSE_PERSO))][(int)(floor(x))]==4 || map[(int)(floor(y-VITESSE_PERSO))][(int)(floor(x))]==5)) y-=VITESSE_PERSO;
      else if (state[SDL_SCANCODE_DOWN] && (map[(int)(floor(y+VITESSE_PERSO))][(int)(floor(x))]==4 || map[(int)(floor(y+VITESSE_PERSO))][(int)(floor(x))]==5)) y+=VITESSE_PERSO;
      else if (state[SDL_SCANCODE_LEFT] && (map[(int)(floor(y))][(int)(floor(x-VITESSE_PERSO))]==4 || map[(int)(floor(y))][(int)(floor(x-VITESSE_PERSO))]==5)) x-=VITESSE_PERSO;
      if(x<0) x=0;
      if(y<0) y=0;
      if(x>999) x=999;
      if(y>999) y=999;
      //chargement de la map
      showMap( x, y);
      afficher_quetes();
      SDL_RenderPresent(renderer);
    }

  	SDL_Event e;
  	while(SDL_PollEvent(&e)) {
  		switch(e.type) {
        //la gestion du clavier hors déplacements se fait ici
        case SDL_KEYDOWN:
        {
          //si c'est la touche d'inventaire
          if(state[SDL_SCANCODE_I]){
            showInventory();
          }
          else if(state[SDL_SCANCODE_ESCAPE]){
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

        break;
      }
      }
    }
    SDL_Delay(5);
  }
  SDL_RenderClear(renderer);
  showMenu();
}
