/**
 * \file game.c
 * \brief Fonction principale du jeu
 * \author Girod Valentin
 * \date 12 mars 2019
 *
 * Contient le loop du jeu
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fonctions_affichage.h>
#include "map.h"
#include "combat.h"
#include <math.h>
#include "quete.h"
#include <affichage.h>
#include "menu_principal.h"




/**
 * \fn void startGame(float x, float y)
 * \brief Commence/charge une partie à des coordonnées données
 * \param[in] Abscisse du début de partie
 * \param[in] Ordonnée du début de partie
 */
void startGame(float x, float y){
  setEtatJeu(VRAI);
  setVitessePerso(0.03);
  //si on est à des coordonnées trop petites pour l'écran, on adapte
  int nbSpriteX = getScreenWidth()/125;
  int nbSpriteY = getScreenHeight()/125;
  if(y-nbSpriteY/2<0) y=nbSpriteY/2;
  if(x-nbSpriteX/2<0) x=nbSpriteX/2;
  if(y+nbSpriteY/2+2>1000) y=999-(nbSpriteY/2+2);
  if(x+nbSpriteX/2+2>1000) x=999-(nbSpriteX/2+2);
  afficher_Map( x, y);
  faire_rendu();
  int running = 1;
   float X = getX();
   float Y = getY();
  while(running && getEtatJeu()!=END_OF_GAME) {
    //Au départ la gestion du clavier se faisait avec un event qui détectait l'appuis d'une touche
    //mais dès que j'ai mis cette partie du code ici sans utiliser l'event, les déplacements sont devenus bien
    //plus fluides, rapides, et surtout la latence au moment de l'appuis sur une touche a disparue
    //(quand on restait appuyé sur une touche, le personnage restait une seconde immobile, comme quand on écrit
    //un caractère en continu)
    //Donc, si on a un mouvement du joueur, on affiche à nouveau la map et les quêtes
    if(detecter_mouvement(&x, &y)){
      //X et Y sont modifiés au moment du chargement de la map, avant cela ils désignes les anciennes coordonnées
      //On peut donc voir si le joueur a changé de case, et vérifier s'il rencontre un monstres
      if(fabs(floor(X)-floor(x)) > 0 || fabs(floor(Y)-floor(y)) > 0){ //si le joueur change de case
        fight_rand();
      }
      //chargement de la map
      afficher_Map( x, y);
      afficher_quetes();
      faire_rendu();
    }
    detecter_touches(&running);
  }
  showMenu();
}
