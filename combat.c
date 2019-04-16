
#include <combat.h>

/*fonction principale du combat qui gère tous les interventants et leurs attributs*/

int combat_on(character_t **player, inventory_t *inventory){
   int etat=1; /*variable qui récupère l option choisie par le joueur lorsqu'il est tombé en combat */
   int xp_temp=0; /*les xp qui sont récupérés lors du combat si le joueur a gagné*/
   int retour_menu=0;  /*retour_menu sert à revenir au début du menu si le joueur a mal fait son choix
   au contraire de "etat" qui lui va juste verifie l'etat du combat (si game over, si joueur s'évade, etc.)*/

   /*définition des participants du combat*/
   int monster_number = entier_aleatoire(1,4); /*nb de monstre qui fera partie du combat*/
   character_t * monster[monster_number];   /*tableau de monstre généré*/

   int i;
   for( i = 0; i < monster_number;i++){
      monster[i] = NULL;
      monster[i] = monster_creation();
   }

   /*début des actions qui s'enchaîneront*/
   do{
      printf("\n\tjoueur %s (%d/%d)\n",(*player)->name, (*player)->health,(*player)->max_health);

      for( i = 0; i < monster_number;i++){
         printf("\tAdversaire %d : %s (vie: %d/%d ; niveau : %d)\n",i+1, monster[i]->name,monster[i]->health, monster[i]->max_health, monster[i]->level);
      }

      etat= affich_choix();

      switch (etat){
         case 1: retour_menu= tour_joueur(*player,monster,monster_number,attack); break;  /*le personnage a toujours le droit d attaquer*/
         case 2: retour_menu = taking_potion(); break;
         case 3: retour_menu = tour_joueur(*player,monster,monster_number,casting_spell) ;break; /*si retour, c est que le joueur n a pas encore de sort*/
         case 4: etat = running_away();break; /*renvoie 0 si il arrive à s echapper*/
         case 5: exit(1);  /*on ne sauvegarde rien, l'utilisateur sait qu il ne peut sauvegarder sa partie QUE quand il est hors combat*/
      }

      if(retour_menu != 0 ){

         for( i = 0; i < monster_number; i++){

            if(is_dead (monster[i]) ){
               printf("\n\t%s meurt...", monster[i]->name);

               int check_xp= xp_points((*player),*monster[i]);
               /*ajout des points d experience au joueur = effectif QUE si on gagne le combat*/
               xp_temp += check_xp;
               update_tab_monster(monster ,i , monster_number);
               monster_number--;
            }
         }
 /*à changer pour faire en sorte que il y ait une fonction qui fasse jouer le monstre*/
         for( i = 0; i < monster_number;i++)
            attack(monster[i], player);


      }

   }while(etat != 0 && monster_number >0 && !is_dead(*player));

   if(!monster_number){

      (*player)->xp += xp_temp;
      printf("Vous avez gagné %d d'XP...\nVotre nouvel xp : %d\n",xp_temp,(*player)->xp);

      if(levelling(*player)){
         sleep(1);
         clear_screen();
         printf("\t\tVous avez atteint le niveau %d \n",(*player)->level);
      }

   }else if(etat){
      printf("GAME OVER...\n");
      etat_jeu=END_OF_GAME;
   }

   for(i =0; i <monster_number ; i++){
     delete_player(&monster[i]);
   }

   return etat_jeu;

}

int tour_joueur(character_t* player,character_t* tab_monstre[], int nb_monstre, void (*ptr_type_attack)(character_t* wizard,character_t **target)){
   int i;
   int choix_j;

   do{
      printf("Quel adversaire choisissez-vous? [0 pour retourner au menu précédent]\n");
      for( i = 0; i < nb_monstre;i++){
         printf("\tAdversaire %d : %s (vie: %d/%d)\n",i+1, tab_monstre[i]->name,tab_monstre[i]->health, tab_monstre[i]->max_health);

      }
      scanf("%d",&choix_j);
      viderBuffer();
   }while (choix_j > nb_monstre || choix_j< 0);

   if(choix_j){


     printf("Adversaire %s (%d/%d) choisi\n", tab_monstre[choix_j-1]->name,tab_monstre[choix_j-1]->health,tab_monstre[choix_j-1]->max_health);
     ptr_type_attack(player,&tab_monstre[choix_j-1]);
   }


   return choix_j;

}

int affich_choix(){

         int player_choice = 0;

         do{  sleep(2);
              printf("Vous êtes en combat, choisir entre les actions ci-dessous:\n\t1 - Attaquer l'adversaire\n\t2 - Prendre une potion\n\t3 - Appliquer un sort\n\t4 - S'évader\n\t5 - Quitter le jeu\nVotre choix : ");
              scanf(" %d",&player_choice);
              viderBuffer();
         }while(player_choice > 5 || player_choice <1);

         return player_choice;
}
/*si un monstre est mort pendant le combat, on va devoir faire en sorte qu il soit supprimé du tableau*/
void update_tab_monster(character_t *monster_array[],int index, int nb_monstre){

  int i;

  delete_player(&monster_array[index]);
  for( i = (index-1); i <  (nb_monstre-1); i++){
      monster_array[index] = monster_array[index+1];
  }
  nb_monstre--;

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

int is_dead(character_t *target){ /* rip :(*/

  return (target->health <= 0); /*retourne 0 = il est vivant*/

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

      int xp_par_niveau = 10; /*variable qui peut definir l evolution du perso dans tout le jeu*/
      return (xp_par_niveau * monster.level);

}

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


void casting_spell(character_t* perso, character_t **target){
  int choix_sort;
  if(perso->liste_spell->debut_liste != NULL){
      choix_sort=choisir_sort_joueur(perso);

  }else{
    printf("Vous n' avez pas de sorts\n" );
  }

}


void apply_state_modifier(character_t ** target, int indice, int ind){

    (*target)->state[indice] = ( (*target)->state[indice] == FAUX ? VRAI : FAUX ) ;

}


/*-------------------------------------------------------------*/

int running_away(){ /* true => successful*/
  /* 15% chance to flee */
  int chance=entier_aleatoire(1,100);
  printf("%d chance\n",chance );
  if(  chance < 15){
    printf("Vous arrivez à vous échapper...(-10 xp)\n" );
    Personnage->xp-=10;
    return 0;
  }
   clear_screen();
   printf("\n\n\n\n\nSorry, you have to fight...\n\n\n\n" );
   return 1;
}
