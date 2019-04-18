#include <combat.h>

int main(){
    init_tab_sort();
    init_menaces();
    create_inventory();
      srand(time(NULL));

    Personnage=creation_char();


    int i;

    for(i = 0; i< 10; i++){
      object_t* obj1= create_loot(4);

      if(fill_up_inventory(obj1) != KO_state);
      else{   /*il faut vérifier que l objet rejeté soit supprimé*/
          delete_object(&obj1);

      }
      obj1=NULL;
    }

    object_t* obj2= create_object(potion,3);
    fill_up_inventory(obj2);
    i=0;

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

    delete_player(&Personnage);
    delete_inventory();
    suppr_tab_sort();

    return 0;

}
