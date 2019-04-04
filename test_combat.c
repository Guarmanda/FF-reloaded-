

#include <combat.h>

int main(){
   /*  spell_t *sorts = malloc(sizeof(*sorts)*TAILLE_TAB_SORT);
       */
       int i;
       etat_jeu=1;


       Personnage= creation_char();
       srand(time(NULL));
       position_x =500;
       position_y = 500;

       Inventaire= create_or_delete_inventory();
       object_t* tab_objet[5];

       /*display_inventory(inventaire);*/
       printf("\t\t\t\t\tvous avez le(s) objet(s) suivant(s):\n" );
       char * nom_obj;

       for(i=0; i<5;i++ ){
          tab_objet[i]=create_object(i);
          nom_obj= display_object(*tab_objet[i]);
          printf("\t\t\tobjet %d %s\n",i, nom_obj);
          fill_up_inventory(Inventaire,tab_objet[i]);
       }
      
       init_menaces();/*initialise une seule fois les menaces*/

       do{
          printf("entrez les coordonnees souhaitées pour x: ");
          scanf("%d", &position_x);
          printf("entrez les coordonnees souhaitées pour y: ");
          scanf("%d", &position_y);
          int menaceeee=map_threat[position_x][position_y];
          printf("il y a une menace de %d\n",menaceeee );
          int res=fight_rand();
          if(res);
          else{
             printf("vous l avez echappé belle\n");
          }
          i--;
       }while(i<5);

       for(i=0; i<5;i++ ){
          delete_object(&(tab_objet[i]));
       }
       return 0;


}
