#ifndef _COMBAT_H_
#define _COMBAT_H_

#include <commun.h>
#include <perso_commun.h>

/**
 * \def MAX_NB_MONSTRE
 * \brief macro qui définit le max de monstre à gérer en combat
 */
#define MAX_NB_MONSTRE 4

/**
 * \def FUITE
 * \brief macro utile pour changer la variable globale \a etat_jeu
 */
/*définit juste l'état du combat*/
#define FUITE -10

int recompense_debut_j; /*variable qui fait partie de la version béta, pour qu'on puisse se balader sur la map sans activer de "quete" déjà faite*/
/*---------------------------- fonctions utilisateur---------------------*/
int tour_joueur(int ,character_t* [], int );
/*Essaie d'eviter le combat*/
int running_away(void);
/*Ajout de la fonction qui augmentera le niveau du joueur*/
int xp_points(character_t );
int levelling(character_t* );
/*Fonction qui déclanche  le combat*/
int combat_on(void);
/*Affichage du menu combat*/
int affich_choix(void);
/*fonction qui gère l'aléatoire sur la carte*/
void fight_rand(void);

/*--------------------fonctions communes aux personnages------------*/
int is_dead(character_t *);
void attack(character_t*,character_t **); /*fonction pour l attaque*/

/*----Creation et manipulation du/des monstre(s)----*/
char* allocating_monster_name(int );
void update_tab_monster(character_t *[],int , int );



#endif
