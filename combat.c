
#include <combat.h>

/*menu principal du combat*/

int combat_on(character_t **player, inventory_t *inventory){

   int monster_number = entier_aleatoire(1,4); /*nb de monstre qui fera partie du combat*/
   printf("vous êtes aux coordonnees %d et %d\n", position_x, position_y);

   character_t * monster[monster_number];   /*tableau de monstre généré*/

   int i;
   for( i = 0; i < monster_number;i++){
      monster[i] = NULL;
      monster[i] = monster_creation();
   }

   int etat=1; /*variable qui récupère l option choisie par le joueur lorsqu'il est tombé en combat */
   int xp_temp=0; /*les xp qui sont récupérés lors du combat si le joueur a gagné*/

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
         case 2: retour = taking_potion(&(*player)); break;  /*afficher les monstres à chaque tour*/
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
   }while (choix_j > nb_monstre || choix_j< 1);

   choix_j--;


   printf("Vous avez choisi %s (adv %d)!\n", tab_monstre[choix_j]->name,choix_j+1);
/*   affich(tab_monstre[choix_j-1]);*/
   attack(player,&tab_monstre[choix_j]);

   /* affich(tab_monstre[choix_j-1]);*/

}

void sort_joueur(character_t* player,character_t* tab_monstre[]){

   int i;
   int choix_j;

  int nb_monstre;

   do{
      for( i = 0; i < nb_monstre;i++){
        printf("\tadversaire %d : %s (vie: %d/%d)\n",i+1, tab_monstre[i]->name,tab_monstre[i]->health, tab_monstre[i]->max_health);
      }
      printf("Appliquer quoi à qui?\n");
      scanf("%d",&choix_j );
      viderBuffer();
   }while((choix_j-1) > nb_monstre || (choix_j-1) <0);

    printf("monstre %s choisi\n", tab_monstre[choix_j-1]->name);
    casting_spell(player,&tab_monstre[choix_j-1]);

}

int affich_choix(){

         int player_choice = 0;

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
   int degat = (attacker->stat_strength) * (attacker->char_weapon->value_object);

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


void fight_rand(){

   int trap=0;
   if (Personnage->accessory != evite_combats){
      trap= entier_aleatoire(1,100);
   }else
      trap= entier_aleatoire(51,100);

   int chances= map_threat[position_x][position_y];
   printf("chances de la map %d, trap random %d \n",chances, trap );
   if(trap <= chances){
      etat_jeu = EN_COMBAT;
      combat_on(&Personnage,Inventaire);
   }


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


void apply_state_modifier(character_t ** target, int indice, int ind){

    (*target)->state[indice] = (*target)->state[indice] == FAUX ? VRAI: FAUX ;

}



int is_dead(character_t *target){ /* rip :(*/

  return (target->health <= 0); /*retourne 0 = il est vivant*/

}
