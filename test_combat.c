#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <combat.h>

int main(){
   character_t* joueur= creation_char();

   character_t* monstre= monster_creation(1);   /*niveau 1*/

   inventory_t* inventaire= create_or_delete_inventory();
   object_t* object=create_object(1);
   printf("vous avez comme objet :\n" );
   char * nom_obj= display_object(*object);

   printf("%s\n", nom_obj);
   fill_up_inventory(inventaire,object);
   int n=0;
   srand(time(NULL));
   do{

      fight_rand(50,&joueur,*inventaire);
      n++;
   }while(n<10);

   return 0;
}
