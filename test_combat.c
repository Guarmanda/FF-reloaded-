#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
/*ne pas oublier d inclure ncurses.h plus tard*/
#include <combat.h>

int main(){
  /*   spell_t* tab_sort ; tout debut de partie, on cree un tableau de sort commun pour tous
   int i;
      for (i = 0; i < TAILLE_TAB_SORT ;i ++)
         tab_sort[i] =malloc(sizeof (spell_t));
      init_tab_sort(&tab_sort);
*/
      character_t* joueur= creation_char();
      srand(time(NULL));

      inventory_t* inventaire= create_or_delete_inventory();
      object_t* tab_objet[5];

      for(i=0; i<5; i++ )
         tab_objet[i]=create_object(i);

      /*display_inventory(inventaire);*/
      printf("\t\t\t\t\tvous avez le(s) objet(s) suivant(s):\n" );
      char * nom_obj;

      for(i=0; i<5;i++ ){
         nom_obj= display_object(*tab_objet[i]);
         printf("\t\t\tobjet %d %s\n",i, nom_obj);
         fill_up_inventory(inventaire,tab_objet[i]);
      }

      i=0;


      do{
         printf("\n\t\t\t\t\t\tROUND %d \n",i);
         combat_on(&joueur,inventaire);
         i++;
         sleep(5);
         printf("\n\n\n\n");
      }while(i<5);


      return 0;
}
