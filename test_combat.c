/**
 * \file
 * \brief Programme de tests sur le combat
 * \author Karman Nathalie, Papot Alexandre
 * \version 0.1
 * \date 6 avril 2019
 *
 * Jeux de tests pour la simulation d'un combat
 *
*/
#include <combat.h>
/**
 * \fn int main (void)
 * \brief Entrée du programme.
 *
 * \return EXIT_SUCCESS - Arrêt normal du programme.
 */
int main(){
    /*fichier de tests pour la simulation d'un combat dans la map*/

    init_tab_sort();
    init_menaces();
    create_inventory();
    srand(time(NULL));

    /*la fonction de creation du personnage pourra être appliqué à 4 personnages, pour
    que le jeu soit fidèle aux règles de rpg et que les classes des personnages s'entraident
    */
    Personnage=creation_char();
    /*au cas où l'on choisit un wizard, et non pas un warrior, il affichera les sorts attribués*/
    afficher_sorts(Personnage);
    /*création d'objets pour que le joueur puisse s'en servir en combat*/
    object_t* obj2= create_object(potion,3);
    fill_up_inventory(obj2);
    object_t* obj1= create_object(potion,2);
    fill_up_inventory(obj1);
   /*tests de positions de la map*/
    do{
       printf("entrez les coordonnees souhaitées pour x [0-999]: ");
       scanf("%d", &position_x);
       printf("entrez les coordonnees souhaitées pour y [0-999]: ");
       scanf("%d", &position_y);
       viderBuffer();

    }while(position_x < 0 || position_x > 999 || position_y < 0 || position_y > 999 );

    int menaceTest = map_threat[position_x][position_y];
    printf("il y a une menace de %d%%\n",menaceTest );

    fight_rand();

    suppr_tab_sort();
    delete_inventory();

    delete_player(&Personnage);

    return EXIT_SUCCESS;

}
