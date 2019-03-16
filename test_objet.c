#include <stdio.h>
#include <stdlib.h>
#include <inventaire.h>


int main(){
    character_t* perso = creation_char();
    affich(perso);
    delete_player(perso);
    /* inventory_t inventaire = create_or_delete_inventory();
    character_t* monster= creation_char();
    monster->level=8;
    affich(monster);
    object_t* objet = create_object(*monster);
    fill_up_inventory(inventaire, objet);

    char *test = malloc(sizeof(char)*30);
    printf("\n\n\n\n");
    test = display_object(*objet);
    printf("%s", test);*/
    return 0;
}
