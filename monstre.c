#include <stdio.h>
#include <stdlib.h>
#include "perso.h"
#include "combat.h"

void allocating_monster_name(int level){
  int randomizer = 0;
  randomizer = rand() % 100;

  char monster_name[30][20] = {""}

  if(level > 8){
    switch(randomizer){
      case randomizer > 80 : (*monster)->name = "Dragon"; break;
      case randomizer > 60 : (*monster)->name = "Manticore"; break;
      case randomizer > 40 : (*monster)->name = "Terrible rabbit"; break; /*Monthy python :p*/
      case randomizer > 20 : (*monster)->name = "Gryffin"; break;
      case default : (*monster)->name = "Minotaur"; break;
    }
  }
  else if(level > 6){
    switch(randomizer){
      case randomizer > 80 : (*monster)->name = "Dark troll"; break;
      case randomizer > 60 : (*monster)->name = "Dark elf"; break;
      case randomizer > 40 : (*monster)->name = "Black wizard"; break;
      case randomizer > 20 : (*monster)->name = "Oger"; break;
      case default : (*monster)->name = "Your angry mom"; break;
    }
  }
  else if(level > 4){
    switch(randomizer){
      case randomizer > 80 : (*monster)->name = "Ghost"; break;
      case randomizer > 60 : (*monster)->name = "Undead"; break;
      case randomizer > 40 : (*monster)->name = "Centaur"; break;
      case randomizer > 20 : (*monster)->name = "Troll"; break;
      case default : (*monster)->name = "Orc"; break;
    }
  }
  else{
    switch(randomizer){
      case randomizer > 80 : (*monster)->name = "Wolf"; break;
      case randomizer > 60 : (*monster)->name = "Snake"; break;
      case randomizer > 40 : (*monster)->name = "Skeleton"; break;
      case randomizer > 20 : (*monster)->name = "Goblin"; break;
      case default : (*monster)->name = "Thief"; break;
    }
  }
}


character_t* monster_creation(int level){
  character_t* monster= malloc(sizeof(character_t));
  monster->level=level;
  monster->name = allocating_monster_name(monster->level);
  monster->health=20*level;
  monster->mana=20*level;

  for(int i = 0;i<7;i++){
    monster->state[i] = 0;
  }
  monster->stat_intel = 3*level;
  monster->stat_stamina = 3*level;
  monster->stat_strength = 3*level;

  return monster;
}
/*appelle la fonc de creation de monstre et genere le niveau
dans un intervalle basé sur la position du joueur
*/
character_t* mob_generation(float X,float Y){
  character_t *monster = NULL;

  if(X > (map_size_x / 2) && Y > (map_size_y / 2)){
     /* monster=monster_creation(); with a rand 4-6 level paramater*/
  }
  else if(X < (map_size_x / 2) && Y > (map_size_y / 2)){
    /* monster=monster_creation(); with a rand 1-4 level paramater*/
  }
  else if(X > (map_size_x / 2) && Y < (map_size_y / 2)){
    /* monster=monster_creation(); with a rand 9-10 level paramater*/
  }
  else{
    /* monster=monster_creation(); with a rand 6-8 level paramater*/
  }
}
