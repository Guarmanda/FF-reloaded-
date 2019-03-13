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
    //si la quête n'est pas finie
    if(quetes[i]->statut !=3){
      //si on peut afficher le perso de début de quête, on le fait
      //printf("x:%.1f y:%.1f\n", quetes[i]->pnj_x-X, nbSpriteX/2);
      if(fabs(quetes[i]->pnj_x-X) <= nbSpriteX/2 && fabs(quetes[i]->pnj_y-Y) <= nbSpriteY/2 ){
        //on reprends le calcul de la map pour les coordonnées du pnj en pixels
        int pnj_x = (quetes[i]->pnj_x-(X-nbSpriteX/2))*125;
        int pnj_y = (quetes[i]->pnj_y-(Y-nbSpriteY/2))*125;
        drawImage( pnj_x, pnj_y, "pnj.png", 60, 60);
      }
      if(abs((int)(quetes[i]->but_x-X)) <= nbSpriteX/2 && abs((int)(quetes[i]->but_y-Y)) <= nbSpriteY/2 ){
        int but_x = (quetes[i]->but_x-(X-nbSpriteX/2))*125;
        int but_y = (quetes[i]->but_y-(Y-nbSpriteY/2))*125;
        drawImage( but_x, but_y, quetes[i]->nom_img, 60, 60);
      }
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
