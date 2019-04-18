#include <combat.h>


EVASION = 15;
/*fonction principale du combat qui gère tous les interventants et leurs attributs*/

int combat_on(character_t **player, inventory_t *inventory){
   int choix_j=1; /*variable qui récupère l option choisie par le joueur lorsqu'il est tombé en combat */
   int xp_temp=0; /*les xp qui sont récupérés lors du combat si le joueur a gagné*/
   int retour_menu=1;  /*retour_menu sert à revenir au début du menu si le joueur a mal fait son choix*/

   /*définition des participants du combat*/
   int monster_number = entier_aleatoire(1,MAX_NB_MONSTRE); /*nb de monstre qui fera partie du combat*/
   character_t * monster[monster_number];   /*tableau de monstre généré*/

   int i;
   for( i = 0; i < monster_number;i++){
      monster[i] = NULL;
      monster[i] = monster_creation();
   }
   clear_screen();
   printf("Vous êtes piégé !\n\n");
   sleep(1);

   /*début des actions qui s'enchaîneront*/
   do{
      for( i = 0; i < monster_number;i++){
        printf("\tAdversaire %d : %s (vie: %d/%d ; niveau : %d)\n",i+1, monster[i]->name,monster[i]->health, monster[i]->max_health, monster[i]->level);
      }
      printf("\n\tJoueur: %s (vie: %d/%d ; niveau : %d)\n",Personnage->name,Personnage->health, Personnage->max_health, Personnage->level);
      choix_j= affich_choix();
      retour_menu= tour_joueur(choix_j,monster,monster_number);
      if(retour_menu != 0 ){


         for( i = 0; i < monster_number; i++){

            if(is_dead (monster[i]) ){
               printf("\n\t%s %d meurt...", monster[i]->name,i+1);
               int check_xp= xp_points(Personnage,*monster[i]);
               /*ajout des points d experience au joueur = effectif QUE si on gagne le combat*/
               xp_temp += check_xp;
               update_tab_monster(monster ,i , monster_number);
               monster_number--;
            }
         }
          /*à changer pour faire en sorte que il y ait une fonction qui fasse jouer le monstre*/
         for( i = 0; i < monster_number;i++)
            attack(monster[i], &Personnage);

      }

   }while( retour_menu != FUITE && monster_number >0 && !is_dead(Personnage) );

   if(!monster_number){

      Personnage->xp += xp_temp;
      printf("Vous avez gagné %d d'XP...\nVos xp : %d\n",xp_temp,Personnage->xp);

      if(levelling(Personnage)){
         sleep(1);
         clear_screen();
         printf("Vous avez atteint le niveau %d \n",Personnage->level);
      }

   }else if(is_dead(Personnage)){
      printf("GAME OVER...\n");
      etat_jeu=END_OF_GAME;
   }

   for(i =0; i <monster_number ; i++){

     delete_player(&monster[i]);
     printf("on delete le monstre %d\n",i+1 );
   }
   printf("on va sortir\n" );
   return etat_jeu;

}

static int choisir_monstre(character_t* tab_adv[], int nb_monstre){
     int choix_j;
     int i;
     do{
        printf("Quel adversaire choisissez-vous? [0 pour retourner au menu précédent]\n");
        for( i = 0; i < nb_monstre; i++){
           printf("\tAdversaire %d : %s (vie: %d/%d)\n",i+1, tab_adv[i]->name,tab_adv[i]->health, tab_adv[i]->max_health);

        }
        printf("Votre choix: " );
        scanf("%d",&choix_j);
        viderBuffer();
     }while (choix_j > nb_monstre || choix_j< 0);
     return choix_j;
     printf("apres leeee choix\n" );
}

static void maj_mana(character_t* perso, int val_sort){
    perso->mana -= val_sort;
}
/*à faire*/
static void apply_auto_spell(character_t* perso){

  int chance=entier_aleatoire(1,6);
  int i;
  for(i = 0 ; i <chance;i++ )
     perso->state[i]=FAUX;
}
static void affich_changement_etat(character_t* perso, int valeur_etat){

    switch (valeur_etat) {
      case 0: printf("%s est étourdi...\n",perso->name ); break;
      case 1: printf("%s saigne...\n",perso->name ); break;
      case 2: printf("%s est un peut lent...\n",perso->name ); break;
      case 3: printf("%s est privé d'utiliser ses sorts\n",perso->name ); break;
      case 4: printf("%s s'est fait empoisonné\n",perso->name ); break;
      case 5: printf("%s est aveugle... \n",perso->name ); break;
      case 6: printf("%s dort...\n",perso->name ); break;
    }
}
void apply_spell(character_t* attacker,character_t **target, int sort_choisi){

    printf("\n\n\t<> %s <> ==============> %s ...\n",tab_sort[sort_choisi].nom_sort,(*target)->name);
    sleep(1);

    if(tab_sort[sort_choisi].type_sort == modifie_etat){
      apply_state_modifier(&(*target),tab_sort[sort_choisi].valeur_sort);
      affich_changement_etat((*target),tab_sort[sort_choisi].valeur_sort);

    }else{

      int degat = (attacker->stat_intelligence) * tab_sort[sort_choisi].valeur_sort;

      ((*target)->health) -= degat + (*target)->accessory ;

      if(is_dead(*target)){
         ((*target)->health)=0;
      }
      printf("\t%d de dégats causés à %s (%d/%d)\n\n", degat,(*target)->name,(*target)->health, (*target)->max_health );
    }
    maj_mana(attacker, tab_sort[sort_choisi].valeur_sort);
}

