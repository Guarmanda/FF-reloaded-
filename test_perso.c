/**
 * \file
 * \brief Programme de tests sur les personnages du jeu
 * \author Karman Nathalie, Papot Alexandre
 * \version 0.1
 * \date 6 avril 2019
 *
 * Jeux de tests pour les fonctions qui manipulent l'inventaire \a Inventaire du joueur
 *    et les objets et leur création
*/

#include <stdio.h>
#include <stdlib.h>
#include <perso_commun.h>


int main(){
    init_tab_sort();
    affich_tab_sort();
    Personnage=creation_char();
    printf("entrez les coordonnees souhaitées pour x: ");
    scanf("%d", &position_x);
    printf("entrez les coordonnees souhaitées pour y: ");
    scanf("%d", &position_y);

    character_t* monstre2= monster_creation();


    affich_stats(Personnage);
    printf("sorts du Personnage\n" );
    afficher_sorts(Personnage);
    delete_player(&monstre2);

    delete_player(&Personnage);
    suppr_tab_sort();

    return EXIT_SUCCESS;
}
