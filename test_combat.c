#include <combat.h>

int main(){
    init_tab_sort();
    init_menaces();
    create_inventory();
    srand(time(NULL));

    Personnage = creation_char();
    printf("les stats du perso\n" );
    affich_stats(Personnage);
    afficher_sorts(Personnage);
    position_x =500; /*Position dans le village*/
    position_y = 500;
    object_t* obj1 = create_object(potion,3);
    affectation_object(obj1);
    fill_up_inventory(obj1);

    object_t* obj2 =create_object(potion,0);
    affectation_object(obj2);
    fill_up_inventory(obj2);

    object_t* obj3 = create_object(potion,2);
    affectation_object(obj3);
    fill_up_inventory(obj3);

    printf("Ceci est un test pour les coordonnees de la map qui contient les pourcentages de menace\n" );
    int i=0;
    do{
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
      i++;
    }while(i < 10);

    delete_player(&Personnage);
    suppr_tab_sort();

    return 0;

}
