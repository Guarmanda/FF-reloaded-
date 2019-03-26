#include <affichage.h>
#include <map.h>
#include <quete.h>
#include <fonctions_affichage.h>
#include <ncurses.h>
#include <math.h>

void gestion_editeur(float x, float y, int selected, int running){}
void showInventory(){}
void detecter_touches(){}

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

void afficher_quete(float x, float y, char etat, char* phrase){
  switch(etat){
    case 'P':
      setcolor(14, 6);
      mvaddstr(y, x, "!");
      break;
    case 'F':
      mvaddstr(23, 20, phrase);
    case 'D':
      mvaddstr(23, 20, phrase);
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
