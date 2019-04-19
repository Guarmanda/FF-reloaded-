/**
 * \file
 * \brief Programme de tests sur les objets et l'inventaire
 * \author Karman Nathalie, Papot Alexandre
 * \version 0.1
 * \date 6 avril 2019
 *
 * Jeux de tests pour les fonctions qui manipulent l'inventaire \a Inventaire du joueur
 *    et les objets et leur création
*/
#include <inventaire.h>

/**
 * \fn int main (void)
 * \brief Entrée du programme.
 *
 * \return EXIT_SUCCESS - Arrêt normal du programme.
 */
int main(){
    srand(time(NULL));
    create_inventory();
    int i;

      /*tests pour voir si dépassement de place dans l'inventaire*/
    for(i = 0; i< 10; i++){
      object_t* obj1= create_loot(4);

      if(fill_up_inventory(obj1) != KO_state);
      else{   /*il faut vérifier que l objet rejeté soit supprimé*/
          delete_object(&obj1);

      }
      obj1=NULL;
    }
    for(i = 0; i< 10; i++){
      object_t* obj1= create_loot(4);

      if(fill_up_inventory(obj1) != KO_state);
      else{   /*il faut vérifier que l objet rejeté soit supprimé*/
          delete_object(&obj1);

      }
      obj1=NULL;
    }
    for(i = 0; i< 10; i++){
      object_t* obj1= create_loot(4);

      if(fill_up_inventory(obj1) != KO_state);
      else{   /*il faut vérifier que l objet rejeté soit supprimé*/
          delete_object(&obj1);

      }
      obj1=NULL;
    }
    printf("affichage de l'inventaire AVANT la suppression que quelques éléments\n" );
    afficher_inventaire();
    /*test pour supprimer un objet dans l'inventaire (premier objet)*/
    printf("test pour supprimer un objet dans l'inventaire (objet 0 qui ne sera jamais saisi par l utilisateur)\n");
    printf("%d state\n",  deleteFrom_inventaire(0) );
    printf("test pour supprimer un objet dans l'inventaire (premier objet)\n");
    printf("%d state\n",  deleteFrom_inventaire(1) );
    printf("test pour supprimer un objet dans l'inventaire (milieu)\n");
    printf("%d state\n",  deleteFrom_inventaire(9) );
    printf("test pour supprimer un objet dans l'inventaire (dernier objet)\n");
    printf("%d state\n",  deleteFrom_inventaire(29) );
    printf("test pour supprimer un objet dans l'inventaire ( objet inexistant)\n");
    printf("%d state\n",  deleteFrom_inventaire(30) );
    printf("affichage de l'inventaire APRES la suppression que quelques éléments\n" );
    afficher_inventaire();

    delete_inventory();

    return EXIT_SUCCESS;
}
