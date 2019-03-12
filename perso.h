#ifndef _PERSO_H_
#define _PERSO_H_

#include <inventaire.h>

/**
 *

 \brief Structure personnage, contient le sexe, les statistiques, l'arme et armure équipé.

 */

typedef struct character_s{
  char name[15]; /*!< Tableau de 15 caractère pour stocker le nom du joueur */
  int xp; /*!< Représente la quantité d'experience gagné */
  int level; /*!< Niveau du joueur */
  int health; /*!< Vie du joueur */
  int mana; /*!< Mana du joueur */
  int max_health; /*!< Vie maximum du joueur */
  int max_mana; /*!< Mana max du joueur */
  int spell[7]; /*!< Tableau de 7 entiers represente les sorts, si 1 le sort est connu du joueur, sinon 0 */
  int state[7]; /*!< Tableau de 7 entiers represente les etats du joueur (etourdit,empoisonne etc...), l'etat est a 1 si le joueur le subit. */
  int stat_strength; /*!< Force du joueur */
  int stat_intel; /*!< Intelligence du joueur */
  int stat_stamina; /*!< Endurance du joueur */
  enum accessories_e accessory; /*!< Represente l'accesoire du joueur */
  char gender[6]; /*!< Tableau de caracteres, donne le genre homme ou femme */
  char class_char[15]; /*!< Tableau de caracteres, represente la classe */
  object_t char_armor;  /*!< Piece d'armure equipee par le joueur */
  object_t char_weapon;  /*!< Arme equipee par le joueur */
}character_t;

character_t* creation_char();
void delete_player(character_t* player);
void levelling(character_t* player, character_t monster);
void affich(character_t* perso); /*fonction d'affichage des details du joueur*/

/*--- combat monstre
character_t* monster_creation();
int attack(character_t **target,character_t attacker);
void combat(character_t *player);*/


#endif
