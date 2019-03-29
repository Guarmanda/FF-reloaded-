#include <stdio.h>
#include <stdlib.h>
#include <perso.h>


int main(){
   spell_t* tab_sort;
    character_t* perso = creation_char();

    character_t* monstre= monster_creation(2);   /*meme niveau que le joueur*/
    printf("vous êtes :\n");
    affich(perso);
    printf("vous jouez contre :\n");
    affich(monstre);
    delete_player(&perso);
    init_tab_sort(tab_sort);
    return 0;
}
