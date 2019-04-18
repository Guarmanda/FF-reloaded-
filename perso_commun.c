#include <perso_commun.h>


/*partie des tests sur perso*/
void debut_liste(character_t** perso){
   (*perso)->liste_spell=(*perso)->liste_spell->debut_liste;
}

void attribution_sort(int indice,character_t* perso){

   if(perso->liste_spell->debut_liste == NULL){
      perso->liste_spell->debut_liste = perso->liste_spell;
      perso->liste_spell->sort= &tab_sort[indice];

    }else{
      liste_sort_t* new= malloc(sizeof(liste_sort_t));
      new->debut_liste = perso->liste_spell->debut_liste;
      while(perso->liste_spell->sort_suivant!= NULL){
         perso->liste_spell= perso->liste_spell->sort_suivant;
      }
      new->sort=&tab_sort[indice];
      new->sort_suivant= NULL;
      perso->liste_spell->sort_suivant= new;

   }
   debut_liste(&perso);

}


void supprimer_sorts(character_t** perso){

   liste_sort_t* temp;

   if((*perso)->liste_spell->sort_suivant != NULL){
      do{

         temp = (*perso)->liste_spell->sort_suivant;
         free((*perso)->liste_spell);
         (*perso)->liste_spell=temp;
      }while( (*perso)->liste_spell != NULL);
   }

}
/*initialisation du tableau statique  = tableau global de sorts
*/
void init_tab_sort(){ /*à initialiser au début de la partie*/
   int i;

   creer_string(&tab_sort[0].nom_sort,"Feu 1");
   creer_string(&tab_sort[1].nom_sort,"Eclair 1");
   creer_string(&tab_sort[2].nom_sort,"Air 1");
   creer_string(&tab_sort[3].nom_sort,"Ice 1");

   for(i = 0; i < 4; i++){
     tab_sort[i].valeur_sort = 20;  /*coût mana et influe de 20% l attaque magique*/
   }

   creer_string(&tab_sort[4].nom_sort,"Double Feu");
   creer_string(&tab_sort[5].nom_sort,"Double Eclair");
   creer_string(& tab_sort[6].nom_sort,"Double Air");
   creer_string(&tab_sort[7].nom_sort,"Double Ice");

   for( ; i < 8; i++){
     tab_sort[i].valeur_sort = 40;
   }

   creer_string(&tab_sort[8].nom_sort,"Demi");   /*si niveau du target <= niv lanceur de sort + gerer aleatoire comme "evader"*/
   creer_string(&tab_sort[9].nom_sort,"Tremblement de terre"); /*degat causés à tous les enemis*/
   creer_string(& tab_sort[10].nom_sort,"Ultima"); /* dégats sur tous les enemis aussi*/

   tab_sort[8].valeur_sort =50 ;  /*pourcent de mana utilisé pour s en servir*/
   tab_sort[9].valeur_sort =70 ;
   tab_sort[10].valeur_sort =90 ;

   for(i = 0; i<= 10; i++){
     tab_sort[i].type_sort = offensif;
   }
   /*sorts de type magie blanche */

   creer_string(&tab_sort[11].nom_sort,"Bouclier");
   creer_string(&tab_sort[12].nom_sort,"Antidote");  /*enleve un etat */
   creer_string(&tab_sort[13].nom_sort,"Poudre de Perlimpinpin"); /*enleve le maximum d etat qu il peut*/
   creer_string(&tab_sort[14].nom_sort,"Hologramme Mélenchon"); /*fait en sorte de disparaître du champ de vision des monstres pendant un tour*/

   /*valeurs symboliques et aussi utiles pour le coût de mana*/
   tab_sort[11].valeur_sort =20 ;     /*bouclier augmente de 20% la vie au prochain tour */
   tab_sort[12].valeur_sort =30 ;  /*Antidote soigne n importe quel etat */
   tab_sort[13].valeur_sort = 50 ;  /*Antidote soigne tous les etats sous lesquels le perso se trouve*/
   tab_sort[14].valeur_sort =30 ;

   /*sorts de type state_modifier*/
   creer_string(&tab_sort[15].nom_sort,"Stunt"); /*gérer avec aleatoire + chance/accuracy de celui qui applique le sort + level du lanceur de sort*/
   creer_string(&tab_sort[16].nom_sort,"Bleed");
   creer_string(&tab_sort[17].nom_sort,"Slow");
   creer_string(&tab_sort[18].nom_sort,"Silence");
   creer_string(&tab_sort[19].nom_sort,"Poison");
   creer_string(&tab_sort[20].nom_sort,"Blind");
   creer_string(&tab_sort[21].nom_sort,"Speed");
   creer_string(&tab_sort[22].nom_sort,"Sleep");


   for ( ; i < TAILLE_TAB_SORT ; i++){
     tab_sort[i].type_sort = modifie_etat;
   }
   int j;
   for (j=Stunt ; j < TAILLE_TAB_SORT ; j++){
     tab_sort[i].valeur_sort = j ;
   }

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
      if((*player)->accessory != est_monstre){
         supprimer_string(&(*player)->class_char);
         supprimer_string(&(*player)->gender);
      }
      delete_object(&(*player)->char_armor);
      delete_object(&(*player)->char_weapon);
      supprimer_string(&(*player)->name);
      supprimer_sorts(player);
      free((*player)->liste_spell);
      free(*player);
      *player=NULL;
   }

}


