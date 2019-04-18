#include <inventaire.h>

static int loot_type(int niveau_adversaire){

     int type_random = entier_aleatoire(1,100);

     if(type_random <5){              /* 5% de chance d avoir une armure */
       return armor;
     }else if(type_random < 15){        /* 15% de chance d avoir une arme*/
       return weapon;
     }else if(type_random < 30){        /* 30% de chance d avoir une arme*/
       return tente;
     }else{
       return potion;        /* type potion a 70% d etre lootée */
     }
}

static int loot_state(int type, int niveau_adversaire){

  switch(type){
      case armor : {
                     if(niveau_adversaire < 3)
                         return 0;
                     else if(niveau_adversaire < 8){
                         return entier_aleatoire(1,2);
                     }
                     else
                        return 3;
       }; break;
      case weapon : return entier_aleatoire(1,4) ;break; /*voir comment gérer les classes avec les loots*/
      case potion : {
                     if(niveau_adversaire < 3){
                       int rand=entier_aleatoire(0,2);
                       return rand ;
                     }
                     else if(niveau_adversaire < 8){
                       int rand=entier_aleatoire(3,13);
                       return rand ;/*voir si ok*/

                     }
                    /* else{
                       return entier_aleatoire(0,14);
                       return (rand() % 12) + 2;
                     }*/
      }break;
      case tente: return 0; break;
     }
     return KO_state ;
}
/*regarde quelle sera la valeur de l objet*/
int value(int type, int state){
  int tab_armor[4] = {10,20,30,40}; /*les valeurs sont des pourcentages*/
  int tab_weapon[5] = {3,5,7,7,10};
  int tab_potion[14] = {30,70,30,70,30,70,Stunt,Bleed,Slow,Silence,Poison,Blind,Speed,Sleep};
  int tab_objet[1]={100}; /*pour la tente*/

  switch(type){
       case armor: return tab_armor[state];break;
       case weapon: return tab_weapon[state];break;
       case potion: return tab_potion[state];break;
       case tente: return tab_objet[state]; break;
  }
  return KO_state;   /*code d erreur si aucun cas de type connu*/
}

void affectation_object(object_t* object){

       object->value_object= value(object->type_object, object->state_object);

       if(object->type_object ==armor){      /*type armure*/

         switch (object->state_object) {

            case 0: creer_string(&object->name_object,"cloth armor"); break;
            case 1: creer_string(&object->name_object,"leather armor");  break;
            case 2: creer_string(&object->name_object,"silver armor"); break;
            case 3: creer_string(&object->name_object,"golden armor"); break;
         }
      }
      else if(object->type_object == weapon){ /*weapon */

         switch (object->state_object) {
            case 0: creer_string(&object->name_object,"dagger"); break;
            case 1: creer_string(&object->name_object,"staff"); break;
            case 2:  creer_string(&object->name_object,"axe"); break;
            case 3:  creer_string(&object->name_object,"bow"); break;
            case 4:  creer_string(&object->name_object,"sword"); break;
         }
      }else if(object->type_object == tente){ /*pour la tente qui fait la sauvegarde */

          creer_string(&object->name_object,"tent");

      }else{

            switch (object->state_object) {
               case 0: creer_string(&object->name_object,"mana potion"); break;
               case 1: creer_string(&object->name_object,"super mana potion"); break;
               case 2: creer_string(&object->name_object,"health potion"); break;
               case 3: creer_string(&object->name_object,"super health potion"); break;
               case 4: creer_string(&object->name_object,"phoenix potion"); break;
               case 5: creer_string(&object->name_object,"super phoenix potion"); break;
               case 6: creer_string(&object->name_object,"anti stunt potion"); break;
               case 7: creer_string(&object->name_object,"anti bleeding potion"); break;
               case 8: creer_string(&object->name_object,"anti slow potion"); break;
               case 9: creer_string(&object->name_object,"anti silence potion"); break;
               case 10: creer_string(&object->name_object,"anti poison potion"); break;
               case 11: creer_string(&object->name_object,"anti blind potion"); break;
               case 12: creer_string(&object->name_object,"speed potion"); break;
               case 13: creer_string(&object->name_object,"lucidity potion"); break;

            }
      }

}
object_t* create_loot(int niv_monstre){ /*va vérifier la valeur de l objet */
   /* state sera donne par un rand dans une range selon la difficulte du mob monstre->level*/

   object_t * new_item = malloc(sizeof(object_t));
   new_item->type_object = loot_type(niv_monstre);
   new_item->state_object = loot_state(new_item->type_object,niv_monstre);
   new_item->value_object = value(new_item->type_object, new_item->state_object);
   affectation_object(new_item);
   return new_item;
}

