#include <stdio.h>
#include <stdlib.h>
#include <commun_perso.h>


int main(){

    character_t* perso = creation_char();
    init_tab_sort();
    printf("entrez les coordonnees souhaitées pour x: ");
    scanf("%d", &position_x);
    printf("entrez les coordonnees souhaitées pour y: ");
    scanf("%d", &position_y);
    character_t* monstre= monster_creation();   /*meme niveau que le joueur*/
    character_t* monstre2= monster_creation();   /*meme niveau que le joueur*/
    printf("vous jouez contre :\n");
    affich_stats(monstre);
    affich_stats(monstre2);
    delete_player(&perso);
    delete_player(&monstre2);
    delete_player(&monstre);

    return 0;
}
