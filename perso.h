#ifndef _PERSO_H_
#define _PERSO_H_

#include <inventaire.h>

typedef struct character_s{
  char name[20];
  int xp;
  int level;
  int health;
  int mana;
  int max_health;       /*vie maximum que peut avoir le joueur selon son niveau*/
  int max_mana;
  int spell[7];            /* */
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
/*void levelling(character_t* player, character_t monster);*/
void affich(character_t*); /*fonction d'affichage des details du joueur*/

/*--- combat monstre
character_t* monster_creation();
int attack(character_t **target,character_t attacker);
void combat(character_t *player);*/


#endif