object_t* create_object(int type, int etat){ /*va vérifier la valeur de l objet */
   /* state sera donne par un rand dans une range selon la difficulte du mob monstre->level*/
   object_t * new_item = malloc(sizeof(object_t));
   new_item->type_object = type;
   new_item->state_object = etat;
   new_item->value_object = value(new_item->type_object, new_item->state_object);
   affectation_object(new_item);
   return new_item;
}


void create_inventory(){

   Inventaire= malloc(sizeof (inventory_t));

   Inventaire->nb_objects =0;
   int i;
   for( i = 0; i<30; i++){
      Inventaire->object[i] = NULL;
   }
}
void delete_object(object_t **item){
    supprimer_string(&(*item)->name_object);
    free(*item);
    *item = NULL;
}

err_t delete_inventory(){
  int i;
  if(Inventaire != NULL){
    for( i = 0; i<Inventaire->nb_objects; i++){
      delete_object(&Inventaire->object[i]);
    }
    free(Inventaire);
    return OK_state;
  }
  return KO_state;

}
/*ajout d un objet dans l inventaire*/
err_t fill_up_inventory(object_t* object) {

   if(Inventaire->nb_objects >= 30){ /*si c est plein, on renvoie 0  car on peut pas faire un overbook*/
          return KO_state;
   }
   Inventaire->object[Inventaire->nb_objects] = object;
   Inventaire->nb_objects++;
   return OK_state;
}


/*faire une fonction qui lise un fichier avec les descriptions des objets*/

static void affichage_type(object_t* objet, string* type_affich){

    switch (objet->type_object){
      case weapon: creer_string(type_affich,"%% de dégats"); break;
      case armor: creer_string(type_affich,"%% de défense"); break;
      case potion:{
                    if(objet->state_object >= 0 && objet->state_object <= 5 ){
                      creer_string(type_affich, "%% de l'effet indiqué");
                    }else
                      creer_string(type_affich, "%%");
        }; break;
      case tente: creer_string(type_affich,"Passer une nuit au calme et reprendre ses esprits..."); break;

    }
}

void afficher_inventaire(){

	int i;
   if (Inventaire->nb_objects >0){
    string affiche_le_type;
   	printf("Votre inventaire contient :\n");
   	for(i = 0; i< Inventaire->nb_objects ;i++){
         affichage_type(Inventaire->object[i],&affiche_le_type);
         printf("\titem %i : %s (%d %s)\n",i+1,Inventaire->object[i]->name_object, Inventaire->object[i]->value_object,affiche_le_type);
         supprimer_string(&affiche_le_type);
   	}
   }else
      printf("L' inventaire est vide\n");

}

void deleteFrom_inventaire(int indice){
  int i;

  delete_object(&Inventaire->object[indice-1]);

  for( i = (indice-1); i < Inventaire->nb_objects-1; i++){
      Inventaire->object[i]=Inventaire->object[i+1];
  }
  Inventaire->nb_objects--;

}
int est_mana(object_t* obj){
  return obj->type_object == potion && (obj->state_object <= 1);
}
int est_cure(object_t* obj){
  return obj->type_object == potion && (obj->state_object <= 3);
}
int est_phoenix(object_t* obj){
  return obj->type_object == potion && (obj->state_object <= 5);
}
