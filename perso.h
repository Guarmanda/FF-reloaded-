#ifndef _PERSO_H_
#define _PERSO_H_

#include <inventaire.h>

enum type{offensif=0, defensif, modifie_etat};

typedef struct spell_s{
   char* nom_sort;
   enum type type_sort;  /* 0 = offensif/ 1 = defensif/ 2 = state modifier*/
   int valeur_sort;
}spell_t;

typedef struct character_s{
  char name[20];
  int xp;
  int level;
  int health;
  int mana;
  int max_health;       /*vie maximum que peut avoir le joueur selon son niveau*/
  int max_mana;
  spell_t* spell;            /* tableau de spell*/
  int state[7];         /*voir possibilité de pouvoir etre sous diff states avec un tableau: blind,stunt,slow,poison,berserk,silence,bleeding*/
  int stat_strength;
  int stat_intel;
  int stat_stamina;
  enum accessories_e accessory;
  char class_char[15];
  object_t char_armor;  /*type = 0*/
  object_t char_weapon;  /*type = 1*/
}character_t;

character_t* creation_char();
char* allocating_monster_name(int);
character_t* monster_creation(int);
void delete_player(character_t**);
void affich(character_t*); /*fonction d'affichage des details du joueur*/
void attribution_sort(character_t* perso);
void init_tab_sort(spell_t** tab_sort);
/*--- combat monstre
character_t* monster_creation();
int attack(character_t **target, character_t attacker);
void combat(character_t *player);*/


#endif
