#ifndef _INVENTAIRE_H_
#define _INVENTAIRE_H_

#include <commun.h>

/*#include <>*/
typedef struct object_s{
  int type_object; /* 0= armure, 1=weapon, 2= potion*/
  int state_object; /* exemple : armure de cuir, potion de mana [0- ] */
  int value_object; /*affectation d une valeur diff selon le type de l objet pour
  ex: potion et son pourcentage
  */
}object_t;
/*static pour eviter que les .o repetent les variables du .h si celui ci est inclu dans ++ fichiers différents   */

enum accessories_e {
      green_amulet=0,ruby_ring,crystal_ring
};

typedef struct inventory_s{
    int nb_objects;
    object_t * object[30];    /*voir si il faut delete*/
}inventory_t;

inventory_t* inventaire;
/*creation des objets*/
object_t* create_object(int level);
void delete_object(object_t **item);
/*definition des objets*/
int loot_type(int level);
int loot_state(int type,int level);
int loot_value(int type, int state);
/*manipulation des objets et insertion dans l inventaire*/
inventory_t* create_or_delete_inventory();
int fill_up_inventory(inventory_t* inventory,object_t* object);
/*affichage */
char* display_object(object_t object);
#endif