void afficher_sorts(character_t* perso){

  liste_sort_t* temp;

  if(perso->liste_spell != NULL){
      temp=perso->liste_spell;
      do{

        printf("%s (coût : %d de mana)\n", temp->sort->nom_sort, temp->sort->valeur_sort);
        temp=temp->sort_suivant;
      }while(temp != NULL);
  }
  debut_liste(&perso);

}

/*fonction qui va permettre au joueur de choisir un sort, on garde en paramètre
un joueur, puisque après, le joueur aura 4 personnages à gérer dans son équipe*/

int chercher_sort(char* nom_sort){
   int i;
   for (i = 0; (nom_sort!=tab_sort[i].nom_sort) && i <TAILLE_TAB_SORT; i++);

   return ( i < TAILLE_TAB_SORT)? i : ERR_LISTE_IND_ELEM;

}

int choisir_sort_joueur(character_t* perso, int* sort_choisi){

  char choix;

  liste_sort_t* temp;
  temp=perso->liste_spell;

  printf("Voici la liste des sorts...\n" );
  sleep(1);

  int compt=1;

  do{

    if(temp == NULL){
        temp=perso->liste_spell;
        compt=1;
        printf("Vous revoici au début de la liste des sorts...\n" );
        sleep(1);
    }

    printf("%d : %s (%d)\n",compt, temp->sort->nom_sort, temp->sort->valeur_sort);
    printf("\nVoulez-vous appliquer ce sort [y/n] ? Tapez [e] pour retourner au menu précédent...\nVotre choix : ");
    scanf("%c",&choix );
    viderBuffer();
    if(choix != 'y')
      temp=temp->sort_suivant;
    else
      *sort_choisi = chercher_sort(temp->sort->nom_sort);
  }while(choix != 'y' && choix != 'e');

  debut_liste(&perso);

  return choix != 'e' ;  /* egale à 0 si on a choisi un sort*/

}

void affich_stats(character_t* perso){
   printf("\tnom du joueur : %s\nPoints d'expérience : %d\nNiveau : %d\nVie : %d/%d\nMana : %d/%d\nForce : %d \nIntelligence : %d\nStamina : %d\n",
   perso->name, perso->xp,perso->level,perso-> health, perso-> max_health,
   perso->mana,perso->max_mana,perso->stat_strength, perso->stat_intelligence,perso->stat_stamina);
   printf("équipé d'une %s et %s\n", perso->char_armor->name_object,perso->char_weapon->name_object );

}
