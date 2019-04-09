#include <combat.h>

static void afficher_map(){
	int i;
	int j;
	printf("X : vous etes ici (x : %i y : %i) : \n", position_x, position_y);
	printf("village : ...\n");

	/*j represente l'axe x*/
	for(j = 0;j<102;j++){
		printf("-");
	}
	printf("\n");

	/*i represente l'axe y*/
	for(i = 0;i<25;i++){
		printf("|");

		/*j represente l'axe x*/
		for(j = 0;j<100;j++){
			if(i == 25 - position_y/40 && j == position_x/10){ /* affichage du personnage*/
				printf("X");
			}
			else if(est_dans_village(j*10,i*40)){
				printf(".");
			}
			else{
				printf(" ");
			}
		}
		printf("|\n");
	}

	/*i represente l'axe x*/
	for(i = 0;i<102;i++){
		printf("-");
	}
	printf("\n");
}

static void deplacement_joueur(){
	int x;
	int y;
	int i;
	afficher_map();
	printf("Ou souhaitez vous vous deplacer ?\n");
	do{
		printf("x : ");
		scanf("%i",&x);
	}while(x < 0 || x > 1000);
	do{
		printf("y : ");
		scanf("%i", &y);
	}while(y < 0 || y > 1000);

	/*deplacement sur l'axe x*/

	for(i = position_x;i != x;i++){
		system("clear");
		sleep(0.2);
		afficher_map();
		if(position_x < x){
			position_x++;
		}
		else{
			position_x--;
		}
		fight_rand();
	}

	for(i = position_y;i != y;i++){
		system("clear");
		sleep(0.2);
		afficher_map();
		if(position_y < y){
			position_y++;
		}
		else{
			position_y--;
		}
		fight_rand();
	}
}

static void quitter_jeu(){
	exit(1);
}

static void nouvelle_partie(){
	Personnage = creation_char();	
	create_inventory();
	en_jeu();
}

static void continuer_partie(){
	create_inventory();
	charger_partie();
	en_jeu();
}

int menu_en_jeu(){
	int choix;
	printf("Menu :\n");
	printf("1 : Se deplacer\n");
	printf("2 : Sauvegarder la partie\n");
	printf("3 : Voir l'inventaire\n");
	printf("4 : Voir la fiche personnage\n");
	printf("5 : Voir mission en cours\n");
	printf("6 : Voir la map\n");
	printf("7 : Quitter le jeu\n");

	do{
		printf("Votre choix : ");
		scanf("%i", &choix);
		viderBuffer();
	}while(choix < 1 || choix > 7);
	return choix;
}

int menu(){
	int choix;
	printf("Menu :\n");
	printf("1 : Lancer une nouvelle partie\n");
	printf("2 : Charger une partie\n");
	printf("3 : Quitter le jeu\n");

	do{
		printf("Votre choix : ");
		scanf("%i", &choix);
		viderBuffer();
	}while(choix < 1 || choix > 3);
	return choix;
}

int en_jeu(){

	int choix_joueur;

	/*etat_jeu*/
	while(etat_jeu != END_OF_GAME ){
		choix_joueur = menu_en_jeu();
		switch(choix_joueur){
			case 1 : deplacement_joueur();break;
			case 2 : sauvegarde_partie(Personnage);break;
			case 3 : afficher_inventaire();break;
			case 4 : affich_stats(Personnage);break;
			case 5 : printf("affichage des quetes ici\n");break;
			case 6 : afficher_map();break;
			case 7 : quitter_jeu();break;
		};
	}
	return 1;
}

int main (int argc, char**argv){
	position_x = 0;
	position_y =40;	/*prob de 0à 39*/
	int choix = menu();
	switch(choix){
		case 1 : nouvelle_partie();
		case 2 : continuer_partie();
		case 3 : quitter_jeu();
	};
	
	afficher_inventaire();
	en_jeu();
	
	/*
	object_t *obj1= create_object(3);
	fill_up_inventory(Inventaire,obj1);
	display_object(*obj1);
	sauvegarde_partie(Personnage,"caca.txt");
	*/


	return EXIT_SUCCESS;

	}