/**
 * \file menu_inventaire.c
 * \brief Affichage de l'inventaire du joueur
 * \author Girod Valentin
 * \date 12 mars 2019
 *
 * Affichage de l'inventaire du joueur
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <map.h>
#include <fonctions_sdl.h>
#include <creationPerso.h>
#include <inventaire.h>


/**
 * \fn void showInventory()
 * \brief Affichage ... regardez au dessus :/
 */
void showInventory(){
  //la longueur des barres de vie/mana/xp est de 8.54% de l'image, suivie d'une autre barre de 8.54% de l'image d'une autre couleur pour la barre vide
  //Il faut (pour l'instant) 100xp par niveau, 100hp en tout,
  //8.54%/100 = le nombre de pixels pour 1xp
  //nouvelle taille en pixels de l'image: (SCREEN_HEIGHT/100)*90
  //8.54% de cette taille = nb de pixels qu'il faut

  float pixels = ((SCREEN_WIDTH/100)*95/100*8.54);
  //calcul du nombre d'xp du niveau actuel:
  //int actual_xp = 100-PLAYER->level*100-PLAYER->xp;
  int actual_xp=PLAYER->xp;
  //affichage des barres
  int W = SCREEN_WIDTH-5*SCREEN_WIDTH/100;
  int H = SCREEN_HEIGHT-5*SCREEN_HEIGHT/100;
  drawImage( (PLAYER->health*pixels/100)-pixels+2.5*SCREEN_WIDTH/100, 0, "life_bar.png", W, H);
  drawImage( actual_xp*pixels/100-pixels+2.5*SCREEN_WIDTH/100, 0, "xp_bar.png", W, H);
  drawImage( PLAYER->mana*pixels/100-pixels+2.5*SCREEN_WIDTH/100, 0, "mana_bar.png", W, H);
  drawImage( 2.5*SCREEN_WIDTH/100, 0, "inventory.png", W, H);

  //le calcul du nombre de pixels pour afficher le texte suis la même logique que les pixels

  //variables de taille du texte et chaine de charactère pour afficher les nombres
  char num[3];
  int textH = 55;
  int textW = 35;

  //affichage du level
  float PxTextXlevel = ((SCREEN_WIDTH/100)*47);
  float PxTextYlevel = ((SCREEN_WIDTH/100)*2.8);
  sprintf(num,"%d",PLAYER->level);
  drawText( PxTextXlevel, PxTextYlevel, num, textH, textW);


  float PxTextXActuel = ((SCREEN_WIDTH/100)*35.1); //X ne change pas pour les 3 premier nombres
  float PxTextYVie = ((SCREEN_WIDTH/100)*7.2);
  float PxTextYXP = ((SCREEN_WIDTH/100)*11.2);
  float PxTextYMana = ((SCREEN_WIDTH/100)*15.2);

  //affichage des valeurs des barres
  sprintf(num,"%d",PLAYER->health);
  drawText( PxTextXActuel, PxTextYVie, num, textH, textW);
  sprintf(num,"%d",actual_xp);
  drawText( PxTextXActuel, PxTextYXP, num, textH, textW);
  sprintf(num,"%d",PLAYER->mana);
  drawText( PxTextXActuel, PxTextYMana, num, textH, textW);

  PxTextXActuel = ((SCREEN_WIDTH/100)*47); //on redéfinit X pour les 3 autres nombres, y ne change pas

  //affichage des valeurs max des barres
  drawText( PxTextXActuel, PxTextYVie, "100", textH, textW);
  drawText( PxTextXActuel, PxTextYXP, "100", textH, textW);
  drawText( PxTextXActuel, PxTextYMana, "100", textH, textW);

  //affichage des items équipés
  //Les images des items ont les mêmes noms que les items eux-même, cela facilite leur affichage graçe à la fonction
  //display_object dans perso.c
  drawImage( (SCREEN_WIDTH/100)*75.75, (SCREEN_HEIGHT/100)*37, display_object(PLAYER->char_armor), 110, 110);
  drawImage( (SCREEN_WIDTH/100)*60.75, (SCREEN_HEIGHT/100)*37, display_object(PLAYER->char_weapon), 110, 110);

  //affichage de l'accessoire
  char accessory[20];
  if(PLAYER->accessory==green_amulet) sprintf(accessory, "%s", "green amulet");
  if(PLAYER->accessory==ruby_ring) sprintf(accessory, "%s", "ruby ring");
  if(PLAYER->accessory==crystal_ring) sprintf(accessory, "%s", "crystal ring");
  drawImage( (SCREEN_WIDTH/100)*60.75, (SCREEN_HEIGHT/100)*9, accessory, 110, 110);

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

          //si c'est la touche d'inventaire, ou la touche échap, ou la touche entrée
          if(state[SDL_SCANCODE_I] || state[SDL_SCANCODE_ESCAPE] || state[SDL_SCANCODE_RETURN]){
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
  showMap( X, Y);
  SDL_RenderPresent(renderer);

}
