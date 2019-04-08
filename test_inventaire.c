#include <stdio.h>
#include <stdlib.h>
#include <inventaire.h>


int main(){
   printf("hi hi\n" );
    inventory_t* inventaire = create_or_delete_inventory();

    object_t* objet = create_object(2);
    fill_up_inventory(inventaire, objet);

    char *test;
    printf("\n\n\n\n");
    test = display_object(*objet);
    printf("la chaine est %s\n", test);
    return 0;
}
