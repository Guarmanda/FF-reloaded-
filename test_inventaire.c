#include <inventaire.h>
/**
 * \file test_inventaire.c
 * \brief jeux de tests pour les fonctions qui manipulent l'inventaire global du joueur
 * \author Karman Nathalie; Papot Alexandre
 * \date 6 avril 2019
 */

int main(){
    srand(time(NULL));

    create_inventory();
    int i;
    for(i = 0; i< 10; i++){
      object_t* obj1= create_loot(4);

      if(fill_up_inventory(obj1) != KO_state);
      else{   /*il faut vérifier que l objet rejeté soit supprimé*/
          delete_object(&obj1);

      }
      obj1=NULL;
    }
    afficher_inventaire();

    deleteFrom_inventaire(9);
    afficher_inventaire();
    delete_inventory();

    return 0;
}
