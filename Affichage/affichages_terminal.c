#include <affichage.h>
#include <map.h>
#include <quete.h>
#include <fonctions_affichage.h>
#include <perso_commun.h>
#include <ncurses.h>
#include <math.h>
#include <inventaire.h>
#include <creationPerso.h>
#include <unistd.h>

void afficher_combat(character_t* monster[], int nb_monstres){
  for( i = 0; i < monster_number;i++){
    printf("\tAdversaire %d : %s (vie: %d/%d ; niveau : %d)\n",i+1, monster[i]->name,monster[i]->health, monster[i]->max_health, monster[i]->level);
  }
  printf("\n\tJoueur: %s (vie: %d/%d ; niveau : %d)\n\n",Personnage->name,Personnage->health, Personnage->max_health, Personnage->level);

}

int affich_choix(character_t * monster[], int nb_monster){

  /*int player_choice = 0;

  do{

       sleep(1);
       printf("Choisir entre les actions ci-dessous:\n\t1 - Attaquer l'adversaire\n\t2 - Prendre une potion\n\t3 - Appliquer un sort\n\t4 - S'évader\n\t5 - Quitter le jeu\nVotre choix : ");
       scanf("%d",&player_choice);
       viderBuffer();
  }while(player_choice > 5 || player_choice <1);

  return player_choice;*/


         char player_choice = '9'; /* voir plus tard pour que le joueur puisse selectionner dans le menu */
         do{
              box( fenetre, 0, 0 );
              fond_blanc();
              mvwprintw( fenetre,7, 10, "Vous êtes en combat, choisir entre les actions ci-dessous:" );
              mvwprintw( fenetre, 8, 10, " 1 - Attaquer l'adversaire\n");
              mvwprintw( fenetre, 9, 10, " 2 - Prendre une potion\n");
              mvwprintw( fenetre, 10, 10, " 3 - Appliquer un sort (à faire)\n");
              mvwprintw( fenetre, 11, 10, " 4 - S'évader\n");
              mvwprintw( fenetre, 12, 10, " 5 - Quitter le jeu\n");
              mvwprintw( fenetre, 13, 10, "Votre choix : ");
              mvwscanw(fenetre, 13, 27, " %c\n",&player_choice);
              sleep(2);
              faire_rendu();
              player_choice -= '0';
              viderBuffer();
              mvwprintw( fenetre,6, 10, "Votre choix est: %c", player_choice);
         }while(player_choice > 5 || player_choice <1);
         return player_choice;
}
int choisir_ennemi(character_t * monstre[], int nb_monster){
  int choix_j;
  int i;
  do{
     printf("Quel adversaire choisissez-vous? [0 pour retourner au menu précédent]\n");
     for( i = 0; i < nb_monstre; i++){
        printf("\tAdversaire %d : %s (vie: %d/%d)\n",i+1, tab_adv[i]->name,tab_adv[i]->health, tab_adv[i]->max_health);

     }
     printf("Votre choix: " );
     scanf("%d",&choix_j);
     viderBuffer();
  }while (choix_j > nb_monstre || choix_j< 0);
  return choix_j;
}

void gestion_editeur(float* x, float* y, int *selected, int *running){}
void detecter_touches(int*running){
  char ch = wgetch(fenetre);
	switch( ch ) {
			case 'i':
									showInventory();
									break;
			case 27:
									*running = 0;
                  wclear(fenetre);
									break;
  }
}

void afficher_selecteur(int x, int y){
  afficher_Map( x, y);
  faire_rendu();
}

/**
 * \fn void creerPerso_terminal()
 * \brief Fonction de gestion de l'édition du personnage en terminal
 */
