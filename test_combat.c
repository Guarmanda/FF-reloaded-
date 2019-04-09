#include <combat.h>

int main(){

    int i;
    create_inventory();
    Personnage= creation_char();
    srand(time(NULL));
    position_x =500; /*Position dans le village*/
    position_y = 500;

    init_menaces();/*initialise une seule fois les menaces*/

    do{
       printf("entrez les coordonnees souhaitées pour x: ");
       scanf("%d", &position_x);
       printf("entrez les coordonnees souhaitées pour y: ");
       scanf("%d", &position_y);
       int menaceTest=map_threat[position_x][position_y];
       printf("il y a une menace de %d%%\n",menaceTest );

       i--;
    }while(i < 5);

    return 0;

}
