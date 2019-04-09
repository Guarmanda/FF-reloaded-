#include <stdio.h>
#include <stdlib.h>
#include <commun_perso.h>


int main(){
    init_tab_sort();
    affich_tab_sort();
    character_t* perso = creation_char();
    printf("les stats du perso\n" );
    affich_stats(perso);
    printf("entrez les coordonnees souhaitées pour x: ");
    scanf("%d", &position_x);
    printf("entrez les coordonnees souhaitées pour y: ");
    scanf("%d", &position_y);

    character_t* monstre2= monster_creation();
    printf("sorts du monstre\n" );
    afficher_sorts(monstre2);
    delete_player(&monstre2);
    delete_player(&perso);
    suppr_tab_sort();

    return 0;
}
