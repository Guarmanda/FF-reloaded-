#include <stdio.h>
#include <stdlib.h>
#include <perso.h>

int main(){
    character_t* perso = creation_char();
    character_t* monstre= monster_creation(perso->level);   /*meme niveau que le joueur*/
    printf("vous êtes :\n");
    affich(perso);
    printf("vous jouez contre :\n");
    affich(monstre);
    delete_player(&perso);

    return 0;
}
