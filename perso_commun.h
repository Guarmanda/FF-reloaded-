#ifndef _PERSO_H_
#define _PERSO_H_

#include <inventaire.h>
#include <map_menace.h>
#include <commun.h>

/**
 * \var EVASION
 * \brief variable qui représente le taux de chance de s'enfuir
 * \details on met cette variable ici puisque elle peut être affectée par la création d'un monstre ou encore, dans \a combat.c
 */
int EVASION; /*taux de chance de pouvoir prendre fuite, peut changer selon l endroit de la carte (par exemple, contre un boss, il sera de 0)*/
/**
 * \def TAILLE_TAB_SORT
 * \brief taille du tableau contenant les sorts des personnages
 */
#define TAILLE_TAB_SORT 23
/**
 * \enum type
 * \brief les différents types de sorts
 *
 */
enum type{offensif=0,
   defensif,
   modifie_etat
};
/**
 * \struct spell_t
 * \brief structure d'un sort, comprend 3 champs
 *
 */
typedef struct spell_s{
   char* nom_sort;
   enum type type_sort;       /*0 = offensif/ 1 = defensif/ 2 = state modifier*/
   int valeur_sort;
}spell_t;

/**
 * \struct liste_sort_t
 * \brief structure d'une liste chaînée de sorts
 * contient dans le champ \a indice_tab_sorts : l'indice du tableau global de sorts
 */
/*------la structure d'une liste de sort, usage commun de tous les personnages------*/
typedef struct liste_sort_s liste_sort_t;
struct liste_sort_s{
   liste_sort_t* debut_liste;
   int indice_tab_sorts;
   liste_sort_t* sort_suivant;
};

/**
 * \struct character_t
 * \brief structure d'un personnage (joueurs et adversaires)
 *
 */
typedef struct character_s{
  char* name ;
  int xp;
  int level;
  int health;
  int mana;
  int max_health;       /*vie maximum que peut avoir le joueur selon son niveau*/
  int max_mana;
  liste_sort_t* liste_spell;      /*   structure chainée qui pointera sur le tableau global de sort*/
  int state[MAX_ETATS];
  int stat_strength;
  int stat_intelligence;
  int stat_stamina;
  char* class_char;
  object_t* char_armor;
  object_t* char_weapon;
  enum accessories_e accessory;
  char* gender;
}character_t;

/*-----------------variables globales-------------------------------------*/
/**
 * \var Personnage
 * \brief variable globale qui est le personnage du joueur
 */
character_t* Personnage;
/**
 * \var tab_sort[]
 * \brief tableau de sorts \a spell_t en global, il est borné par la constante TAILLE_TAB_SORT
 */
spell_t tab_sort[TAILLE_TAB_SORT]; /*tableau global à usage commun entre les persos*/

/*-----------------manipulation des sorts-------------------------------------*/

void init_tab_sort(void);
void affich_tab_sort(void);
int joueur_sort(character_t* );
err_t suppr_tab_sort();

/*-------------- manipulation des stats/attributs des personnages ----------------------*/

/*- reservé au joueur -*/
character_t* creation_char(void);
void apply_auto_spell(character_t*);
int taking_potion(void);

/*- reservé que aux adversaires et nécessaire pour module combat.c -*/
character_t* monster_creation(void);

/*-usage commun-*/
void debut_liste(character_t** );
void delete_player(character_t** );
void afficher_sorts(character_t*);
void supprimer_sorts(character_t** );
void affich_stats(character_t*); /*fonction d'affichage des details des persos*/
void apply_state_modifier(character_t **, int );
void attribution_sort(int,character_t*);
/*--*/

/*sauvegarde*/
character_t* charger_partie();
void sauvegarde_partie();

#endif
