/**
 * \file level_editor.c
 * \brief Editeur de carte
 * \author Girod Valentin
 * \date 12 mars 2019
 *
 * Contient l'éditeur de carte
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fonctions_affichage.h>
#include <affichage.h>
#include "map.h"
#include "menu_principal.h"
#include <math.h>



/**
 * \fn void showEditor(float x, float y)
 * \brief Gère l'édition de la map
 * \param[in] Abscisse du début de l'édition
 * \param[in] Ordonnée du début de l'édition
 */
void showEditor(float x, float y){
  setVitessePerso(0.15); //on sera plus rapide dans l'éditeur
  //si on est à des coordonnées trop petites pour l'écran, on adapte
  int nbSpriteX = getScreenWidth()/125;
  int nbSpriteY = getScreenHeight()/125;
  if(y-nbSpriteY/2<0) y=nbSpriteY/2;
  if(x-nbSpriteX/2<0) x=nbSpriteX/2;
  if(y+nbSpriteY/2+2>1000) y=999-(nbSpriteY/2+2);
  if(x+nbSpriteX/2+2>1000) x=999-(nbSpriteX/2+2);
  afficher_selecteur(x, y);
  int running = 1;
  int selected = 1;
  while(running) {
    //l'état du clavier à l'instant actuel
    gestion_editeur(&x, &y, &selected, &running);
  }
  showMenu();
}
