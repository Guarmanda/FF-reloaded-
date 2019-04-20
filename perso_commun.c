/**
 * \file      perso_commun.c
 * \author    Nathalie Karman, Alexandre Papot
 * \version   1.0
 * \date     Mars 2019
 * \brief    Module qui gère les personnages et leurs attributs en combat
 *
 * \details  On met en commun les fonctions qui sont utiles aux personnages (joueur ou adversaire)
 *            et on oublie pas les fonctions qui seront mises en oeuvre dans combat.c
 */
 #include <perso_commun.h>

/**
 * \fn void init_tab_sort(void)
 * \brief Fonction qui initialise le tableau global de sorts
*/

void init_tab_sort(){ /*à initialiser au début de la partie*/
   int i;

   creer_string(&tab_sort[0].nom_sort,"Feu 1");
   creer_string(&tab_sort[1].nom_sort,"Eclair 1");
   creer_string(&tab_sort[2].nom_sort,"Air 1");
   creer_string(&tab_sort[3].nom_sort,"Ice 1");

   for(i = 0; i < 4; i++){
     tab_sort[i].valeur_sort = 10;  /*coût mana et influe de 20% l attaque magique*/
   }

   creer_string(&tab_sort[4].nom_sort,"Double Feu");
   creer_string(&tab_sort[5].nom_sort,"Double Eclair");
   creer_string(& tab_sort[6].nom_sort,"Double Air");
   creer_string(&tab_sort[7].nom_sort,"Double Ice");

   for( ; i < 8; i++){
     tab_sort[i].valeur_sort = 20;
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
   creer_string(&tab_sort[15].nom_sort,"Speed");

   /*valeurs symboliques et aussi utiles pour le coût de mana*/
   tab_sort[11].valeur_sort =20 ;     /*bouclier augmente de 20% la vie au prochain tour */
   tab_sort[12].valeur_sort =30 ;  /*Antidote soigne n importe quel etat */
   tab_sort[13].valeur_sort = 50 ;  /*Antidote soigne tous les etats sous lesquels le perso se trouve*/
   tab_sort[14].valeur_sort =30 ;
   tab_sort[15].valeur_sort =20 ;
   for ( ; i < 16 ; i++){
     tab_sort[i].type_sort = defensif;
   }
   /*sorts de type state_modifier*/
   creer_string(&tab_sort[16].nom_sort,"Stunt"); /*gérer avec aleatoire + chance/accuracy de celui qui applique le sort + level du lanceur de sort*/
   creer_string(&tab_sort[17].nom_sort,"Bleed");
   creer_string(&tab_sort[18].nom_sort,"Slow");
   creer_string(&tab_sort[19].nom_sort,"Silence");
   creer_string(&tab_sort[20].nom_sort,"Poison");
   creer_string(&tab_sort[21].nom_sort,"Blind");
   creer_string(&tab_sort[22].nom_sort,"Sleep");

   int j;
   for (j=Stunt ; i < TAILLE_TAB_SORT ; i++){
     tab_sort[i].type_sort = modifie_etat;
     tab_sort[i].valeur_sort = j ;  /*de 0 à 6 voir tableau dans inventaire.h*/

   }


}
/**
 * \fn void affich_tab_sort(void)
 * \brief Fonction qui est utile dans les jeux de tests
 */
void affich_tab_sort(){   /*uniquement pour jeux de tests dans test_combat.c*/
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
/**
 * \fn err_t suppr_tab_sort(void)
 * \brief Fonction qui supprime le tableau de sort
 * \return OK_state après avoir tout supprimé ou KO_state si erreur lors de la suppression
 */
err_t suppr_tab_sort(){
  int i;

  for (i = 0; i< TAILLE_TAB_SORT ; i++){
      if( supprimer_string(&tab_sort[i].nom_sort) == KO_state )
        return KO_state;
  }
  return OK_state;
}

/**
 * \fn void debut_liste(character_t** perso)
 * \brief Fonction qui gère le début de la liste chaînée des sorts d'un personnage donné
 * \details va juste positionner l'élément courant comme étant le début de la liste
 * \param perso est un pointeur sur le personnage
 */
void debut_liste(character_t** perso){
  (*perso)->liste_spell=(*perso)->liste_spell->debut_liste;
}
/**
 * \fn  void attribution_sort(int indice,character_t* perso)
 * \brief Fonction qui affecte un nouveau sort à la liste chainée des sorts du personnage
 * \details est une fonction qui alloue dynamiquement l'espace nécessaire pour un int qui est l'indice du tableau de sorts
 *
 * \param indice est l'indice du tableau global des sorts
 * \param perso est le personnage qui aura le nouveau sort attribué
 */
void attribution_sort(int indice,character_t* perso){

  if(perso->liste_spell->debut_liste == NULL){
     perso->liste_spell->debut_liste = perso->liste_spell;
     perso->liste_spell->indice_tab_sorts= indice;     /*on garde l'indice du tableau global*/

   }else{
     liste_sort_t* new= malloc(sizeof(liste_sort_t));
     new->debut_liste = perso->liste_spell->debut_liste;
     while(perso->liste_spell->sort_suivant!= NULL){
        perso->liste_spell= perso->liste_spell->sort_suivant;
     }
     new->indice_tab_sorts=indice;     /*on garde l'indice du tableau global*/
     new->sort_suivant= NULL;
     perso->liste_spell->sort_suivant= new;

  }
  debut_liste(&perso);

}
/**
* \fn  void supprimer_sorts(character_t** perso)
* \brief Fonction qui supprime tous les sorts du personnage
* \details utile lorsque le joueur quitte le jeu
* \param perso est un pointeur sur le personnage qui aura ses sorts supprimés
*/
void supprimer_sorts(character_t** perso){

  liste_sort_t* temp;

  if((*perso)->liste_spell != NULL){
     do{

        temp = (*perso)->liste_spell->sort_suivant;
        free((*perso)->liste_spell);
        (*perso)->liste_spell=temp;
     }while( (*perso)->liste_spell != NULL);
  }

}

/**
 * \fn void delete_player(character_t** player)
 * \brief Fonction qui supprime n'importe quel personnage du jeu
 * \param player est le personnage qui va être supprimé
 */
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

/**
 * \fn void afficher_sorts(character_t* perso)
 * \brief Fonction qui affiche la liste des sorts d'un personnage
 * \details fonction utile si joueur a 4 perso par ex ou encore si on veut afficher les sorts du bestiaire lors d'un combat
 * \param perso est le personnage qui va avoir ses sorts affichés
*/
void afficher_sorts(character_t* perso){

  liste_sort_t* temp;

  if(perso->liste_spell->debut_liste != NULL){
      printf("Voici les sorts de %s :\n", perso->name );
      int cpt =1;
      temp=perso->liste_spell;
      do{

        printf("%d : %s (%d)\n",cpt, tab_sort[temp->indice_tab_sorts].nom_sort, tab_sort[temp->indice_tab_sorts].valeur_sort);
        temp=temp->sort_suivant;
        cpt++;
      }while(temp != NULL);
  }else{
    printf("%s ne possède pas de sorts\n",perso->name );
  }
  debut_liste(&perso);

}

/**
 * \fn static void ia_sort(character_t* adv, character_t ** joueur)
 * \brief Fonction qui servira d'IA pour les monstres de plus haut niveau
 * \details fonction utile dans module \a combat.c
 *    fonction incomplète
 * \param adv est l'adversaire qui veut appliquer le sort offensif
 * \param joueur est le joueur qui sera affecté
 */
static void ia_sort(character_t* adv, character_t ** joueur){
  liste_sort_t* temp;

  if(adv->liste_spell != NULL){
      temp=adv->liste_spell;
      do{

        temp=temp->sort_suivant;
      }while(temp != NULL);
      if(temp == NULL)
        temp= adv->liste_spell;
  }
}


/**
 * \fn void affich_stats(character_t* perso)
 * \brief Fonction qui affiche les statistiques d'un personnage donné
 * \param perso est de type \a character_t et permet d'accéder aux champs à afficher
 */
void affich_stats(character_t* perso){
   printf("\tnom du joueur : %s\nPoints d'expérience : %d\nNiveau : %d\nVie : %d/%d\nMana : %d/%d\nForce : %d \nIntelligence : %d\nStamina : %d\n",
   perso->name, perso->xp,perso->level,perso-> health, perso-> max_health,
   perso->mana,perso->max_mana,perso->stat_strength, perso->stat_intelligence,perso->stat_stamina);
   printf("équipé d'une %s et %s\n", perso->char_armor->name_object,perso->char_weapon->name_object );

}

/**
 * \fn void apply_auto_spell(character_t* perso)
 * \brief Fonction qui applique un sort sur le personnage lui-même
 * \details la fonction n'est pas terminée
 * \param perso est le personnage qui veut appliquer le sort
 */
void apply_auto_spell(character_t* perso){

  int chance=entier_aleatoire(1,6);
  int i;
  for(i = 0 ; i <chance;i++ )
     perso->state[i]=FAUX;
}
