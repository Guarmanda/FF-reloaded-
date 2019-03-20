#include <stdio.h>
#include <stdlib.h>

#include <combat.h>

int x_coord=500;
int y_coord=500;


/*menu principal du combat*/

int combat_on(character_t **player, inventory_t *inventory, int* xp_temp){

   int monster_number = entier_aleatoire(1,4); /*nb de monstre qui fera partie du combat*/
   printf("vous êtes aux coordonnees %d et %d\n", x_coord,y_coord);
   printf("il y a %d monstres\n",monster_number );

   character_t * monster[monster_number];   /*tableau de monstre généré*/

   int i;
   for( i = 0; i < monster_number;i++){
      monster[i] = NULL;
      monster[i] = monster_creation(1);  /*faut mettre les coordonnees */

   }

   int etat=1;

   do{
      printf("\t\t%s %d\n",(*player)->name, (*player)->health);
      etat= affich_choix();

      switch (etat) {
         case 1: attaque_joueur(*player,monster,monster_number); break;  /*afficher les monstres à chaque tour*/
         case 2: taking_potion(&(*player),inventory); break;  /*afficher les monstres à chaque tour*/
         case 3: break;
         case 4: etat = running_away(player);break;
      }

      for( i = 0; i < monster_number; i++){

         if(is_dead (monster[i]) ){
            printf("\n\n\t\t%s est mort...\n\n", monster[i]->name);
            (*xp_temp)+= xp_points((*player),*monster[i]); /*ajout des points d experience au joueur*/

            printf("XP GAGNEY MONSTRE MORT %d\n", (*xp_temp) );
            update_tab_monster(monster ,i , monster_number);
            delete_player(&monster[monster_number-1]);
            monster_number--;
         }
      }
      for( i = 0; i < monster_number;i++){
         attack(monster[i], player);
      }
      printf("etat %d\n",etat );
   }while( etat != 0 && etat != 5 && monster_number >0 && !is_dead(*player) );

   if(!monster_number){
      printf("vous avez gagné %d d' xp\n",*xp_temp );
      (*player)->xp += *xp_temp;
      printf("vos nouveaux points d 'xp = %d\n",(*player)->xp);
      printf("vous avez le niveau %d \n", (*player)->level);
      if(levelling(*player)){
         printf("vous avez atteint le niveau %d \n",(*player)->level);
      }
   }else
      printf("GAME OVER...\n" );
   printf("fin du combat\n" );
   return 1;
}


void attaque_joueur(character_t* player,character_t* tab_monstre[], int nb_monstre){ /*tableau de monstre en param*/
   int i;
   int choix_j;
   printf("Quel monstre choisissez-vous? \n");

   for( i = 0; i < nb_monstre;i++){
      printf("\t adversaire %d : %s (vie: %d/%d)\t",i+1, tab_monstre[i]->name,tab_monstre[i]->health, tab_monstre[i]->max_health);
      printf("\n");
   }
   do{
      printf("\nnombre de monstre %d\n",nb_monstre );
      scanf("%d",&choix_j );

   }while((choix_j-1) > nb_monstre || (choix_j-1) <0);

   printf("monstre %s choisi\n", tab_monstre[choix_j-1]->name);
/*   affich(tab_monstre[choix_j-1]);*/
   attack(player,&tab_monstre[choix_j-1]);
   /* affich(tab_monstre[choix_j-1]);*/

}
int affich_choix(){

         int player_choice = 0; /* voir plus tard pour que le joueur puisse selectionner dans le menu */

         do{
              printf("Vous êtes en combat, choisir entre les actions ci-dessous:\n" );
              printf(" 1 - Attaquer l'adversaire\n");
              printf(" 2 - Prendre une potion\n");
              printf(" 3 - Appliquer un sort\n");
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
   printf("%s == ATTAQUE ==> %s ...\n",attacker->name,(*target)->name);

   int degat = (attacker->stat_strength) * (attacker->char_weapon.value_object);

   ((*target)->health) -= degat;
   printf("%d de dégats causés à %s  \n", degat,(*target)->name);

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

/* t_chance = pourcentage contenu dans une matrice (niveau de menace)*/
/*fonction qui va etre appelée à chaque combat*/
int fight_rand(int fight_chance,character_t **player, inventory_t inventaire){

   int trap= entier_aleatoire(1,100);

   if(trap <= fight_chance){
      int etat_combat;
      int xp_fight=0;


   }
   printf("vous l'avez echappée belle! ;)\n");
   return OK;
}


/*-------------------------------------------------------------*/

int running_away(character_t** player){ /* true => successful*/
  /* 15% chance to flee */

  if( entier_aleatoire(1,100) < 15){
    printf("Vous arrivez à vous échapper...\n" );
    (*player)->xp-=10;
    return 0;
  }
   printf("Sorry, you have to fight...\n" );
   return 1;
}
void casting_spell( character_t* wizard,character_t **target, spell_t spell){
  if(spell.spell_type == 0){ /* offensif*/
    (*target)->health -= wizard->stat_intel * spell.spell_value;
  }
  else if(spell.spell_type == 1){ /* soin*/
    (*target)->health += wizard->stat_intel * spell.spell_value;
  }
  else{ /* state modifier*/
    apply_state_modifier(target,spell.spell_value,VRAI);
  }
}



void apply_state_modifier(character_t **target, int value, int off_or_on){

  if(off_or_on == VRAI){
    (*target)->state[value] = FAUX;
  }else{

    (*target)->state[value] = VRAI;
  }
}


void taking_potion(character_t **player,inventory_t* inventaire){ /*true if it works, otherwise false*/

   int choix=1;

   int i;
   do{

      for( i =0; i< inventaire->nb_objects ; i++){
         char* temp =display_object(*inventaire->object[i]);
         printf("objet %d => %s\n",i+1, temp );
      }
      printf("quel objet voulez-vous prendre? [-1 pour sortir du menu] " );
      scanf("%d", &choix);
      choix--;

      printf("vous avez choisi\n" );
      char* temp =display_object(*inventaire->object[choix]);
      printf("objet %d => %s\n",choix+1, temp );

      if(inventaire->object[choix] != NULL){

         object_t* choix_potion= inventaire->object[choix];
         printf("\n\t\tvotre mana est de %d/%d \n",  (*player)->mana,(*player)->max_mana);
         printf("\n\t\tvotre vie est de %d/%d \n",  (*player)->health, (*player)->max_health);

         if(choix_potion->type_object == potion) {   /*on rentre dans le cas général des potions*/

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
            choix=0;

         }else{
               printf("l objet choisi n'est pas une potion ou un objet qui peut être utilisé maintenant...\n");
         }
      }else
         printf("l objet choisi n'existe pas...\n" );


   }while (choix!= -1 || choix!= 0);

}

int is_dead(character_t *target){ /* rip :(*/

  return (target->health <= 0); /*retourne 0 = il est vivant*/

}
