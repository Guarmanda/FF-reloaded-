#include <perso_commun.h>
int afficher_menu(char menu[4][30]);
void afficher_Map(float, float);
void afficher_quete(float x, float y, char * phrase, char*image, char etat);
void afficher_creation(char*name, char*class_char, char*gender);
void afficher_selecteur(int x, int y);
void showInventory();
int detecter_mouvement(float*x, float*y);
void detecter_touches(int*);
void gestion_editeur(float*, float*, int*, int*);
int affich_choix(character_t * monster[], int nb_monster);
void afficher_combat(character_t* monster[], int nb_monstres);
int choisir_ennemi(character_t * monster[], int nb_monster);
void afficher_degat(character_t * attaquant, character_t * cible, int degats, character_t* monster[], int nb_monstres);