void afficher_creation(char*name, char*class_char, char*gender){
	int running = -1; //la variable qui gère le choix du menu
	char classe[4][30] = { "Warrior", "Wizard", "Hunter", "Priest" };
	char genre[2][6] = { "Man", "Woman" };
	char item[30];
	int ch, i = 0, width = 30;
	wclear(fenetre);
	initscr(); // initialize Ncurses
	box( fenetre, 0, 0 ); //initialisation des bordures
	//affichage des boutons
	for( i=0; i<4; i++ ) {
			if( i == 0 )
					wattron( fenetre, A_STANDOUT ); //on surligne le premier
			else
					wattroff( fenetre, A_STANDOUT );
			mvwprintw( fenetre, i+12, 30, "%s", classe[i] );
	}
	for( i=0; i<2; i++ ) {
		if( i == 0 )
				wattron( fenetre, A_STANDOUT ); //on surligne le premier
		else
			wattroff( fenetre, A_STANDOUT );
		mvwprintw( fenetre, i+12, 50, "%s", genre[i] );
	}
	mvwprintw( fenetre, 12, 10, "Nom: %s        ", name);
	mvwprintw( fenetre, 13, 10, "Classe: %s     ", class_char);
	mvwprintw( fenetre, 14, 10, "Genre: %s      ", gender);
	wrefresh( fenetre ); //mise à jour de l'écran
	int classe_ind = 0;
	int genre_ind = 0;
	noecho(); //désactivation de l'écho des caratères
	keypad( fenetre, TRUE ); //on autorise à taper des trucs
	curs_set( 0 ); //on cache le curseur du terminal

	//détection de la touche
	while(( ch = wgetch(fenetre)) != '\n'){
					mvwprintw( fenetre, classe_ind+12, 30, "%s", classe[classe_ind] );
					mvwprintw( fenetre, genre_ind+12, 50, "%s", genre[genre_ind] );
					switch( ch ) {
							case KEY_UP:
													classe_ind--;
													classe_ind = ( classe_ind<0 ) ? 3 : classe_ind;
													break;
							case KEY_DOWN:
													classe_ind++;
													classe_ind = ( classe_ind>3 ) ? 0 : classe_ind;
													break;
							case KEY_LEFT:
													genre_ind--;
													genre_ind = ( genre_ind<0 ) ? 1 : genre_ind;
													break;
							case KEY_RIGHT:
													genre_ind++;
													genre_ind = ( genre_ind>1 ) ? 0 : genre_ind;
													break;
					}
					wattron( fenetre, A_STANDOUT );
					mvwprintw( fenetre, classe_ind+12, 30, "%s", classe[classe_ind]);
					mvwprintw( fenetre, genre_ind+12, 50, "%s", genre[genre_ind]);
					sprintf(class_char,"%s", classe[classe_ind]);
					sprintf(gender, "%s", genre[genre_ind]);
					wattroff( fenetre, A_STANDOUT );
					mvwprintw( fenetre, 12, 10, "Nom: %s        ", name);
					mvwprintw( fenetre, 13, 10, "Classe: %s     ", class_char);
					mvwprintw( fenetre, 14, 10, "Genre: %s      ", gender);
	}
    mvwscanw(fenetre, 13, 27, " %s\n", name);
}


/**
 * \fn void showMap(float x, float y)
 * \brief Gère l'affichage de la map et du joueur en terminal
 * \param[in] Abscisse du joueur
 * \param[in] Ordonnée du joueur
 */
void afficher_Map(float x, float y){
  //on rend accessible les nouvelles coordonnées du joueur pour les monstres/quetes
  X=x;
  Y=y;

  for(int i=y-11; i<=y+12;i++){
    for(int j=x-40; j<x+40; j++){
      int x2 = j-(x-40);
      int y2 = i-(y-12);
      switch(map[i][j]){
        case 1:
        case 3://arbres
          setcolor(10, 2);
          mvaddstr( y2, x2, "T" ); break;
        case 2://eau
          setcolor(14, 3);
          mvaddstr(  y2, x2, "~" ); break;
        case 4://routes
          setcolor(8, 0);
          mvaddstr(  y2, x2, "#" ); break;
        case 6://maisons
          setcolor(14, 4);
          mvaddstr(  y2, x2, "M" ); break;
        case 5://herbe
          setcolor(2, 2);
          mvaddstr(  y2, x2, " "); break;
      }
    }
  }//joueur
  setcolor(15, 7);
  mvaddstr(  11, 39, "P");
}



int afficher_menu(char list[4][30]){
	int ch, i = 0, width = 30;
	box( fenetre, 0, 0 ); //initialisation des bordures
	//affichage des boutons
	for( i=0; i<4; i++ ) {
			if( i == 0 )
					wattron( fenetre, A_STANDOUT ); //on surligne le premier
			else
					wattroff( fenetre, A_STANDOUT );
			mvwprintw( fenetre, i+12, 30, "%s", list[i] );
	}
	wrefresh( fenetre ); //mise à jour de l'écran
	int running = 0;
	noecho(); //désactivation de l'écho des caratères
	keypad( fenetre, TRUE ); //on autorise à taper des trucs
	curs_set( 0 ); //on cache le curseur du terminal

	//détection de la touche
	while(( ch = wgetch(fenetre)) != '\n'){
					mvwprintw( fenetre, running+12, 30, "%s", list[running] );
					switch( ch ) {
							case KEY_UP:
													running--;
													running = ( running<0 ) ? 3 : running;
													break;
							case KEY_DOWN:
													running++;
													running = ( running>3 ) ? 0 : running;
													break;
					}
					wattron( fenetre, A_STANDOUT );
					mvwprintw( fenetre, running+12, 30, "%s", list[running]);
					wattroff( fenetre, A_STANDOUT );
	}
	return running;
}

