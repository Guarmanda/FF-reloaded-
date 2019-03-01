#include <stdio.h>
#include <stdlib.h>
#include "perso.h"

int affect_value(int val, object_t object){ /*va vérifier la valeur de l objet */
   return val;
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

int fill_up_inventory(inventory_t array_inventory,void* object) {

   if(array_inventory.nb_objects >= 30){
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
               case 1: etat ="super mana potion"; break;
               case 2: etat ="health potion"; break;
               case 3: etat ="super health potion"; break;
               case 4: etat ="phoenix potion"; break;
               case 5: etat ="super phoenix potion"; break;
               case 6: etat ="anti poison potion"; break;
               case 7: etat ="anti silence potion"; break;
               case 8: etat ="anti blind potion"; break;
               case 9: etat ="anti silence potion"; break;
               case 10: etat ="anti stunt potion"; break;
               case 11: etat ="anti bleeding potion"; break;
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
