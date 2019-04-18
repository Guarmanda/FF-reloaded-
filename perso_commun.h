#ifndef _PERSO_H_
#define _PERSO_H_

#include <inventaire.h>
#include <map_menace.h>
#include <commun.h>
int EVASION; /*taux de chance de pouvoir prendre fuite, il peut changer selon l endroit de la carte (par exemple, contre un boss, il sera de 0)*/

/*----les différents types de sorts-----*/
enum type{offensif=0, defensif, modifie_etat};
/*------la structure d'un sort------*/
typedef struct spell_s{
   char* nom_sort;
   enum type type_sort;       /*0 = offensif/ 1 = defensif/ 2 = state modifier*/
   int valeur_sort;
}spell_t;

/*------la structure d'une liste de sort, usage commun de tous les personnages------*/
typedef struct liste_sort_s liste_sort_t;
struct liste_sort_s{
   liste_sort_t* debut_liste;
   int indice_tab_sorts;
   liste_sort_t* sort_suivant;
};

/*------la structure d'une liste de sort, usage commun de tous les personnages------*/

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
character_t* Personnage;
spell_t tab_sort[TAILLE_TAB_SORT]; /*tableau global à usage commun entre les persos*/

/*-----------------manipulation des sorts-------------------------------------*/

void init_tab_sort(void);
void affich_tab_sort(void);
int joueur_sort(character_t* );
err_t suppr_tab_sort();
/*-------------- manipulation des stats/attributs des personnages ----------------------*/
character_t* creation_char(void);
void delete_player(character_t** player);
void supprimer_sorts(character_t** perso);
void affich_stats(character_t*); /*fonction d'affichage des details du joueur*/
/*--*/
character_t* monster_creation();

/*--*/
int taking_potion(void);
void apply_state_modifier(character_t **, int );
/*--*/
void attribution_sort(int,character_t*);

/*sauvegarde*/
character_t* charger_partie(char *);
void sauvegarde_partie(character_t *,char *);

#endif
