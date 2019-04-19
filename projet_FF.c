#include <combat.h>



static void afficher_map(){
		int y;
		int x;
		printf("X : vous etes ici (x : %d y : %d) : \n", position_x, position_y);
		printf("village : ...\n");

		/*j represente l'axe x*/
		for(x = 0; x < 102; x++){
			printf("-");
		}
		printf("\n");

		for( y = 0 ; y < 25 ; y++){
			printf("|");

			for(x = 0; x < 100; x++){
				if(y == 25 - position_y/40 && x == position_x/10){ /
					printf("X");
				}
				else if(est_dans_village(x*10,y*40)){
					printf(".");
				}
				else{
					printf(" ");
				}
			}
			printf("|\n");
		}

		for(x = 0; x < 102; x++){
			printf("-");
		}
		printf("\n");
}

static void deplacement_joueur(){
		srand(time(NULL));
		int x;
		int y;
		int i;

		afficher_map();
		printf("Ou souhaitez vous vous deplacer ?\n");
		do{
			printf("x : ");
			scanf("%d",&x);
			viderBuffer();
		}while(x < 0 || x > 999);
		do{
			printf("y : ");
			scanf("%i", &y);
			viderBuffer();
		}while(y < 0 || y > 999);

		/*deplacement sur l'axe x*/

		while(position_x != x && etat_jeu != END_OF_GAME){
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

		while(position_y != y && etat_jeu != END_OF_GAME){
			system("clear");
			sleep(0.2);
			afficher_map();
			if(position_y < y){
				position_y++;
				fight_rand();
			}
			else{
				position_y--;
			}
			fight_rand();
		}
}

static void quitter_jeu(){
		delete_inventory();
		exit(1);
}

static void nouvelle_partie(){
		
		position_x = 500;
		position_y = 500;
		
		init_menaces();
		init_tab_sort();
		Personnage = creation_char();
		create_inventory();
		printf("Bienvenue, vous commencez votre aventure, avec deux potions de vie\n");
		fill_up_inventory(create_object(potion,2));
		fill_up_inventory(create_object(potion,2));
		printf("(Une arme et une tente se cache au coordonnees x : 505 et y : 505)\n");
		en_jeu();
}

static void continuer_partie(){
	init_menaces();
	init_tab_sort();
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
								case 1 : deplacement_joueur(); break;
								case 2 : sauvegarde_partie(Personnage); break;
								case 3 : afficher_inventaire(); break;
								case 4 : affich_stats(Personnage); break;
								case 5 : /*affich_quetes()*/; break;
								case 6 : afficher_map(); break;
								case 7 : quitter_jeu(); break;
				}
				if(position_x == 505 && position_y == 505){
					printf("\nVous trouvez une épée et une tente !\n");
					fill_up_inventory(create_object(tente,0));
					delete_object(&Personnage->char_weapon);
					Personnage->char_weapon = create_object(weapon,4);
				}
	}
	return 1;
}

int main (int argc, char**argv){
	srand(time(NULL));
	position_x = 0;
	position_y =40;	

	int choix = menu();

	switch(choix){
				case 1 : nouvelle_partie(); break;
				case 2 : continuer_partie(); break;
				case 3 : quitter_jeu(); break;
	}

	afficher_inventaire();
	en_jeu();

	return EXIT_SUCCESS;

}
