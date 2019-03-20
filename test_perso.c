#include <stdio.h>
#include <stdlib.h>
#include <perso.h>

int main(){
    character_t* perso = creation_char();
    affich(perso);
    delete_player(perso);
    return 0;
}
