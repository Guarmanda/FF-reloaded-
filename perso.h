
enum accessories_e{green_amulet=0,ruby_ring,crystal_ring};

typedef struct object_s{
  int type_object; /* 0= armure, 1=weapon, 2= potion*/
  int state_object; /* exemple : armure de cuir, potion de mana [0- ] */
  int value_object; /*affectation d une valeur diff selon le type de l objet pour
  ex: potion et son pourcentage
  */
}object_t;


typedef struct character_s{
  char name[15];
  int xp;
  int level;
  int health;
  int mana;
  int state[7]; /*voir possibilité de pouvoir etre sous diff states avec un tableau: blind,stunt,slow,poison,berserk,silence,bleeding*/
  int stat_strength;
  int stat_intel;
  int stat_stamina;
  enum accessories_e accessory;
  char class_char[15];
  object_t char_armor;
  object_t char_weapon;
}character_t;



typedef struct potion_s {
  int pot_mana; /*potion pour augmenter de 30% la mana*/
  int pot_max_mana; /*potion pour augmenter de 80% la mana*/
  int pot_health; /*potion pour augmenter de 30% la health*/
  int pot_max_health; /*potion pour augmenter de 80% la health*/
  int pot_phoenix; /*potion pour ressuciter un perso avec 30% de vie*/
  int pot_phoenix_health;  /*potion pour ressuciter un perso avec 80% de vie*/
  int anti_poison;
  int anti_silence;   /*enleve l etat silence*/
  int anti_blind;   /*anti aveuglement*/
  int anti_stunt; /*anti etourdissement*/
  int anti_bleeding; /*anti saignement*/
  int pot_speed; /*droit de faire deux actions à son tour*/
  int pot_lucidity; /*enleve le beserk*/
} potion_t ;

typedef struct inventory_s{
    int nb_objects;
    object_t * object[30];
}inventory_t;

inventory_t create_or_delete_inventory();
character_t* creation_char();
int fill_up_inventory(inventory_t array_inventory,object_t* object);
void delete_player(character_t* player);
void levelling(character_t* player, character_t monster);
char* display_object(object_t object);
void affich(character_t* perso);
object_t* create_object(character_t monster);
void delete_object(object_t **item);
int loot_type(character_t monster);
int loot_state(int type, character_t monster);
int loot_value(int type, int state);
