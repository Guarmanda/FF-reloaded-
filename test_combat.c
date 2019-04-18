#include <combat.h>

int main(){

    init_tab_sort();
    init_menaces();
    create_inventory();
    srand(time(NULL));

    Personnage=creation_char();

    afficher_sorts(Personnage);

    object_t* obj2= create_object(potion,3);
    fill_up_inventory(obj2);
    object_t* obj1= create_object(potion,2);
    fill_up_inventory(obj1);



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



    return 0;

}
