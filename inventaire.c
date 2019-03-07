#include <stdio.h>
#include <stdlib.h>
#include <inventaire.h>

object_t* create_object(int level){ /*va vérifier la valeur de l objet */
   /* state sera donne par un rand dans une range selon la difficulte du mob monstre->level*/
   object_t *new_item = malloc(sizeof(object_t));
   new_item->type_object = loot_type(level);
   new_item->state_object = loot_state(new_item->type_object,level);
   new_item->value_object = loot_value(new_item->type_object, new_item->state_object);

   return new_item;
}

void delete_object(object_t **item){
  free(*item);
  *item = NULL;
}

int loot_type(int level){        /*si niv 10*/

     int value = rand() % 100;
     printf("valeur %d\n",value );
     if(value <15){
       return 0;              /* armor */
     }else if(value < 30){
       return 1;            /* weapon*/
     }else{
       return 2;        /* potion a 70% d etre lootée */
     }
}

int loot_state(int type,int level){

  switch(type){
       case 0 : {
                 if(level < 3)
                     return 0;
                 else if(level < 8){
                   int value = (rand() % 3) + 1;
                   return value;
                 }
                 else{
                   return 4;
                 }
                 }; break;
       case 1 : return rand() % 5 ;break;
       case 2 : {
                 if(level < 3){
                   return rand() % 2;
                 }
                 else if(level < 8){
                   return rand() % 9;
                 }
                 else{
                   return (rand() % 12) + 2;
                 }
               }break;
     }
     return -1; /*voir code d erreur */
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
  return -1;   /*code d erreur*/
}

inventory_t create_or_delete_inventory(){
   inventory_t inventory;
   inventory.nb_objects =0;
   int i;
   for( i = 0; i<30; i++){
      inventory.object[i] = NULL;
   }

   return inventory;
}
/*ajout d un objet dans l inventaire*/
int fill_up_inventory(inventory_t array_inventory,object_t* object) {

   if(array_inventory.nb_objects >= 30){ /*si c est plein, on renvoie 0  car on peut pas faire un overbook*/
         return 0;
   }
   else{
      array_inventory.object[array_inventory.nb_objects] = object;
      array_inventory.nb_objects++;
   }
   return 1;
}

char* display_object(object_t object){

      char* etat= malloc (sizeof(char)*20);

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
               case 6: etat ="anti stunt potion"; break;
               case 7: etat ="anti bleeding potion"; break;
               case 8: etat ="anti slow potion"; break;
               case 9: etat ="anti silence potion"; break;
               case 10: etat ="anti poison potion"; break;
               case 11: etat ="anti blind potion"; break;
               case 12: etat ="speed potion"; break;
               case 13: etat ="lucidity potion"; break;
            }
      }
      return etat;
}

/*void delete_etat*/
