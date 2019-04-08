#include <stdio.h>
#include <stdlib.h>
#include <commun_perso.h>


int main(){
    init_tab_sort();
    character_t* perso = creation_char();



  /*
    printf("entrez les coordonnees souhaitées pour x: ");
    scanf("%d", &position_x);
    printf("entrez les coordonnees souhaitées pour y: ");
    scanf("%d", &position_y);
 character_t* monstre2= monster_creation();   meme niveau que le joueur

    affich_stats(monstre);
      delete_adversaire(&monstre);*/
      perso->liste_spell=perso->liste_spell->debut_liste;
      do{

      free(&perso->liste_spell);
      perso->liste_spell=perso->liste_spell->sort_suivant;
    }while(perso->liste_spell != NULL);
    delete_player(&perso);
    suppr_tab_sort();

    return 0;
}
