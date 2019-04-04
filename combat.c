
#include <combat.h>

/*menu principal du combat*/

int combat_on(character_t **player, inventory_t *inventory){

   int monster_number = entier_aleatoire(1,4); /*nb de monstre qui fera partie du combat*/
   printf("vous êtes aux coordonnees %d et %d\n", position_x, position_y);

   character_t * monster[monster_number];   /*tableau de monstre généré*/

   int i;
   for( i = 0; i < monster_number;i++){
      monster[i] = NULL;
      monster[i] = monster_creation();/* faut mettre les coordonnees */
   }

   int etat=1;
   int xp_temp=0;

   do{
      printf("\n\tjoueur %s (%d/%d)\n",(*player)->name, (*player)->health,(*player)->max_health);
      printf("\nil y a %d monstres\n",monster_number );

      for( i = 0; i < monster_number;i++){
         printf("\tadversaire %d : %s (vie: %d/%d ; niveau : %d)\n",i+1, monster[i]->name,monster[i]->health, monster[i]->max_health, monster[i]->level);
      }
      etat= affich_choix();
      int retour=1;  /*retour sert à revenir au menu lorsque le joueur a mal fait son choix
      au contraire de "etat" qui lui va juste verifier si il continue le combat ou pas (cf. running_away qui peut ne pas aboutir)*/

      switch (etat) {
         case 1: attaque_joueur(*player,monster,monster_number); break;  /*afficher les monstres à chaque tour*/
         case 2: retour = taking_potion(&(*player),inventory); break;  /*afficher les monstres à chaque tour*/
         case 3: /*casting_spell() ;*/break;
         case 4: etat = running_away(player);break;
         case 5: exit(1);  /*on ne sauvegarde rien sauf si l utilisateur l a fait avant*/
      }
      if(retour){              /*au cas où l utilisateur a fait le mauvais choix et a changé d'idée*/

         for( i = 0; i < monster_number; i++){

            if(is_dead (monster[i]) ){
               printf("\n\n\t\t%s est mort...\n\n", monster[i]->name);
               int check_xp= xp_points((*player),*monster[i]);
               printf("\tvous avez gagné %d d' xp\n", check_xp);
               xp_temp += check_xp; /*ajout des points d experience au joueur = effectif QUE si on gagne le combat*/

               update_tab_monster(monster ,i , monster_number);
               delete_player(&monster[monster_number-1]);
               monster_number--;
            }
         }
         for( i = 0; i < monster_number;i++){
            attack(monster[i], player);
         }

         /*printf("etat %d\n",etat );*/
      }

   }while(etat != 0 && monster_number >0 && !is_dead(*player));

   if(!monster_number){

      (*player)->xp += xp_temp;
      printf("vos nouveaux points d 'xp = %d\nvous avez le niveau %d\n",(*player)->xp,(*player)->level);

      if(levelling(*player)){
         printf("vous avez atteint le niveau %d \n",(*player)->level);
      }
   }else{
      printf("GAME OVER...\n" );
      etat_jeu=END_OF_GAME;
   }

   printf("\t\tfin du combat ^^\n" );
   return 1;
}

void attaque_joueur(character_t* player,character_t* tab_monstre[], int nb_monstre){ /*tableau de monstre en param*/
   int i;
   int choix_j;

   do{
      printf("Quel adversaire choisissez-vous?\n");

      for( i = 0; i < nb_monstre;i++){
         printf("\tadversaire %d : %s (vie: %d/%d)\t",i+1, tab_monstre[i]->name,tab_monstre[i]->health, tab_monstre[i]->max_health);
         printf("\n");
      }
      scanf("%d",&choix_j);   /*faire une fonction qui fasse la saisie et verifie si le choix est correct?*/
   }while (choix_j > nb_monstre || choix_j<1);

   choix_j--;


   printf("Vous avez choisi %s (adv %d)!\n", tab_monstre[choix_j]->name,choix_j+1);
/*   affich(tab_monstre[choix_j-1]);*/
   attack(player,&tab_monstre[choix_j]);

   /* affich(tab_monstre[choix_j-1]);*/

}
/*
void sort_joueur(character_t* player,character_t* tab_monstre[], int nb_monstre){

   int i;
   int choix_j;
   printf("Appliquer quoi à qui?\n");

   for( i = 0; i < nb_monstre;i++){
      printf("\t adversaire %d : %s (vie: %d/%d)\t",i+1, tab_monstre[i]->name,tab_monstre[i]->health, tab_monstre[i]->max_health);
      printf("\n");
   }
   do{
      printf("\nnombre de monstre %d\n",nb_monstre );
      scanf("%d",&choix_j );

   }while((choix_j-1) > nb_monstre || (choix_j-1) <0);

   printf("monstre %s choisi\n", tab_monstre[choix_j-1]->name);
    affich(tab_monstre[choix_j-1]);
    casting_spell(player,&tab_monstre[choix_j-1],);
    affich(tab_monstre[choix_j-1]);
}
*/
int affich_choix(){

         int player_choice = 0; /* voir plus tard pour que le joueur puisse selectionner dans le menu */

         do{
              printf("Vous êtes en combat, choisir entre les actions ci-dessous:\n" );
              printf(" 1 - Attaquer l'adversaire\n");
              printf(" 2 - Prendre une potion\n");
              printf(" 3 - Appliquer un sort (à faire)\n");
              printf(" 4 - S'évader\n");
              printf(" 5 - Quitter le jeu\n");
              printf("Votre choix : ");
              scanf(" %i",&player_choice);
         }while(player_choice > 5 || player_choice <1);
         return player_choice;
}

