#include <stdio.h>
#include <stdlib.h>

#include <combat.h>

/*partie des tests de l inventaire*/

char* allocating_monster_name(int level){
     int randomizer = 0;
     randomizer = rand() % 100+1;
     printf("randomize = %d\n",randomizer );

     char* monster_name= malloc(sizeof(char)*40);

     if(level > 8){

         if (randomizer > 80) {
            strcpy(monster_name, "Dragon");
         }
         else if (randomizer > 60){
            strcpy(monster_name, "Manticore");
         }
         else if  (randomizer > 40){
            strcpy(monster_name,"Terrible r");
         }
         else if  (randomizer > 20){
            strcpy(monster_name,"Gryffin");
         }
         else
            strcpy(monster_name,"Minotaur");

       }else if(level > 6){

         if (randomizer > 80) {
           strcpy(monster_name,"Dark troll");
         }
         else if (randomizer > 60){
           strcpy(monster_name,"Dark elf");
         }
         else if  (randomizer > 40){
           strcpy(monster_name,"Black wizard");
         }
         else if  (randomizer > 20){
           strcpy(monster_name,"Oger");
         }
         else
            strcpy(monster_name,"Your aaa");
       }else if(level > 4){
           if (randomizer > 80) {
             strcpy(monster_name,"Ghost");
         }
         else if (randomizer > 60){
          strcpy(monster_name,"Undead");
         }
         else if  (randomizer > 40){
           strcpy(monster_name,"Centaur");
         }
         else if  (randomizer > 20){
          strcpy(monster_name,"Troll");
         }
         else
            strcpy(monster_name, "Orc");

         }else{
           if(randomizer > 80) {
            strcpy(monster_name,"Wolf");
           }
         else if(randomizer > 60){
             strcpy(monster_name,"Snake");
         }
         else if(randomizer > 40){
            strcpy(monster_name,"Skeleton");
         }
         else if  (randomizer > 20){
            strcpy(monster_name, "Goblin");
         }
         else
            strcpy(monster_name,"Thief");
         }
         printf("le nom du monstre %s\n",monster_name );
   return monster_name;
}

character_t* monster_creation(int level){
  character_t* monster= malloc(sizeof(character_t));
  monster->level=level;
  char* nom_temp= allocating_monster_name(monster->level);
  strcpy(monster->name,nom_temp);
  monster->health=20*level;
  monster->mana=20*level;
  int i;
  for(i = 0;i<7 ;i++){
    monster->state[i] = 0;
  }
  monster->stat_intel = 3*level;
  monster->stat_stamina = 3*level;
  monster->stat_strength = 3*level;

  return monster;
}



