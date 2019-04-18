/**
 * \file sauvegarde.c
 * \brief Fonctions de chargement du jeu
 * \author Karman Nathalie; Papot Alexandre
 * \date 3 avril 2019
 */

#include <perso_commun.h>

character_t* charger_partie(){

    FILE * fichier;
    char nom_fichier_sauvegarde[50];

    do{
        printf("Entrer le nom du fichier de sauvegarde : ");
        scanf("%s", nom_fichier_sauvegarde);
        fichier = fopen(nom_fichier_sauvegarde, "r");
    }while(fichier == NULL);

    int i;
    Personnage = malloc(sizeof(character_t));
    Personnage->name = malloc(sizeof(char) * TAILLE_STR);
    Personnage->liste_spell = malloc(sizeof(liste_sort_t));

    fscanf(fichier, "%[^;];", Personnage->name);
    fscanf(fichier, "%i;", &Personnage->xp);
    fscanf(fichier, "%i;", &Personnage->level);
    fscanf(fichier, "%i;", &Personnage->health);
    fscanf(fichier, "%i;", &Personnage->mana);
    fscanf(fichier, "%i;", &Personnage->max_health);
    fscanf(fichier, "%i;", &Personnage->max_mana);
   /* fscanf(fichier, "%i;", &Personnage->spell[0]);
    fscanf(fichier, "%i;", &Personnage->spell[1]);
    fscanf(fichier, "%i;", &Personnage->spell[2]);
    fscanf(fichier, "%i;", &Personnage->spell[3]);
    fscanf(fichier, "%i;", &Personnage->spell[4]);
    fscanf(fichier, "%i;", &Personnage->spell[5]);
    fscanf(fichier, "%i;", &Personnage->spell[6]);
*/  fscanf(fichier, "%i;", &Personnage->state[0]);
    fscanf(fichier, "%i;", &Personnage->state[1]);
    fscanf(fichier, "%i;", &Personnage->state[2]);
    fscanf(fichier, "%i;", &Personnage->state[3]);
    fscanf(fichier, "%i;", &Personnage->state[4]);
    fscanf(fichier, "%i;", &Personnage->state[5]);
    fscanf(fichier, "%i;", &Personnage->state[6]);
    fscanf(fichier, "%i;", &Personnage->state[7]);
    fscanf(fichier, "%i;", &Personnage->stat_strength);
    fscanf(fichier, "%i;", &Personnage->stat_intelligence);
    fscanf(fichier, "%i;", &Personnage->stat_stamina);
    fscanf(fichier, "%i;", (int*)&Personnage->accessory);
    fscanf(fichier, "%[^;];", Personnage->class_char);
    Personnage->char_armor=malloc(sizeof(object_t));
    fscanf(fichier, "%i;", (int*)&Personnage->char_armor->type_object);
    fscanf(fichier, "%i;", &Personnage->char_armor->state_object);
    fscanf(fichier, "%i;", &Personnage->char_armor->value_object);
    affectation_object(Personnage->char_armor);
    Personnage->char_weapon=malloc(sizeof(object_t));
    fscanf(fichier, "%i;", (int*)&Personnage->char_weapon->type_object);
    fscanf(fichier, "%i;", &Personnage->char_weapon->state_object);
    fscanf(fichier, "%i;", &Personnage->char_weapon->value_object);
    affectation_object(Personnage->char_weapon);
    fscanf(fichier, "%[^;];", Personnage->gender);

    int x;
    int y;

    fscanf(fichier, "%i;", &x);
    fscanf(fichier, "%i;", &y);

    position_x = x;
    position_y = y;


    object_t *tmp;
    for(i = 0;i<Inventaire->nb_objects;i++){
       printf("%i\n", Inventaire->nb_objects);
       tmp = malloc(sizeof(object_t));
       fscanf(fichier, "%i;", (int*)&tmp->type_object);
       fscanf(fichier, "%i;", &tmp->state_object);
       fscanf(fichier, "%i;", &tmp->value_object);
       fill_up_inventory(tmp);
       free(tmp);
       tmp = NULL;
       Inventaire->nb_objects--;
    }

    fclose(fichier);
    return Personnage;
}

/**
 * \file sauvegarde.c
 * \brief Fonctions de sauvegarde de la partie
 * \author Karman Nathalie; Papot Alexandre
 * \date 3 avril 2019
 * Ecrit dans un fichier sauvegarde.txt les statistiques du joueur, les objets de l'inventaire et la position du joueur dans le jeu
 */

void sauvegarde_partie(){

    char nom_fichier_sauvegarde[50];
    printf("Entrer un nom de fichier de sauvegarde : \n");
    scanf("%s", nom_fichier_sauvegarde);

    int i;
    FILE * fichier = fopen(nom_fichier_sauvegarde, "w");

    fprintf(fichier, "%s;",Personnage->name);
    fprintf(fichier, "%i;",Personnage->xp);
    fprintf(fichier, "%i;",Personnage->level);
    fprintf(fichier, "%i;",Personnage->health);
    fprintf(fichier, "%i;",Personnage->mana);
    fprintf(fichier, "%i;",Personnage->max_health);
    fprintf(fichier, "%i;",Personnage->max_mana);
    for(i= 0; i<MAX_ETATS ;i++){
      fprintf(fichier, "%i;",Personnage->state[i]);
    }
    fprintf(fichier, "%i;",Personnage->stat_intelligence);
    fprintf(fichier, "%i;",Personnage->stat_stamina);
    fprintf(fichier, "%i;",Personnage->stat_strength);
    fprintf(fichier, "%i;",Personnage->accessory);
    fprintf(fichier, "%s;",Personnage->class_char);
    fprintf(fichier, "%i;",Personnage->char_armor->type_object);
    fprintf(fichier, "%i;",Personnage->char_armor->state_object);
    fprintf(fichier, "%i;",Personnage->char_armor->value_object);
    fprintf(fichier, "%i;",Personnage->char_weapon->type_object);
    fprintf(fichier, "%i;",Personnage->char_weapon->state_object);
    fprintf(fichier, "%i;",Personnage->char_weapon->value_object);
    fprintf(fichier,"%s;", Personnage->gender);
    fprintf(fichier,"%i;", position_x);
    fprintf(fichier,"%i;", position_y);

    for (i= 0;i<Inventaire->nb_objects;i++){
       fprintf(fichier, "%i;", Inventaire->object[i]->type_object);
       fprintf(fichier, "%i;", Inventaire->object[i]->state_object);
       fprintf(fichier, "%i;", Inventaire->object[i]->value_object);
    }
    fclose(fichier);
}
