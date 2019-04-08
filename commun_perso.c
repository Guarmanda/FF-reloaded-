#include <commun_perso.h>
#include <commun.h>

/*partie des tests sur perso*/

void attribution_sort(int indice,character_t* perso){

   if(perso->liste_spell->debut_liste == NULL){
      perso->liste_spell->debut_liste = perso->liste_spell;
      perso->liste_spell->sort= &tab_sort[indice];
   }else{
      liste_sort_t* new= malloc(sizeof(liste_sort_t));

      while(perso->liste_spell->sort_suivant!= NULL){
         perso->liste_spell= perso->liste_spell->sort_suivant;
      }
      new->debut_liste = perso->liste_spell->debut_liste;
      new->sort=&tab_sort[indice];
      new->sort_suivant= NULL;
      perso->liste_spell->sort_suivant= new;

   }

}

static void supprimer_sorts(character_t* perso){

   if(perso->liste_spell->debut_liste != NULL){

      while(perso->liste_spell !=NULL){
        free(perso->liste_spell);
        perso->liste_spell= perso->liste_spell->sort_suivant;
      }
   }
   if(perso->liste_spell->debut_liste == NULL)
      printf("c est cool\n" );

}
void init_tab_sort(){ /*à initialiser au début de la partie*/
   int i;

   creer_string(&tab_sort[0].nom_sort,"Feu 1");
   creer_string(&tab_sort[1].nom_sort,"Eclair 1");
   creer_string(&tab_sort[2].nom_sort,"Air 1");
   creer_string(&tab_sort[3].nom_sort,"Eau 1");

   for(i = 0; i < 4; i++){
     tab_sort[i].valeur_sort = 20;
   }

   creer_string(&tab_sort[4].nom_sort,"Double Feu");
   creer_string(&tab_sort[5].nom_sort,"Double Eclair");
   creer_string(& tab_sort[6].nom_sort,"Double Air");
   creer_string(&tab_sort[7].nom_sort,"Double Eau");

   for( ; i < 8; i++){
     tab_sort[i].valeur_sort = 40;
   }

   creer_string(&tab_sort[8].nom_sort,"Demi");   /*si niveau du target <= niv lanceur de sort + gerer aleatoire comme "evader"*/
   creer_string(&tab_sort[9].nom_sort,"Tremblement de terre"); /*degat causés à tous les enemis*/
   creer_string(& tab_sort[10].nom_sort,"Ultima"); /* dégats sur tous les enemis aussi*/

   tab_sort[8].valeur_sort =50 ;
   tab_sort[9].valeur_sort =70 ;
   tab_sort[10].valeur_sort =90 ;

   for(i = 0; i<= 10; i++){
     tab_sort[i].type_sort = offensif;
   }

   creer_string(&tab_sort[11].nom_sort,"Blind"); /*gerer avec aleatoire + chance  + level du lanceur de sort*/
   creer_string(&tab_sort[12].nom_sort,"Sleep");
   creer_string(&tab_sort[13].nom_sort,"Slow");
   creer_string(&tab_sort[14].nom_sort,"Stunt");
   creer_string(&tab_sort[15].nom_sort,"Bleed");
   creer_string(&tab_sort[16].nom_sort,"Berserk");
   creer_string(&tab_sort[17].nom_sort,"Poison");

   /*sorts de type magie blanche */
   creer_string(&tab_sort[18].nom_sort,"Red Bull");
   creer_string(&tab_sort[19].nom_sort,"Anti Blind");
   creer_string(&tab_sort[20].nom_sort,"Antidote");  /*enleve un etat */
   creer_string(&tab_sort[21].nom_sort,"Poudre de perlimpinpin");
   creer_string(&tab_sort[22].nom_sort,"Hologramme");

   int j;
   for(j=1 ; i < TAILLE_TAB_SORT ; i++,j++){
     tab_sort[i].type_sort = modifie_etat;
     tab_sort[i].valeur_sort = j ;
   }
   printf("\t\taffichage des sorts\n");
   /*affich_tab_sort();
*/
}

void affich_tab_sort(){
   int i;
   char* etat;

   for(i=0; i < TAILLE_TAB_SORT ; i++){

      switch (tab_sort[i].type_sort) {
         case modifie_etat: creer_string(&etat,"modificateur"); break;
         case offensif:  creer_string(&etat,"offensif"); break;
         case defensif:  creer_string(&etat,"défensif"); break;
      }

      printf("nom du sort: %s ; valeur du sort: %d%%; type du sort %s\n",tab_sort[i].nom_sort,tab_sort[i].valeur_sort,etat );
      supprimer_string(&etat);
   }

}

err_t suppr_tab_sort(){
  int i;

  for (i = 0; i< TAILLE_TAB_SORT ; i++){
      supprimer_string(&tab_sort[i].nom_sort);
  }

  return OK_state;
}
void delete_player(character_t** player){

    if(*player != NULL){

      delete_object(&(*player)->char_armor);
      delete_object(&(*player)->char_weapon);
      supprimer_string(&(*player)->class_char);
      supprimer_string(&(*player)->gender);
      supprimer_string(&(*player)->name);

      free((*player)->liste_spell);
      free(*player);
      *player=NULL;
   }

}

int chercher_sort(char* nom_sort){
   int i;
   for (i = 0; !(strcmp(nom_sort,tab_sort[i].nom_sort)) && i <TAILLE_TAB_SORT; i++);

   return i< TAILLE_TAB_SORT? i : ERR_LISTE_IND_ELEM;

}
void afficher_sorts(character_t* perso){

   perso->liste_spell = perso->liste_spell->debut_liste;

   while(perso->liste_spell != NULL){
      printf("sort %s  et valeur= %d \n", perso->liste_spell->sort->nom_sort,perso->liste_spell->sort->valeur_sort  );
      perso->liste_spell = perso->liste_spell->sort_suivant ;
   }

}


void affich_stats(character_t* perso){
   printf("\tnom du joueur : %s\nPoints d'expérience : %d\nNiveau : %d\nVie : %d/%d\nMana : %d/%d\nForce = %d \nIntelligence : %d\nStamina : %d\n",
   perso->name, perso->xp,perso->level,perso-> health, perso-> max_health,
   perso->mana,perso->max_mana,perso->stat_strength, perso->stat_intelligence,perso->stat_stamina);


  /*
   printf("les sorts\n" );
    afficher_sorts(perso);
*/}
