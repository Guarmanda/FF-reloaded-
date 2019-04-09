#ifndef _INVENTAIRE_H_
#define _INVENTAIRE_H_

#include <commun.h>

enum etatPerso{Stunt=0,Bleed,Slow,Silence,Poison,Blind,Speed,Sleep};
enum type_obj { armor=0, weapon, potion };
/*evite_combats sert à baisser les chances de tomber sur des monstres lorsqu le joueur se balade sur la carte*/
enum accessories_e{est_monstre,evite_combats, green_amulet=10,ruby_ring=20,crystal_ring=30}; /*est_monstre indique c est un monstre => il n a pas d accessoire*/
enum adv_armure {contre_fire=0, contre_thunder, contre_terre,contre_ice,resistance=20,resistance2=40};

/*structure objet qui possède trois champs, le type_object va de 0 à */
typedef struct object_s{
  char* name_object;
  enum type_obj type_object; /* 0= armure, 1=weapon, 2= les potions*/
  int state_object; /* exemple : armure de cuir, potion de mana [0- ] */
  int value_object; /*affectation d une valeur diff selon le type de l objet pour
  ex: potion et son pourcentage
  */
}object_t;
/*static pour eviter que les .o repetent les variables du .h si celui ci est inclu dans ++ fichiers différents   */



typedef struct inventory_s{
    int nb_objects;
    object_t * object[30];
}inventory_t;

inventory_t* Inventaire;
/*creation des objets*/
object_t* create_loot(int);
void delete_object(object_t **);
void affectation_object(object_t* );
/*definition des objets*/

/*manipulation des objets et insertion dans l inventaire*/
int value(int type, int state);
void create_inventory(void);
void afficher_inventaire(void);
err_t delete_inventory(void);
int fill_up_inventory(object_t* object);
/*variables utiles lors du combat pour modifier l'état des joueurs*/
int est_mana(object_t*);
int est_cure(object_t*);
int est_phoenix(object_t*);

#endif
