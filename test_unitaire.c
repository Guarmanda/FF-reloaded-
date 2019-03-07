#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int loot_type(){        /*si niv 10*/

  int value = rand() % 100;

  printf("valeur %d\n",value );
  if(value <15){
    return 0;              /* armor */
  }else if(value < 30){
    return 1;            /* weapon*/
  }else{
    return 2;/* potion a 70% d etre lootey */
  }
}

int main(){
   srand(time(NULL));
   for(int i=0; i< 20;i++){
      int loot=loot_type(10);
      printf("loot %d\n",loot );
   }

   return 0;
}