void showInventory(){
  int running = -1; //la variable qui gère le choix du menu
  char classe[Inventaire->nb_objects][30];
  for(int i=0; i<Inventaire->nb_objects; i++){
    strcpy(classe[i], Inventaire->object[i]->name_object);
  }
  char item[30];
  int ch, i = 0, width = 30;
  wclear(fenetre);
  initscr(); // initialize Ncurses
  box( fenetre, 0, 0 ); //initialisation des bordures
  //affichage des boutons
  for( i=0; i<Inventaire->nb_objects; i++ ) {
      if( i == 0 )
          wattron( fenetre, A_STANDOUT ); //on surligne le premier
      else
          wattroff( fenetre, A_STANDOUT );
      mvwprintw( fenetre, i+12, 30, "%s", classe[i] );
  }
  mvwprintw( fenetre, 12, 10, "Nom: %s        ", Personnage->name);
  mvwprintw( fenetre, 13, 10, "Classe: %s     ", Personnage->class_char);
  mvwprintw( fenetre, 14, 10, "Genre: %s      ", Personnage->gender);
  wrefresh( fenetre ); //mise à jour de l'écran
  int classe_ind = 0;

  noecho(); //désactivation de l'écho des caratères
  keypad( fenetre, TRUE ); //on autorise à taper des trucs
  curs_set( 0 ); //on cache le curseur du terminal

  //détection de la touche
  while(( ch = wgetch(fenetre)) != '\n'){
          mvwprintw( fenetre, classe_ind+12, 30, "%s", classe[classe_ind] );
          switch( ch ) {
              case KEY_UP:
                          classe_ind--;
                          classe_ind = ( classe_ind<0 ) ? Inventaire->nb_objects-1 : classe_ind;
                          break;
              case KEY_DOWN:
                          classe_ind++;
                          classe_ind = ( classe_ind>Inventaire->nb_objects-1 ) ? 0 : classe_ind;
                          break;
          }
          wattron( fenetre, A_STANDOUT );
          mvwprintw( fenetre, classe_ind+12, 30, "%s", classe[classe_ind]);
          wattroff( fenetre, A_STANDOUT );
          mvwprintw( fenetre, 12, 10, "Nom: %s        ", Personnage->name);
          mvwprintw( fenetre, 13, 10, "Classe: %s     ", Personnage->class_char);
          mvwprintw( fenetre, 14, 10, "Genre: %s      ", Personnage->gender);
    }
}

void afficher_quete(float x, float y, int i, char etat){
  switch(etat){
    case 'P':
      setcolor(14, 6);
      mvaddstr(y, x, "!");
      break;
    case 'F':
      mvaddstr(23, 10, quetes[i]->pnj_nom);
      mvaddstr(23, 20, quetes[i]->phrase_fin);
    case 'D':
      mvaddstr(23, 10, quetes[i]->pnj_nom);
      mvaddstr(23, 20, quetes[i]->phrase_debut);
      break;
    case 'B':
      setcolor(14, 6);
      mvaddstr(y, x, "B");
      break;

  }
}

int detecter_mouvement(float*x, float*y){
  //l'état du clavier à l'instant actuel
  int touche = wgetch(fenetre); //en terminal
  //si c'est une touche de mouvement
  if(touche == KEY_UP || touche == KEY_DOWN || touche == KEY_LEFT || touche == KEY_RIGHT){
    //on gère les colisions et la vitesse du perso
    //on a besoin de regarder à quel endroit de la map on est et ce qu'il y a après
    //on fait cohabiter le sdl et le terminal pour un code le plus optimisé possible
    if (touche == KEY_RIGHT && (map[(int)(floor(*y))][(int)(floor(*x+VITESSE_PERSO))]==4 || map[(int)(floor(*y))][(int)(floor(*x+VITESSE_PERSO))]==5)) *x+=VITESSE_PERSO;
    else if (touche == KEY_LEFT && (map[(int)(floor(*y))][(int)(floor(*x-VITESSE_PERSO))]==4 || map[(int)(floor(*y))][(int)(floor(*x-VITESSE_PERSO))]==5)) *x-=VITESSE_PERSO;
    if (touche == KEY_UP && (map[(int)(floor(*y-VITESSE_PERSO))][(int)(floor(*x))]==4 || map[(int)(floor(*y-VITESSE_PERSO))][(int)(floor(*x))]==5)) *y-=VITESSE_PERSO;
    else if (touche == KEY_DOWN && (map[(int)(floor(*y+VITESSE_PERSO))][(int)(floor(*x))]==4 || map[(int)(floor(*y+VITESSE_PERSO))][(int)(floor(*x))]==5)) *y+=VITESSE_PERSO;
    if(*x<0) *x=0;
    if(*y<0) *y=0;
    if(*x>999) *x=999;
    if(*y>999) *y=999;
    return 1;
  }
  return 0;
}
