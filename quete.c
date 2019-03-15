/**
 * \file quetes.c
 * \brief Chargement, gestion et affichage des quêtes
 * \author Girod Valentin
 * \date 12 mars 2019
 *
 * Contient les fonctions de chargement, gestion et affichage des quêtes
 *
 */
#include <math.h>
#include <quete.h>
#include <map.h>
#include <fonctions_sdl.h>
#include <string.h>
#include <creationPerso.h>

//chargement des objets/personnages de quêtes sur la map s'il y en a
/**
 * \fn void afficher_quetes()
 * \brief Affichage des gestion des quêtes sur la map, si le joueur est prêt d'un objectif ou d'un pnj
 */
void afficher_quetes(){
  //on a besoin du nombre de sprites affichables
  float nbSpriteX = SCREEN_WIDTH/125;
  float nbSpriteY = SCREEN_HEIGHT/125;
  for(int i=0; i<100 && quetes[i] != NULL; i++){
      //si on peut afficher le perso de début de quête, on le fait
      //printf("x:%.1f y:%.1f\n", quetes[i]->pnj_x-X, nbSpriteX/2);
    if(fabs(quetes[i]->pnj_x-X) <= nbSpriteX/2 && fabs(quetes[i]->pnj_y-Y) <= nbSpriteY/2 ){
      //on reprends le calcul de la map pour les coordonnées du pnj en pixels
      int pnj_x = (quetes[i]->pnj_x-(X-nbSpriteX/2))*125;
      int pnj_y = (quetes[i]->pnj_y-(Y-nbSpriteY/2))*125;
      drawImage( pnj_x, pnj_y, "pnj.png", 60, 60);
    }
    //meme chose pour le but d'une quête, mais le statut de la quête doit être 1
    if(abs((int)(quetes[i]->but_x-X)) <= nbSpriteX/2 && abs((int)(quetes[i]->but_y-Y)) <= nbSpriteY/2 && quetes[i]->statut ==1){
      int but_x = (quetes[i]->but_x-(X-nbSpriteX/2))*125;
      int but_y = (quetes[i]->but_y-(Y-nbSpriteY/2))*125;
      drawImage( but_x, but_y, quetes[i]->nom_img, 60, 60);
    }
    //si un joueur croise un pnj (si la distance entre les deux est inférieure à 1)
    if(fabs(quetes[i]->pnj_x-X) <= 1 && fabs(quetes[i]->pnj_y-Y) <= 1 ){
      int pnj_x = (quetes[i]->pnj_x-(X-nbSpriteX/2))*125;
      int pnj_y = (quetes[i]->pnj_y-(Y-nbSpriteY/2))*125;
      //si la quête commence, on affiche le message de début
      if(quetes[i]->statut < 2){
        if(quetes[i]->statut == 0) quetes[i]->statut = 1;
        int long_p_deb = strlen(quetes[i]->phrase_debut) * 8;
        drawImage( pnj_x-long_p_deb/4, pnj_y-50, "bulle.png", long_p_deb+40, 60);
        drawText(pnj_x-long_p_deb/4+20, pnj_y-45, quetes[i]->phrase_debut, 25, 8);
      }
      //sinon on affiche le message de fin et on donne l'xp au joueur
      else {
        if(quetes[i]->statut == 2){
           quetes[i]->statut = 3;
           PLAYER->xp += quetes[i]->xp;
           if(PLAYER->xp >=100){
             PLAYER->level++;
             PLAYER->xp -= 100;
           }
        }
        int long_p_fin = strlen(quetes[i]->phrase_fin) * 8;
        drawImage( pnj_x-long_p_fin/4, pnj_y-50, "bulle.png", long_p_fin+40, 60);
        drawText(pnj_x-long_p_fin/4+20, pnj_y-45, quetes[i]->phrase_fin, 25, 8);
      }
    }
    //si on croise un but
    if(fabs(quetes[i]->but_x-X) <= 1 && fabs(quetes[i]->but_y-Y) <= 1 ){
        if(quetes[i]->statut == 1) quetes[i]->statut = 2;
    }
  }
}


//on charge les quetes à partir d'un fichier facilement modifiable pour les stocker dans un tableau.
/**
 * \fn void afficher_quetes()
 * \brief Mets les pointeurs du tableau de quêtes à NULL puis charge un nombre indéfinit de quêtes depuis le fichier de quetes (pratique pour en ajouter facilement)
 */
void charger_quetes(){
  FILE*fichier_quetes= fopen("quetes.txt", "r");
  for(int i=0; i<100; i++){
    quetes[i] = NULL;
  }
  int i=0;
  while(!feof(fichier_quetes)&& i<100){
      quetes[i] = malloc(sizeof(quete_t));
      int nb1, nb2, nb3, nb4, nb5;
      char char1[200];
      char char2[30];
      char char3[200];
      fscanf(fichier_quetes, "pnj_x=%d,pnj_y=%d,\"%[^\"]\",but_x=%d,but_y=%d,\"%[^\"]\",\"%[^\"]\",xp=%d;\n",
      &quetes[i]->pnj_x, &quetes[i]->pnj_y, quetes[i]->phrase_debut, &quetes[i]->but_x, &quetes[i]->but_y,
       quetes[i]->nom_img, quetes[i]->phrase_fin, &quetes[i]->xp);
      quetes[i]->statut = 0;
      printf("%d, %d, %s \n", quetes[i]->pnj_x,quetes[i]->pnj_y, quetes[i]->phrase_debut );
      i++;
  }
  printf("%d quetes chargées\n",i);
}
