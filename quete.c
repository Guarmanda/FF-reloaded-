#include <quete.h>


/*on charge les quetes à partir d'un fichier facilement modifiable pour les stocker dans un tableau.*/
/**
 * \fn void afficher_quetes()
 * \brief Mets les pointeurs du tableau de quêtes à NULL puis charge un nombre indéfinit de quêtes depuis le fichier de quetes (pratique pour en ajouter facilement)
 */
void charger_quetes(){
  FILE* fichier_quetes= fopen("quetes.txt", "r");
  int i;

  for( i=0; i<100; i++){
    quetes[i] = NULL;
  }
  i=0;
  while( !feof(fichier_quetes) && i < MAX_QUETES){
      quetes[i] = malloc(sizeof(quete_t));

      fscanf(fichier_quetes, "pnj_nom=\"%[^\"]\",pnj_img=\"%[^\"]\",pnj_x=%d,pnj_y=%d,\"%[^\"]\",but_x=%d,but_y=%d,\"%[^\"]\",\"%[^\"]\",xp=%d;\n",
      quetes[i]->pnj_nom, quetes[i]->pnj_img, &quetes[i]->pnj_x, &quetes[i]->pnj_y, quetes[i]->phrase_debut, &quetes[i]->but_x, &quetes[i]->but_y,
       quetes[i]->nom_img, quetes[i]->phrase_fin, &quetes[i]->xp);
      quetes[i]->statut = 0;
      i++;
  }
  printf("%d quetes chargées\n",i);
}
void afficher_quete(float x, float y, int i, char etat){

}