/*-------------------------------------------------------------*/
void casting_spell(character_t* wizard,character_t **target, spell_t spell){
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

/* t_chance = pourcentage contenu dans une matrice (niveau de menace)*/
/*fonction qui va etre appelée à chaque combat*/
void fight_rand(int fight_chance,character_t **player, inventory_t inventaire){
   int trap=( rand() % 100 + 1 );
   printf("on est en combat et trap = %d\n", trap);

   if(trap <= fight_chance){

      begin_fight(player,&inventaire);   /*inventaire va etre modifié si le joueur veut accéder à ses potions et autres*/

   }else
      printf("il l' a echappée belle! ;)\n");
}

void attack(character_t* attacker,character_t **target){
   printf("%s attaque %s ...\n",attacker->name,(*target)->name);
  int degat=(attacker->stat_strength) * (attacker->char_weapon.value_object);
  ((*target)->health) -= degat;
  printf("%d de dégats causés à %s  \n", degat,(*target)->name);
}

void apply_state_modifier(character_t **target, int value, int off_or_on){
  if(off_or_on == VRAI){
    (*target)->state[value] = FAUX;
  }else{

    (*target)->state[value] = VRAI;
  }
}


int taking_potion(character_t **player,inventory_t* inventaire){ /*true if it works, otherwise false*/
  int choix;
  printf("seule potion choisie\n");
  choix=0;  /*changer le choix*/
  object_t* choix_potion= inventaire->object[choix];


    printf("la mana avant = %d\n",  (*player)->mana);
     if(choix_potion->type_object == 2){   /*on rentre dans le cas général des potions*/
         float pourcentage = choix_potion->value_object/100.0;
         printf("choix_potion->type_object = %d\n", choix_potion->type_object);
         if(choix_potion->state_object <= 1){  /*on rentre dans le cas où c est une potion mana: 0 à 1*/


           (*player)->mana += (*player)->max_mana * pourcentage;
           (*player)->mana = ((*player)->mana  > (*player)->max_mana)? (*player)->max_mana: (*player)->mana;

         }
         else if(choix_potion->state_object <= 3){ /*potion de vie: 2 à3*/

             (*player)->health += (*player)->max_health * pourcentage ;
             (*player)->health = ((*player)->health > (*player)->max_health)? (*player)->max_health:(*player)->health ;

          }else if(choix_potion->state_object <= 5){

                  apply_state_modifier(player,choix_potion->value_object,VRAI);

           }else if(choix_potion->state_object <= 13){
              apply_state_modifier(player,choix_potion->value_object,VRAI);
          }
         return VRAI;
     }else
       return FAUX; /*cas ou l objet n est pas une potion*/
}

int is_dead(character_t *target){ /* rip :(*/

  return (target->health <= 0); /*retourne 0 = il est vivant*/

}

void update_tab_monster(character_t *monster_array[],int index, int nb_monstre){ /* swap monster place in an array*/
  int i;
  for( i = index ;i < nb_monstre ;i++){ /* -1 pour monsternumber?*/
    monster_array[i] = monster_array[i+1];
  }
}

int running_away(character_t player,character_t monster){ /* true => successful*/
  /* 15% chance to flee */
  if(((rand() % 100) / 100) < 0.15){
    return VRAI;
  }
  else{
    return FAUX;
  }
}

void player_action(character_t **player, character_t ** monster, inventory_t *inventory){

    int player_choice = 0; /* voir plus tard pour que le joueur puisse selectionner dans le menu */
    int n=1;
    do{
      printf(" Choisir entre les actions ci-dessous:\n" );
		printf(" 1 - Attaquer l'adversaire\n");
      printf(" 2 - Prendre une potion\n");
		printf(" 3 - mystere\n");
		printf(" 4 - mystere2\n");
		printf(" 5 - Quitter\n");
		printf("Votre choix : ");
		scanf(" %i",&player_choice);

		/* Traitement du choix de l'utilisateur */
		switch(player_choice){
         case 1:  attack(*player,monster);break;
			case 2:  taking_potion(player,inventory);break;
			case 3:  printf("oui oui\n"); break; /*not done*/
			case 4:  printf("non \n"); break;
			case 5:  break;
			default: printf("Erreur: votre choix doit etre compris entre 1 et 5\n");
		}
         n--;

	}

	while(n);

}

int begin_fight(character_t **player, inventory_t* inventory){ /* return true if the player win, else false, -1 if you flee*/
  /* display fight scene */
  /* generating monster */

  int monster_number = rand() % 4 + 1; /*nb de monstre qui fera partie du combat*/
  printf("il y a %d monstres\n",monster_number );
  character_t * monster[monster_number];   /*tableau de monstre généré*/

    int i;
    for( i = 0; i < monster_number;i++){
      monster[i] = monster_creation(1);  /*faut mettre le niveau */
      printf("monstre %d ...\n",i+1 );
      affich(monster[i]);
    }

    do{
      /*Insert player action*/
      for( i = 0; i < monster_number;i++){
        printf("%s\n", monster[i]->name);
      }
      int choix_j;
      printf("choisir quel monstre frappey\n" );
      scanf("%d",&choix_j );
      printf("monstre %s choisi \n", monster[choix_j-1]->name);
      player_action(player,& (monster[choix_j-1]),inventory);  /*appel pour un coup du joueur*/
      printf("etat du monstre après tour \n");
      affich(monster[choix_j-1]);
      /* checking if monsters are dead */
      for( i = 0;i<monster_number;i++){
          if(is_dead (monster[i]) ){
            update_tab_monster(monster,i,monster_number);
            free(monster[monster_number]);  /*delete player = monstre (appeler la fonction qui delete le joueur)*/
            monster_number--;
          }
        }

      /*Insert monster(s) action(s), at the moment attack only*/

      for( i = 0;i< monster_number;i++){

         attack(monster[i],player);
      }
    }while(!is_dead(*player) && monster_number > 0);

    if(is_dead(*player)){
      return FAUX;
    }
    else{
      return VRAI;
    }
}

void levelling(character_t* player, character_t monster){
         /*à priori le nb de monstres est variables (nb param variables)*/
      int cap_xp = 50;
      int cap_reward = 50;
      player->xp += cap_xp * monster.level;
      if(player->xp >= (cap_reward * player->level)){
         player->level++;
      }
}