int tour_joueur( int choix_j, character_t* tab_monstre[], int nb_monstre){

   int retour_menu=1;

   switch (choix_j){
      case 1: {
                retour_menu = choisir_monstre(tab_monstre,nb_monstre); /*il n'y a qu'une attaque donc on choisit une cible, si on veut*/
                if(retour_menu != 0)
                  attack(Personnage,&tab_monstre[retour_menu-1]);
              }; break;
      case 2: retour_menu = taking_potion(); break;
      case 3: {
                int sort_choisi;
                sort_choisi=joueur_sort(Personnage);  /*renvoie -1 si le personnage n a pas de sort */

                if(sort_choisi > -1){

                     if(tab_sort[sort_choisi].type_sort != defensif){

                        retour_menu = choisir_monstre(tab_monstre,nb_monstre);
                        apply_spell(Personnage,&tab_monstre[retour_menu-1], sort_choisi);

                    }else
                        apply_auto_spell(Personnage);

                }else
                  retour_menu = 0;  /*on retourne au menu puisqu il a pas de sort*/

              };break;
      case 4: retour_menu = running_away();break; /*renvoie FUITE (-10 )si on s echappe*/
      case 5: exit(1);
   }
   if(retour_menu == 0){
        printf("Retour au menu précédent...\n");
        sleep(1);
        clear_screen();
   }
   return retour_menu;

}

int affich_choix(){

         int player_choice = 0;

         do{

              sleep(1);
              printf("Choisir entre les actions ci-dessous:\n\t1 - Attaquer l'adversaire\n\t2 - Prendre une potion\n\t3 - Appliquer un sort\n\t4 - S'évader\n\t5 - Quitter le jeu\nVotre choix : ");
              scanf("%d",&player_choice);
              viderBuffer();
         }while(player_choice > 5 || player_choice <1);

         return player_choice;
}
/*si un monstre est mort pendant le combat, on va devoir faire en sorte qu il soit supprimé du tableau*/
void update_tab_monster(character_t *monster_array[],int index, int nb_monstre){

    int i;
    affich_stats(monster_array[index]);
    delete_player(&monster_array[index]);
    for( i = index; i <  nb_monstre-1 ; i++){
      monster_array[i] = monster_array[i+1];
    }

}

void attack(character_t* attacker,character_t **target){

   printf("\n\t%s ATTAQUE ==============> %s ...\n",attacker->name,(*target)->name);
   sleep(2);

   int degat = (attacker->stat_strength) * (attacker->char_weapon->value_object);

   ((*target)->health) -= degat + (*target)->accessory ;

   if(is_dead(*target)){
      ((*target)->health)=0;
   }
   printf("\t%d de dégats causés à %s (%d/%d)\n\n", degat,(*target)->name,(*target)->health, (*target)->max_health );

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

      int xp_par_niveau = 10; /*variable qui peut definir l evolution du perso dans tout le jeu ou monstre.stat_strength*/
      return (xp_par_niveau * monster.level);

}

void fight_rand(){

   int trap=0;
   if (Personnage->accessory != evite_combats){
      trap= entier_aleatoire(1,100);
   }else
      trap= entier_aleatoire(51,100);

   int chances= map_threat[position_x][position_y];

   if(trap <= chances){
      etat_jeu = EN_COMBAT;
      combat_on(&Personnage,Inventaire);
   }

}


/*marche inversement aussi, si on met un Antidote on va juste inverser l etat*/
void apply_state_modifier(character_t ** target, int indice){

    (*target)->state[indice] = ( (*target)->state[indice] == FAUX ? VRAI : FAUX ) ;

}

/*-------------------------------------------------------------*/

int running_away(){ /* true => successful*/
  /* 15% chance to flee */
  int chance=entier_aleatoire(1,100);
  printf("%d chance\n",chance );
  if(  chance < EVASION ){
    printf("Vous arrivez à vous échapper...(-10 xp)\n" );
    Personnage->xp-=10;
    etat_jeu=HORS_COMBAT;

  }else
      printf("\n\nSorry, you have to fight...\n" );

   return (chance < EVASION ? FUITE : 1);
}
