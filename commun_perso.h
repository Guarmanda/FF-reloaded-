#ifndef _PERSO_H_
#define _PERSO_H_

#include <inventaire.h>
#include <map_menace.h>

enum type{offensif=0, defensif, modifie_etat};

typedef struct spell_s{
   char* nom_sort;
   enum type type_sort;  /*0 = offensif/ 1 = defensif/ 2 = state modifier*/
   int valeur_sort;
}spell_t;

spell_t tab_sort[TAILLE_TAB_SORT]; /*tableau global à usage commun entre les persos*/

typedef struct liste_sort_s liste_sort_t;

struct liste_sort_s{
   liste_sort_t* debut_liste;
   spell_t* sort;
   liste_sort_t* sort_suivant;
};

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

character_t* PLAYER;

void init_tab_sort(void);
void affich_tab_sort(void);
int choisir_sort_joueur(character_t*);
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
void apply_state_modifier(character_t **, int , int );
/*--*/
void attribution_sort(int,character_t*);

/*sauvegarde*/
character_t* charger_partie(char *);
void sauvegarde_partie(character_t *,char *);

#endif
