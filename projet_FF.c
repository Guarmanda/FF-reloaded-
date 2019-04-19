/**
 * \file      projet_FF.c
 * \author    Nathalie Karman, Alexandre Papot
 * \version   1.0
 * \date     Mars 2019
 * \brief     Module principal du jeu (version beta)
 */
#include <combat.h>

/**
 * \fn static void afficher_map()
 * \brief Fonction d'affichage : affiche la map et l'emplacement du joueur
*/
static void afficher_map(){
		int y;
		int x;
		printf("X : vous etes ici (x : %d y : %d) : \n", position_x, position_y);
		printf("village : ...\n");


		for(x = 0; x < 102; x++){
			printf("-");
		}
		printf("\n");

		for( y = 0 ; y < 25 ; y++){
			printf("|");

			for(x = 0; x < 100; x++){
				if(y == 25 - position_y/40 && x == position_x/10){
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
/**
 * \fn static void deplacement_joueur()
 * \brief Fonction qui se charge du déplacement du joueur sur la carte
*/
static void deplacement_joueur(){

		int x;
		int y;

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
/**
 * \fn static int quitter_jeu()
 * \brief Fonction qui supprime toutes les allocations dynamiques et quitte le programme
 *\return OK_state qui indique la fin du programme
 *
 */
static int quitter_jeu(){
		suppr_tab_sort();
		delete_inventory();
		delete_player(&Personnage);
		return OK_state;
}

/**
 * \fn int menu(void)
 * \brief Fonction qui affiche le menu qui permet de jouer
 *
 * \return choix, le choix de l'utilisateur de 1 à 7
 */
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

/**
 * \fn int en_jeu(void)
 * \brief Fonction qui permet au joueur de jouer sa partie à partir des choix faits dans \a menu_en_jeu()
 *
 * \return etat_jeu (macros dans \a commun.h)
 */
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
	return etat_jeu;
}
/**
 * \fn static void nouvelle_partie()
 * \brief Fonction qui démarre une nouvelle partie (version béta)
 *
 */
static void nouvelle_partie(){

		position_x = 500;
		position_y = 500;

		init_menaces();
		init_tab_sort();
		Personnage = creation_char();
		create_inventory();
		clear_screen();
		printf("Bienvenue, vous commencez votre aventure, avec deux potions de vie en cadeau!\n");
		fill_up_inventory(create_object(potion,2));
		fill_up_inventory(create_object(potion,2));
		sleep(1);
		printf("\n...(Une arme et une tente se cachent au coordonnees x : 505 et y : 505)\n");
		sleep(2);
		en_jeu();
}
/**
 * \fn int menu(void)
 * \brief Fonction qui affiche le menu principal (premier menu) du jeu
 *
 * \return choix, le choix de l'utilisateur 1, 2 ou 3
 */
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

/**
 * \fn static void continuer_partie()
 * \brief Fonction qui charge les données de Personnage à partir d'un fichier.txt et reprend la partie sauvegardée
 *
 */
static void continuer_partie(){
	init_menaces();
	init_tab_sort();
	create_inventory();
	charger_partie();		/*fait un create_char pour charger la variable globale Personnage*/
	en_jeu();
}
/**
 * \fn int main (void)
 * \brief Entrée du programme.
 *
 * \return EXIT_SUCCESS - Arrêt normal du programme.
 */
int main (){
	srand(time(NULL));

	int sortie_prog=0;
	do{
			int choix = menu();

			switch(choix){
						case 1 : nouvelle_partie(); break;
						case 2 : continuer_partie(); break;
						case 3 : sortie_prog=quitter_jeu(); break;
			}


			en_jeu();
			if(etat_jeu == END_OF_GAME)
				clear_screen();
	}while(sortie_prog != 1);

	return EXIT_SUCCESS;

}
