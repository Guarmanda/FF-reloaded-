#include <commun_perso.h>
#include <commun.h>

/*partie des tests de l inventaire*/

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
static void afficher_sorts(character_t* perso){
   perso->liste_spell=perso->liste_spell->debut_liste;

   while(perso->liste_spell != NULL){
      printf("sort %s  et valeur= %d \n", perso->liste_spell->sort->nom_sort,perso->liste_spell->sort->valeur_sort  );
      perso->liste_spell = perso->liste_spell->sort_suivant ;
   }


}
void init_tab_sort(){ /*à initialiser au début de la partie*/
   int i;

   tab_sort[0].nom_sort=creer_string("Feu 1");
   tab_sort[1].nom_sort=creer_string("Eclair 1");
   tab_sort[2].nom_sort=creer_string("Air 1");
   tab_sort[3].nom_sort=creer_string("Eau 1");

   for(i = 0; i < 4; i++){
     tab_sort[i].valeur_sort = 20;
   }

   tab_sort[4].nom_sort=creer_string("Double Feu");
   tab_sort[5].nom_sort=creer_string("Double Eclair");
   tab_sort[6].nom_sort=creer_string("Double Air");
   tab_sort[7].nom_sort=creer_string("Double Eau");
   tab_sort[8].nom_sort=creer_string("Demi");   /*si niveau du target <= niv lanceur de sort + gerer aleatoire comme "evader"*/
   tab_sort[9].nom_sort=creer_string("Tremblement de terre"); /*degat à tous les enemis*/
   tab_sort[10].nom_sort=creer_string("Ultima"); /*9999 dégats sur tous les enemis aussi*/

   for( ; i < 8; i++){
     tab_sort[i].valeur_sort = 40;
   }
   tab_sort[8].valeur_sort =50 ;  /*pour sort Demi qui joue sur les pourcentages*/
   tab_sort[9].valeur_sort =70 ;
   tab_sort[10].valeur_sort =90 ;
   for(i = 0; i<= 10; i++){
     tab_sort[i].type_sort = offensif;
   }
   /*sorts specifiques pour les monstres*/
   tab_sort[11].nom_sort=creer_string("Blind"); /*gerer avec aleatoire + chance  + level du lanceur de sort*/
   tab_sort[12].nom_sort=creer_string("Sleep");
   tab_sort[13].nom_sort=creer_string("Slow");
   tab_sort[14].nom_sort=creer_string("Stunt");
   tab_sort[15].nom_sort=creer_string("Bleed");
   tab_sort[16].nom_sort=creer_string("Berserk");
   tab_sort[17].nom_sort=creer_string("Poison");

   /*sorts de type magie blanche */
   tab_sort[18].nom_sort=creer_string("Red Bull");
   tab_sort[19].nom_sort=creer_string("Anti Blind");
   tab_sort[20].nom_sort=creer_string("Antidote");  /*enleve un etat */
   tab_sort[21].nom_sort=creer_string("Poudre de perlimpinpin");
   tab_sort[22].nom_sort=creer_string("Hologramme");


   int j;
   for(j=1 ; i < TAILLE_TAB_SORT ; i++,j++){
     tab_sort[i].type_sort = modifie_etat;
     tab_sort[i].valeur_sort = j ;
   }
   printf("\t\taffichage des sorts\n");
   affich_tab_sort();

}
void affich_tab_sort(){
   int i;
   char* etat;

   for(i=0; i < TAILLE_TAB_SORT ; i++){

      switch (tab_sort[i].type_sort) {
         case modifie_etat: etat=creer_string("modificateur"); break;
         case offensif:  etat= creer_string("offensif"); break;
         case defensif:  etat=creer_string("défensif"); break;
      }

      printf("nom du sort: %s ; valeur du sort: %d%% type du sort %s\n",tab_sort[i].nom_sort,tab_sort[i].valeur_sort,etat );
      supprimer_string(&etat);
   }

}

err_t suppr_tab_sort(spell_t* spell){
   return OK_state;
}
void delete_player(character_t** player){

    if(*player != NULL){
      free(*player);
      *player=NULL;
   }
}

void affich_stats(character_t* perso){
   printf("nom perso %s\n", perso->name);
   printf("xp = %d\n", perso->xp);
   printf("level = %d\n", perso->level);
   printf("health = %d\n", perso-> health);
   printf("mana= %d\n", perso->mana);
   printf("state= %d\n", perso->state[0]);
   printf("stat_strength = %d \n", perso->stat_strength);
   printf("stat_intelligence= %d \n", perso->stat_intelligence);
   printf("stat_stamina= %d \n", perso->stat_stamina);
   printf("class_char= %s\n", perso->class_char);
   printf("accessoire= %d\n", perso->accessory);
   char* objet= display_object(perso->char_armor);
   char* objet2= display_object(perso->char_weapon);
   printf("armure = %s\n",objet);
   printf("arme = %s\n",objet2);
   printf("affichage des sorts\n" );

   afficher_sorts(perso);

}
