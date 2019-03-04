#include <stdio.h>
#include <stdlib.h>
#include "perso.h"

object_t* create_object(character_t monster){ /*va vérifier la valeur de l objet */
   // state sera donnee par un rand dans une range celon la difficulte du mob
   object_t *new_item = malloc(sizeof(object_t));
   new_item->type_object = loot_type(monster);
   new_item->state_object = loot_state(new_item->type_object,monster);
   new_item->value_object = loot_value(new_item->type_object,new_item->state_object);
   return new_item;
}

void delete_object(object_t **item){
  free(*item);
  *item = NULL;
}

int loot_type(character_t monster){
  monster.level; //a voir plus tard
  int value = rand() % 100;
  if(value > 70){
    return 2;
  }
  else if(value > 15){
    return 1;
  }
  else{
    return 0;
  }
}

int loot_state(int type, character_t monster){
  switch(type){
    case 0 : {
              if(monster.level < 3)
                  return 0;
              else if(monster.level < 8){
                int value = (rand() % 3) + 1;
                return value;
              }
              else{
                return 4;
              }
              }; break;
    case 1 : return rand() % 5 ;break;
    case 2 : {
              if(monster.level < 3){
                return rand() % 2;
              }
              else if(monster.level < 8){
                return rand() % 9;
              }
              else{
                return (rand() % 12) + 2;
              }
            }break;
  }
}

int loot_value(int type, int state){
  int tab_armor[4] = {10,20,30,40};
  int tab_weapon[5] = {3,5,7,7,10};
  int tab_potion[14] = {30,30,1,2,3,4,5,6,30,70,70,70,7,8};

  switch(type){
    case 0: return tab_armor[state];break;
    case 1: return tab_weapon[state];break;
    case 2: return tab_potion[state];break;
  }
}

character_t* creation_char(){
    character_t* player=NULL;
    player = malloc(sizeof(character_t));
    printf("Insert your name : ");
    scanf("%s", player->name);
    printf("Choose a class for your character : \n");
    printf("warrior, wizard, hunter, priest \n");
    scanf("%s", player->class_char);
    player->xp=0;
    player->level=1;
    player->health=100;
    player->mana=100;

    for(int i = 0;i<7;i++){
      player->state[i] = 0;
    }
    player->stat_intel = 10;
    player->stat_stamina = 10;
    player->stat_strength = 10;
    player->accessory=green_amulet;                  /*green_amulet = 0*/
    player->char_armor.type_object = 0;   /*armure*/
    player->char_armor.state_object=0;   /*cloth*/

    player->char_weapon.type_object = 1; /*armure*/
    player->char_weapon.state_object=0;   /*dagger*/
    return player;
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

void delete_player(character_t* player){
    if(player != NULL){
      free(player);
      player=NULL;
   }

}

inventory_t create_or_delete_inventory(){
   inventory_t inventory;
   inventory.nb_objects =0;
   for(int i = 0;i<30;i++){
      inventory.object[i] = NULL;
   }

   return inventory;
}

int fill_up_inventory(inventory_t array_inventory,object_t* object) {

   if(array_inventory.nb_objects >= 30){ //si c est plein, on renvoie 0  car on peut pas faire un overbook
         return 0;
   }
   else{
      array_inventory.object[array_inventory.nb_objects] = object;
      array_inventory.nb_objects++;
   }
   return 1;
}

char* display_object(object_t object){

      char* etat;

      if(object.type_object ==0){      /*armure*/
         printf("objet armure = %d\n", object.state_object);
         switch (object.state_object) {

            case 0: etat = "cloth armor"; break;
            case 1: etat ="leather armor";  break;
            case 2: etat ="silver armor"; break;
            case 3: etat ="golden armor"; break;
         }
      }
      else if(object.type_object ==1){ /*weapon */
         switch (object.state_object) {
            case 0: etat ="dagger"; break;
            case 1: etat ="staff"; break;
            case 2: etat ="axe"; break;
            case 3: etat ="bow"; break;
            case 4: etat ="sword"; break;
         }
      }else{
            switch (object.state_object) {
               case 0: etat ="mana potion"; break;
               case 1: etat ="health potion"; break;
               case 2: etat ="anti poison potion"; break;
               case 3: etat ="anti silence potion"; break;
               case 4: etat ="anti blind potion"; break;
               case 5: etat ="anti silence potion"; break;
               case 6: etat ="anti stunt potion"; break;
               case 7: etat ="anti bleeding potion"; break;
               case 8: etat ="phoenix potion"; break;
               case 9: etat ="super mana potion"; break;
               case 10: etat ="super health potion"; break;
               case 11: etat ="super phoenix potion"; break;
               case 12: etat ="speed potion"; break;
               case 13: etat ="lucidity potion"; break;
            }
      }
      return etat;
}
void affich(character_t* perso){
   printf("nom perso %s\n", perso->name);
   printf("xp = %d\n", perso->xp);
   printf("level = %d\n", perso->level);
   printf("health = %d\n", perso-> health);
   printf("mana= %d\n", perso->mana);
   printf("state= %d\n", perso->state[0]);
   printf("stat_strength = %d \n", perso->stat_strength);
   printf("stat_intel= %d \n", perso->stat_intel);
   printf("stat_stamina= %d \n", perso->stat_stamina);
   printf("class_char= %s\n", perso->class_char);
   printf("accessoire= %d\n", perso->accessory);
   char* objet= display_object(perso->char_armor);
   char* objet2= display_object(perso->char_weapon);
   printf("armure = %s\n",objet);
   printf("arme = %s\n",objet2);
}
