#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
/*ne pas oublier d inclure ncurses.h plus tard*/
#include <combat.h>

int main(){
   /*  spell_t *sorts = malloc(sizeof(*sorts)*TAILLE_TAB_SORT);
       */int i;

       position_x =501;
       position_y = 400;
     /*  init_tab_sort(sorts);
       printf("sort 0 %s\n",sorts[0].nom_sort );
       printf("sort 1 %s\n",sorts[1].nom_sort );
       printf("sort 16 %s\n",sorts[16].nom_sort );*/
     /*  detruire_tab_sort(&sorts);*/
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
       character_t* advers=monster_creation();
       character_t* advers2=monster_creation();
        /*
             do{
                printf("\n\n\n\n\t\t\t\t\ttROUND %d\n",i);
                combat_on(&joueur,inventaire);
                i++;
                sleep(5);
                printf("\n\n\n\n");
             }while(i<5);
       */
       for(i=0; i<5;i++ ){
          delete_object(&(tab_objet[i]));
       }
       return 0;


}
