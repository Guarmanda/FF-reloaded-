#include <stdio.h>
#include <stdlib.h>

/**
 * \file sauvegarde.c
 * \brief Fonctions de chargement du jeu
 * \author Karman Nathalie; Papot Alexandre
 * \date 3 avril 2019
 */

/*changer param car perso est en global*/
#include <commun_perso.h>

character_t* charger_partie(char *nom_fichier_sauvegarde){

    int i;
    FILE * fichier = fopen(nom_fichier_sauvegarde, "r");
    character_t* perso=NULL;
    perso = malloc(sizeof(character_t));

    fscanf(fichier, "%[^;];", perso->name);
    fscanf(fichier, "%i;", &perso->xp);
    fscanf(fichier, "%i;", &perso->level);
    fscanf(fichier, "%i;", &perso->health);
    fscanf(fichier, "%i;", &perso->mana);
    fscanf(fichier, "%i;", &perso->max_health);
    fscanf(fichier, "%i;", &perso->max_mana);
   /* fscanf(fichier, "%i;", &perso->spell[0]);
    fscanf(fichier, "%i;", &perso->spell[1]);
    fscanf(fichier, "%i;", &perso->spell[2]);
    fscanf(fichier, "%i;", &perso->spell[3]);
    fscanf(fichier, "%i;", &perso->spell[4]);
    fscanf(fichier, "%i;", &perso->spell[5]);
    fscanf(fichier, "%i;", &perso->spell[6]);
*/  fscanf(fichier, "%i;", &perso->state[0]);
    fscanf(fichier, "%i;", &perso->state[1]);
    fscanf(fichier, "%i;", &perso->state[2]);
    fscanf(fichier, "%i;", &perso->state[3]);
    fscanf(fichier, "%i;", &perso->state[4]);
    fscanf(fichier, "%i;", &perso->state[5]);
    fscanf(fichier, "%i;", &perso->state[6]);
    fscanf(fichier, "%i;", &perso->stat_strength);
    fscanf(fichier, "%i;", &perso->stat_intelligence);
    fscanf(fichier, "%i;", &perso->stat_stamina);
    fscanf(fichier, "%i;", (int*)&perso->accessory);
    fscanf(fichier, "%[^;];", perso->class_char);
    fscanf(fichier, "%i;", (int*)&perso->char_armor.type_object);
    fscanf(fichier, "%i;", &perso->char_armor.state_object);
    fscanf(fichier, "%i;", &perso->char_armor.value_object);
    fscanf(fichier, "%i;", (int*)&perso->char_weapon.type_object);
    fscanf(fichier, "%i;", &perso->char_weapon.state_object);
    fscanf(fichier, "%i;", &perso->char_weapon.value_object);
    fscanf(fichier, "%[^;];", perso->gender);
    fscanf(fichier, "%i;", &position_x);
    fscanf(fichier, "%i;", &position_y);

    object_t *tmp;
    for(i = 0;i<Inventaire->nb_objects;i++){
       printf("%i\n", Inventaire->nb_objects);
       tmp = malloc(sizeof(object_t));
       fscanf(fichier, "%i;", (int*)&tmp->type_object);
       fscanf(fichier, "%i;", &tmp->state_object);
       fscanf(fichier, "%i;", &tmp->value_object);
       fill_up_inventory(Inventaire,tmp);
       free(tmp);
       tmp = NULL;
       Inventaire->nb_objects--;
    }

    fclose(fichier);
    return perso;
}

/**
 * \file sauvegarde.c
 * \brief Fonctions de sauvegarde de la partie
 * \author Karman Nathalie; Papot Alexandre
 * \date 3 avril 2019
 * Ecrit dans un fichier sauvegarde.txt les statistiques du joueur, les objets de l'inventaire et la position du joueur dans le jeu
 */

void sauvegarde_partie(character_t *perso,char *nom_fichier_sauvegarde){

    int i;
    FILE * fichier = fopen(nom_fichier_sauvegarde, "w");

    fprintf(fichier, "%s;",perso->name);
    fprintf(fichier, "%i;",perso->xp);
    fprintf(fichier, "%i;",perso->level);
    fprintf(fichier, "%i;",perso->health);
    fprintf(fichier, "%i;",perso->mana);
    fprintf(fichier, "%i;",perso->max_health);
    fprintf(fichier, "%i;",perso->max_mana);
   /* for(i= 0; i<7 ;i++){
      fprintf(fichier, "%i;",perso->state[i]);
      fprintf(fichier, "%i;",perso->spell[i]);
   }*/
    fprintf(fichier, "%i;",perso->stat_intelligence);
    fprintf(fichier, "%i;",perso->stat_stamina);
    fprintf(fichier, "%i;",perso->stat_strength);
    fprintf(fichier, "%i;",perso->accessory);
    fprintf(fichier, "%s;",perso->class_char);
    fprintf(fichier, "%i;",perso->char_armor.type_object);
    fprintf(fichier, "%i;",perso->char_armor.state_object);
    fprintf(fichier, "%i;",perso->char_armor.value_object);
    fprintf(fichier, "%i;",perso->char_weapon.type_object);
    fprintf(fichier, "%i;",perso->char_weapon.state_object);
    fprintf(fichier, "%i;",perso->char_weapon.value_object);
    fprintf(fichier,"%s;", perso->gender);
    fprintf(fichier,"%i;", position_x);
    fprintf(fichier,"%i;", position_y);

    for (i= 0;i<Inventaire->nb_objects;i++){
       fprintf(fichier, "%i;", Inventaire->object[i]->type_object);
       fprintf(fichier, "%i;", Inventaire->object[i]->state_object);
       fprintf(fichier, "%i;", Inventaire->object[i]->value_object);
    }
    fclose(fichier);
}
