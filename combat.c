#include <stdio.h>
#include <stdlib.h>
#include "perso.h"
#include "combat.h"

#define map_size_x 1000
#define map_size_y 1000

typedef enum {true,false}booleen;

void casting_spell(character_t wizard,character_t **target, spell_t spell){
  if(spell.spell_type == 0){ // offensif
    (*target)->health -= wizard.stat_intel * spell.spell_value;
  }
  else if(spell.spell_type == 1){ // soin
    (*target)->health += wizard.stat_intel * spell.spell_value;
  }
  else{ // state modifier
    apply_state_modifier(target,spell.spell_value,true);
  }
}

/* fight_chance = pourcentage contenu dans une matrice (niveau de menace)*/

void fight_rand(int fight_chance,character_t **player){
  if((rand() % 100 + 1) <= fight_chance){
    fight(player);
  }
}


void attack(character_t attacker,character_t **target){
  (*target)->health -= attacker->stat_strength * attacker.char_weapon.value;
}

void apply_state_modifier(character_t **target, int value, int off_or_on){
  if(off_or_on = true){
    (*target)->state[value] = false;
  }
  else{
    (*target)->state[value] = true;
  }
}

int taking_potion(character_t **player,object_t potion){ /*true if it works, otherwise false*/
  if(potion.type == 2){
      if(potion.state <= 1){ // mana potion
        (*player)->mana += (*player)->mana_max * (potion.value / 100);
        // making sure we don't give the player too much health
        if((*player)->mana > (*player)->mana_max){
          (*player)->mana = (*player)->mana_max;
        }
      }
      else if(potion.state <= 3){ // health potion
        (*player)->health += (*player)->health_max * (potion.value / 100);
        // making sure we don't give the player too much health
        if((*player)->health > (*player)->health_max){
          (*player)->health = (*player)->health_max;
        }
      }
      else if(potion.state <= 3) // pheonix potion, not implemented yet
      else if(potion.state <= 4){
        apply_state_modifier(player,potion.value,true);
      }
      else{
        /* lucidiy and speed*/
      }
      return true;
  }
  return false;
}

int is_dead(character_t *target){ /* rip :(, return true if dead else false*/
  if((*target)->health <= 0){
    return 1;
  }
  return 0;
}

void update_tab_monster(character_t *monster_array[],int index){ /* swap monster place in an array*/
  for(int i = index;i<monster_number-1;i++){
    monster_array[i] = monster_array[i+1];
  }
}

int running_away(character_t player,character_t monster){ // true => successful
  /* 15% chance to flee */
  if(((rand() % 100) / 100) < 0.15){
    return true;
  }
  else{
    return false;
  }
}

void player_action(character_t **player,character_t * monster, inventory_t *inventory){
    int player_choice = 0; /* player selection in the menu */
    switch(player_choice){
      case 1 : attack(player,monster);break;
      case 2 : taking_potion(player,inventory->object[selection]);break; /*not done*/
      case 3 : break; /*not done*/
      case 4 : break;
    }
}

int fight(character_t **player, inventory_t *inventory){ // return true if the player win, else false, -1 if you flee
  /* display fight scene */
  /* generating monster */
  int monster_number = rand() % 4 + 1;
  character_t *monster[monster_number];
  for(int i = 0; i<monster_number;i++){
    monster[i] = mob_generation(X,Y);
  }

  do{
    /*Insert player action*/
    player_action(player,monster,inventory);

    /* checking if monsters are dead */
      for(int i = 0;i<monster_number;i++){
        if(is_dead(monster[i])){
          update_tab_monster(monster,i);
          free(monster[monster_number]);
          monster_number--;
        }
      }

    /*Insert monster(s) action(s), at the moment attack only*/

    for(int i = 0;i<monster_number;i++){
      attack(monster[i],player);
    }
  }while(!is_dead(*player) && monster_number > 0);

  if(is_dead(*player)){
    return false;
  }
  else{
    return true;
  }
}
