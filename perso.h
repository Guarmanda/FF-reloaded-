
typedef enum {green_amulet,ruby_ring,crystal_ring};

typedef struct character_s{
  char name[15];
  int xp;
  int health;
  int mana;
  int state[7]; /*voir possibilité de pouvoir etre sous diff states avec un tableau: blind,stunt,slow,poison,berserk,silence,bleeding*/
  int stat_strength;
  int stat_intel;
  int stat_stamina;
  char class_char[15];
  enum accessoire;
  armor_t char_armor;
  weapon_t char_weapon;

}character_t;

typedef struct weapon_s {
  int dagger;
  int staff;
  int sword;
  int axe;
  int bow;
}weapon_t;

typedef struct armor_s {
  int armor_cloth;
  int armor_copper;
  int armor_silver;
  int armor_leather;
}armor_t;

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

typedef struct inventory{
    void *object[30];
}
