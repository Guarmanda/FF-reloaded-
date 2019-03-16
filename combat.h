#ifndef _COMBAT_H_
#define _COMBAT_H_

#include <perso.h>

#define map_size_x 1000
#define map_size_y 1000

typedef struct spell_s{
  char spell_name[30];
  int spell_type; /* 0 = offensif/ 1 = defensif/ 2 = state modifier*/
  int spell_value;
}spell_t;

/*-------------------------------------------------------------*/
void casting_spell(character_t* wizard,character_t **target, spell_t spell);
void fight_rand(int fight_chance,character_t **player, inventory_t inventaire); /*necessaire*/
void attack(character_t* attacker,character_t **target);
void apply_state_modifier(character_t **target, int value, int off_or_on);
int taking_potion(character_t **player,inventory_t* inventaire);
int is_dead(character_t *target);

int running_away(character_t player,character_t monster);
void player_action(character_t **player,character_t ** monster, inventory_t *inventory);

int begin_fight(character_t **player, inventory_t* inventory);
character_t* monster_creation(int level);
char* allocating_monster_name(int level);
void update_tab_monster(character_t *monster_array[],int index, int nb_monstre);

void levelling(character_t* player, character_t monster); /*ajout de la fonction qui augmentera le niveau du joueur*/


#endif