void update_tab_monster(character_t *monster_array[],int index, int nb_monstre){ /* swap monster place in an array*/

  for( ; index < (nb_monstre-1) ; index++){

    *monster_array[index] = *monster_array[index+1];
  }
}

void attack(character_t* attacker,character_t **target){

   printf("\t%s ATTAQUE ==> %s ...\n",attacker->name,(*target)->name);
   sleep(2);
   int degat = (attacker->stat_strength) * (attacker->char_weapon.value_object);

   ((*target)->health) -= degat;

   if(is_dead(*target)){
      ((*target)->health)=0;
   }
   printf("\t%d de dégats causés à %s (%d/%d)\n", degat,(*target)->name,(*target)->health, (*target)->max_health );

}
int levelling(character_t* player){
   int changement_niv = 50;

   if( player->xp >= (changement_niv * player->level) ){
      player->level++;
      return 1;
   }
   return 0;
}
int xp_points(character_t* player, character_t monster){

      printf("monstre level %d \n", monster.level);
      int xp_par_niveau = 10;
      return (xp_par_niveau * monster.level);

}
/*fight chance change selon l emplacement du joueur sur la map*/


int fight_rand(){

   int trap=0;
   if (Personnage->accessory != evite_combats){
      trap= entier_aleatoire(1,100);
   }else
      trap= entier_aleatoire(51,100);

   int chances= map_threat[position_x][position_y];
   printf("chances de la map %d, trap random %d \n",chances, trap );
   if(trap <= chances){
      combat_on(&Personnage,Inventaire);
      return EN_COMBAT;
   }
   return FAUX;

}




/*-------------------------------------------------------------*/

int running_away(character_t** player){ /* true => successful*/
  /* 15% chance to flee */

  if( entier_aleatoire(1,100) < 15){
    printf("Vous arrivez à vous échapper...\n" );
    (*player)->xp-=10;
    return 0;
  }
   printf("\n\n\n\n\nSorry, you have to fight...\n\n\n\n" );
   return 1;
}

void casting_spell(character_t* perso, character_t **target){


}


void apply_state_modifier(character_t **target, int value, int off_or_on){

  if(off_or_on == VRAI){
    (*target)->state[value] = FAUX;
  }else{

    (*target)->state[value] = VRAI;
  }
}


int taking_potion(character_t **player,inventory_t* inventaire){
   int choix;
   char* temp;
   do{
      int i;
      for( i =0; i< inventaire->nb_objects ; i++){
          temp=display_object(*inventaire->object[i]);
         printf("objet %d => %s\n",i+1, temp );
      }
      printf("quel objet voulez-vous prendre? [0 pour retourner au menu précédent]\n");
      scanf("%d", &choix);
   }while (choix > inventaire->nb_objects || choix<0 );

   while(choix != 0 && choix!= -1){
      /*if(choix > 0){*/
         choix--;
         printf("vous avez choisi\n" );
         temp =display_object(*inventaire->object[choix]);
         printf("objet %d => %s\n",choix+1, temp );

         if(inventaire->object[choix]->type_object == potion){ /*on ne rentre QUE si c est un
            objet de type potion ou similaire*/

            object_t* choix_potion= inventaire->object[choix];
            printf("\n\t\tvotre mana est de %d/%d \n",  (*player)->mana,(*player)->max_mana);
            printf("\n\t\tvotre vie est de %d/%d \n",  (*player)->health, (*player)->max_health);

            float pourcentage = choix_potion->value_object/10.0;

            if(choix_potion->state_object <= 1){  /*on rentre dans le cas où c est une potion mana: 0 à 1*/
               (*player)->mana += (*player)->max_mana * pourcentage;
               (*player)->mana = ((*player)->mana  > (*player)->max_mana)? (*player)->max_mana: (*player)->mana;

            }else if(choix_potion->state_object <= 3){ /*potion de vie: 2 à3*/

               (*player)->health += (*player)->max_health * pourcentage ;
               (*player)->health = ((*player)->health > (*player)->max_health)? (*player)->max_health:(*player)->health ;


            }else if(choix_potion->state_object <= 5){

               apply_state_modifier(player,choix_potion->value_object,VRAI);

            }else if(choix_potion->state_object <= 13){
               apply_state_modifier(player,choix_potion->value_object,VRAI);
            }
            printf("\n\t\tvotre mana est de %d/%d\n",  (*player)->mana,(*player)->max_mana);
            printf("\n\t\tvotre vie est de %d/%d\n",  (*player)->health, (*player)->max_health);

            choix = -1;

            }else{
                  printf("l objet choisi n'est pas une potion ou un objet qui peut être utilisé maintenant...\n");
            }

   }
   if(!choix)
      printf("Retour au menu précédent...\n" );
   return choix;
}

int is_dead(character_t *target){ /* rip :(*/

  return (target->health <= 0); /*retourne 0 = il est vivant*/

}
