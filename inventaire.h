#ifndef _INVENTAIRE_H_
#define _INVENTAIRE_H_

#include "commun.h"
/*#include <>*/

/**
 *

 \brief Structure objet.

 */

typedef struct object_s{
  int type_object; /*!< 0 = armure, 1 = arme, 2 = potion */
  int state_object; /*!< Numero de l'objet dans le type */
  int value_object; /*!< Valeur de l'objet (armure, pourcentage de vie rendu etc...) */
}object_t;
/*static pour eviter que les .o repetent les variables du .h si celui ci est inclu dans ++ fichiers différents   */


/**
 *
 \brief Accesoire du joueur.
 */

enum accessories_e {
      green_amulet=0, /*!< 0 */
      ruby_ring=1, /*!< 1*/
      crystal_ring=2 /*!< 2 */
};

/**
 *
 \brief Inventaire du joueur.
 */

typedef struct inventory_s{
    int nb_objects; /*!< Nombre d'emplacements maximal dans l'inventaire. */
    object_t * object[30]; /*!< Tableau de 30 pointeurs vers objet. */
}inventory_t;

/*creation des objets*/
object_t* create_object(int level);
void delete_object(object_t **item);
/*definition des objets*/
int loot_type(int level);
int loot_state(int type,int level);
int loot_value(int type, int state);
/*manipulation des objets et insertion dans l inventaire*/
inventory_t create_or_delete_inventory();
int fill_up_inventory(inventory_t array_inventory,object_t* object);
/*affichage */
char* display_object(object_t object);
#endif
