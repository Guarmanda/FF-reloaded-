#ifndef _QUETE_H_
#define _QUETE_H_

#include <combat.h>
#define MAX_QUETES 5
/**
 *
 \brief Structure des quêtes:

 */

typedef struct quete_s{
    int pnj_x;
    int pnj_y;
    char phrase_debut[400];
    char phrase_fin[400];
    char pnj_nom[30];
    int statut;
    int but_x;
    int but_y;
    int xp;

    char nom_img[30];
    char pnj_img[30];

}quete_t;

quete_t * quetes[MAX_QUETES]; /*!< Tableau de pointeurs de structures quêtes */

void charger_quetes(void);
int affich_quetes(void);

#endif
