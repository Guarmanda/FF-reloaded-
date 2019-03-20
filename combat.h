#ifndef _COMBAT_H_
#define _COMBAT_H_

#include <perso.h>

#define map_size_x 1000
#define map_size_y 1000

enum spell_enum{ offensif, defensif, modifie_etat};

typedef struct spell_s{
  char spell_name[30];
  enum spell_enum spell_type; /* 0 = offensif/ 1 = defensif/ 2 = state modifier*/
  int spell_value;
}spell_t;

/*-------------------------------------------------------------*/
void casting_spell(character_t* wizard,character_t **target, spell_t spell);  /*à implémenter */
/*Attaque sur un des monstres*/
void attaque_joueur(character_t* player,character_t* tab_monstre[], int nb_monstre);
void attack(character_t* attacker,character_t **target); /*fonction auxiliaire pour l attaque*/

/*Modifier etat du joueur */
void taking_potion(character_t **player,inventory_t* inventaire);
void apply_state_modifier(character_t **target, int value, int off_or_on);

/*Renvoie vrai si le joueur/monstre est mort*/
int is_dead(character_t *target);

/*Essaie d'eviter le combat*/
int running_away(character_t** player);
/*sauvegarde de la fonction originale au cas où :
int running_away(character_t player,character_t monster);
*/

/*----Creation et manipulation du/des monstre(s)----*/
char* allocating_monster_name(int level);
void update_tab_monster(character_t *monster_array[],int index, int nb_monstre);

/*Ajout de la fonction qui augmentera le niveau du joueur*/
int xp_points(character_t* player, character_t monster);
int levelling(character_t* player);

/*Fonction qui déclanche  le combat*/
int combat_on(character_t **player, inventory_t *inventory, int* xp_temp);

/*Affichage du menu combat*/
int affich_choix();



#endif
