#ifndef _INVENTAIRE_H_
#define _INVENTAIRE_H_

#include <commun.h>

/**
 * \def MAX_OBJ
 * \brief maximum d'objets que peut contenir l'inventaire
 */
#define MAX_OBJ 30  /*maximum d'objets que peut contenir l'inventaire*/

/**
 * \enum etatPerso
 * \brief les différents etats physiques et/ou psycholiques qui influent en combat
 *
 */
enum etatPerso{
  Stunt=0,   /*!< étourdi jusqu à application d'antidote */
  Bleed,   /*!< saigne jusqu à application d'antidote */
  Slow,  /*!< lenteur pendant 2-3 tours */
  Silence,   /*!< empêche l'utilisation de magie */
  Poison,  /*!< perd 5% de vie à chaque tour */
  Blind,  /*!< est aveugle pendant 2-3 tours */
  Sleep  /*!< dort pendant 2-3tours */
};
/**
 * \enum type_obj
 * \brief les différents types d'objets en catégorie
 *
 * le type objet tente est spécifié à part puisque il n'est utile que dans une seule situation
 * les valeurs d'enumération sont des indices pour le dictionnaire respectif à chaque type
 */
enum type_obj {
  armor=0, /*!< type armure = 0 */
  weapon,  /*!< type arme = 1 */
  potion ,   /*!< type potion = 2 */
  tente=30   /*!< type tente = 30, valeur qui définit le prix de l'objet tente */
};
/**
 * \enum accessories_e
 * \brief accessoires qui peuvent être acquis lors d'une récompense et équipés
 */
enum accessories_e{
  est_monstre=0,  /*!< aide à calculer le dégats d'attaque et aussi à supprimer les adversaires */
  evite_combats=20,  /*!<baisse le taux de chance de tomber en combat */
  green_amulet=10,    /*!< à équiper, donne 10% de defense */
  ruby_ring=20, /*!< à équiper, donne 20% de defense */
  crystal_ring=30 /*!< à équiper, donne 30% de defense */
};

/**
 * \struct object_t
 * \brief définit un objet à l'aide de son nom, son type, son état ou \a spécificité et sa valeur
 *
 */

typedef struct object_s{
  char* name_object;
  enum type_obj type_object; /* 0= armure, 1=weapon, 2= les potions, 30 pour la tente*/
  int state_object;     /* exemple : armure de cuir, potion de mana [0- ] */
  int value_object;  /*affectation d une valeur diff selon le type de l objet par  ex: potion et son pourcentage
  */
}object_t;

/**
 * \struct inventory_t
 * \brief structure inventory_t
 *
 * Il contiendra au maximum MAX_OBJ d'objets et son compteur \a nb_objects
 * permet de parcourir les elements et et checker si il est plein ou vide
 */
typedef struct inventory_s{
    int nb_objects;
    object_t * object[MAX_OBJ];
}inventory_t;

/*--------------------------------------*/


/**
 * \var Inventaire
 * \brief declaration en global de l'inventaire
 */
inventory_t* Inventaire;

/*creation des objets*/
object_t* create_loot(int);
object_t* create_object(int, int);
void delete_object(object_t **);
void affectation_object(object_t* );
/*definition des objets*/

/*manipulation des objets et insertion dans l inventaire*/
int value(int type, int state);
void create_inventory(void);
int afficher_inventaire(void);
err_t deleteFrom_inventaire(int );
err_t delete_inventory(void);
int fill_up_inventory(object_t* object);
/*variables utiles lors du combat pour modifier l'état des joueurs*/
int est_mana(object_t*);
int est_cure(object_t*);
int est_phoenix(object_t*);

#endif
