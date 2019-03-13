#include <stdio.h>
#include <stdlib.h>
#include <combat.h>

int main(){
    character_t* perso = creation_char();
    affich(perso);
    delete_player(perso);
    int niv=2;
    character_t* monstre= monster_creation(niv);
    return 0;
}
