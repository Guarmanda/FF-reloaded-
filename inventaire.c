
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

int loot_type(int level){

     int value = entier_aleatoire(1,100);
     printf("valeur aleatoire tirée pour l'objet %d [0=armure, 1= arme, 2 =potions]\n",value );
     if(value <15){              /* 15% de chance d avoir une armure */
       return armor;
    }else if(value < 30){        /* 30% de chance d avoir une arme*/
       return weapon;
     }else{
       return potion;        /* potion a 70% d etre lootée */

     }
}

int loot_state(int type, int level){

  switch(type){
       case armor : {
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
       case weapon : return rand() % 5 ;break;
       case potion : {
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
  int tab_armor[4] = {10,20,30,40}; /**/
  int tab_weapon[5] = {3,5,7,7,10};
  int tab_potion[14] = {30,30,1,2,3,4,5,6,30,70,70,70,7,8};

  switch(type){
       case 0: return tab_armor[state];break;
       case 1: return tab_weapon[state];break;
       case 2: return tab_potion[state];break;
  }
  return -1;   /*code d erreur*/
}

inventory_t* create_or_delete_inventory(){
   inventory_t* inventaire_partie= malloc(sizeof (inventory_t));

   inventaire_partie->nb_objects =0;
   int i;
   for( i = 0; i<30; i++){
      inventaire_partie->object[i] = NULL;
   }
   return inventaire_partie;

}
/*ajout d un objet dans l inventaire*/
int fill_up_inventory(inventory_t* inventory,object_t* object) {

   if(inventory->nb_objects >= 30){ /*si c est plein, on renvoie 0  car on peut pas faire un overbook*/
         return 0;
   }
   else{
      inventory->object[inventory->nb_objects] = object;
      inventory->nb_objects++;
   }
   return 1;
}


char* display_object(object_t object){ /*voir si il faut faire un free à la fin et ne rien retourner,
    comment gerer le malloc ici et dans le main par ex*/

      char* etat= malloc (sizeof(char)*20);

      if(object.type_object ==0){      /*armure*/
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
/*
void display_inventory(inventory_t* inventory){
   printf("vous avez dans votre inventaire:\n" );
   int total_objet= inventory->nb_objects;
   int i;

}
void delete_etat*/
