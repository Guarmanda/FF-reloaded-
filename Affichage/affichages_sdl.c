/**
 * \file      affichages_sdl.c
 * \author    Girod Valentin
 * \version   1.0
 * \date     Mars 2019
 * \brief    Contient toutes les fonctions d'affichage du jeu en sdl
 */
#include <affichage.h>
#include "../map.h"
#include <fonctions_affichage.h>
#include "SDL2/include/SDL2/SDL.h"
#include "../map_menace.h"
#include <math.h>



/**
 * \fn void afficher_degat(character_t * attaquant, character_t * cible, int degats, character_t* monster[], int nb_monstres)
 * \brief affiche les dégats causés lors d'une attaque
 * \param[in] attaquant
 * \param[in] cible
 * \param[in] degats
 * \param[in] tableau des monstres du combat
 * \param[in] nombre de monstres
*/
void afficher_degat(character_t * attaquant, character_t * cible, int degats, character_t* monster[], int nb_monstres){
  character_t * Personnage = getPersonnage();
  float colonne;
  if(strcmp(attaquant->name, Personnage->name) == 0){
    colonne = getScreenWidth()/100*75;
  }
  else{
    colonne = getScreenWidth()/100*25;
  }
  char degat[10];
  sprintf(degat, "-%d", degats);
  for(int i=0; i<500; i++){
    afficher_combat(monster, nb_monstres);
    drawText(colonne, getScreenHeight()/2-i,degat ,50,18);
    faire_rendu();
  }
}

/**
 * \fn void afficher_combat(character_t * monster[], int nb_monster)
 * \brief affiche les monstres et leur statistiques pendant le combat
 * \param[in] tableau des monstres du combat
 * \param[in] nombre de monstres
*/
void afficher_combat(character_t* monster[], int nb_monstres){
  character_t * Personnage = getPersonnage();
  drawImage(0,0, "interface_combat", getScreenWidth(), getScreenHeight());
  char sprite[30] = "";
	strcat(sprite, Personnage->class_char);
	strcat(sprite, "_");
	strcat(sprite, Personnage->gender);
	strcat(sprite, "_right");
  char niveau[20];
  sprintf(niveau, "Niveau: %d", Personnage->level);
  char vie[20];
  sprintf(vie, "Vie: %d/%d", Personnage->health, Personnage->max_health);
  char mana[20];
  sprintf(mana, "Mana: %d/%d", Personnage->mana, Personnage->max_mana);
  drawText(getScreenWidth()/100*15, getScreenHeight()/100*(25-10),niveau ,25,9);
  drawText(getScreenWidth()/100*15, getScreenHeight()/100*(25-7),vie ,25,9);
  drawText(getScreenWidth()/100*15, getScreenHeight()/100*(25-4),mana ,25,9);
  drawImage(getScreenWidth()/100*15, getScreenHeight()/100*25, sprite,60,60);
  for(int i=0; i<nb_monstres; i++){
    char niveau[20];
    sprintf(niveau, "Niveau: %d", monster[i]->level);
    char vie[20];
    sprintf(vie, "Vie: %d/%d", monster[i]->health, monster[i]->max_health);
    char mana[20];
    sprintf(mana, "Mana: %d/%d", monster[i]->mana, monster[i]->max_mana);
    drawText(getScreenWidth()/100*85, getScreenHeight()/100*(25*(i+1)-10),niveau ,25,9);
    drawText(getScreenWidth()/100*85, getScreenHeight()/100*(25*(i+1)-7),vie ,25,9);
    drawText(getScreenWidth()/100*85, getScreenHeight()/100*(25*(i+1)-4),mana ,25,9);
    drawImage(getScreenWidth()/100*85, getScreenHeight()/100*(25*(i+1)), monster[i]->name,120,120);
  }

}

/**
 * \fn int affich_choix(character_t * monster[], int nb_monster)
 * \brief Gère l'affichage des choix à faire pendant le tour du joueur dans un combat
 * \param[in] tableau des monstres du combat
 * \param[in] nombre de monstres
 * \return un int qui représente le choix fait
*/
int affich_choix(character_t * monster[], int nb_monster){
          faire_rendu();
         int player_choice = 0; /* voir plus tard pour que le joueur puisse selectionner dans le menu */
         char desc_choix[5][30] = {"Attaquer l'adversaire", "prendre une potion", "Appliquer un sort", "S'évader", "Quitter le jeu (rageux!)"};
         int selection_choix = 0; //permet de recharger l'écran à intervales moins réguliers, réduit donc la consommation de ressources et les bugs
         do{
           SDL_Event e;
           while(SDL_PollEvent(&e)) {
             switch(e.type) {
               case SDL_MOUSEBUTTONDOWN:
               //quand on clique, si on clique au dessus du sélecteur, on va choisir un monstre.
               //Sinon, on regarde si on a cliqué dans une case du sélecteur.
               {
                 int mouse_x, mouse_y;
                 SDL_GetMouseState(&mouse_x, &mouse_y);
                   //si on est à la hauteur d'une case du sélecteur
                 if(mouse_y>getScreenHeight()-100 && mouse_y<getScreenHeight()){
                   //la position de x sur l'image
                   int pos = mouse_x;
                   for(int j=20.7*getScreenWidth()/100,i = 1; j<pos+6.7*getScreenWidth()/100 ;i++, j+=8.27*getScreenWidth()/100){
                     if(pos >= j && pos <= j+6.7*getScreenWidth()/100){
                       //i corresponds au numéro de la case du sprite sélectionné,
                       player_choice = i;
                     }
                   }
                 }
               break;
              }
              case SDL_MOUSEMOTION:
              //quand on clique, si on clique au dessus du sélecteur, on va choisir un monstre.
              //Sinon, on regarde si on a cliqué dans une case du sélecteur.
              {
                int mouse_x, mouse_y;
                SDL_GetMouseState(&mouse_x, &mouse_y);
                  //si on est à la hauteur d'une case du sélecteur
                if(mouse_y>getScreenHeight()-100 && mouse_y<getScreenHeight()){
                  //la position de x sur l'image
                  int pos = mouse_x;
                  for(int j=20.7*getScreenWidth()/100,i = 1; j<pos+6.7*getScreenWidth()/100 ;i++, j+=8.27*getScreenWidth()/100){
                    if(pos >= j && pos <= j+6.7*getScreenWidth()/100){
                      //i corresponds au numéro de la case du sprite sélectionné,
                      if(i<=5 && selection_choix != i){
                        selection_choix = i;
                        afficher_combat(monster, nb_monster);
                        drawText((j+3.35*getScreenWidth()/100)-15*(strlen(desc_choix[i-1])/2), getScreenHeight()-getScreenHeight()/100*25, desc_choix[i-1], 35, 15);
                        faire_rendu();
                      }
                    }
                  }
                }
                else if(selection_choix !=0){
                  selection_choix = 0;
                  afficher_combat(monster, nb_monster);
                  faire_rendu();
                }
              break;
             }
             }
           }
           SDL_Delay(5);
         }while(player_choice > 5 || player_choice <1);
         return player_choice;
  }

/**
 * \fn int choisir_ennemi(character_t * monster[], int nb_monster)
 * \brief Gère l'affichage de la sélection d'un monstre à attaquer
 * \param[in] tableau des monstres du combat
 * \param[in] nombre de monstres
 * \return l'index du monstre sélectionné
*/
int choisir_ennemi(character_t * monster[], int nb_monster){
  int choix = 0;
  do{
      SDL_Event e;
      while(SDL_PollEvent(&e) && choix == 0) {
        switch(e.type) {
          case SDL_MOUSEBUTTONDOWN:
          //quand on clique, si on clique au dessus du sélecteur, on va choisir un monstre.
          //Sinon, on regarde si on a cliqué dans une case du sélecteur.
          {
            int mouse_x, mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            //si on est dans la colonne des monstres
            if(mouse_x>=getScreenWidth()/100*85 && mouse_x <=getScreenWidth()/100*85+120){
              //si on est à la hauteur d'un monstre
                int pos = mouse_y;
                for(int i = 0, j=getScreenHeight()/100*(25*(i+1)); j<pos+120 ;i++, j=getScreenHeight()/100*(25*(i+1))){
                  if(pos >= j && pos <= j+120){
                    //i corresponds au numéro de la case du sprite sélectionné,
                    printf("%d\n", i);
                    choix = i+1;
                  }
                }
              }
            }
          break;
          case SDL_MOUSEMOTION:
          //quand on clique, si on clique au dessus du sélecteur, on va choisir un monstre.
          //Sinon, on regarde si on a cliqué dans une case du sélecteur.
          {
            int mouse_x, mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            //si on est dans la colonne des monstres
            if(mouse_x>=getScreenWidth()/100*85 && mouse_x <=getScreenWidth()/100*85+120){
              //printf("%d, %d\n", mouse_x, mouse_y);
              //si on est à la hauteur d'un monstre
                int pos = mouse_y;
                for(int i = 0, j=getScreenHeight()/100*(25*(i+1)); j<pos+120 ;i++, j=getScreenHeight()/100*(25*(i+1))){
                  if(pos >= j && pos <= j+120){
                    //i corresponds au numéro de la case du sprite sélectionné,
                    afficher_combat(monster, nb_monster);
                    SDL_ShowCursor(SDL_DISABLE);
                    drawImage(mouse_x-20, mouse_y-20, "sword", 40, 40);
                    faire_rendu();
                  }
                  else{
                      afficher_combat(monster, nb_monster);
                      SDL_ShowCursor(SDL_ENABLE);
                      faire_rendu();
                  }
                }
            }
              else{
                afficher_combat(monster, nb_monster);
                SDL_ShowCursor(SDL_ENABLE);
                faire_rendu();
              }
            }
          break;
        }
      }
      SDL_Delay(5);
  }while (choix > nb_monster || choix< 1);
  SDL_ShowCursor(SDL_ENABLE);
  return choix;
}


/**
 * \fn void afficher_inv(int PH, int PW, int H, int W, int PSH, int PSW, int partie_items)
 * \brief Gère l'affichage de l'inventaire
 * \param[in] 1% de la largeur de l'image d'inventaire en pixels
 * \param[in] 1% de la hauteur de l'image d'inventaire en pixels
 * \param[in] pixels en largeur de l'image
 * \param[in] pixels en hauteur de l'image
 * \param[in] abscisse de l'image sur l'écran
 * \param[in] ordonnée de l'image sur l'écran
 * \param[in] un entier qui représente la partie de l'inventaire qui est affichée, comme tous les items ne peuvent être affichés en meme temps
 */
void afficher_inv(int PH, int PW, int H, int W, int PSH, int PSW, int partie_items){
  character_t * Personnage = getPersonnage();
  //la longueur des barres de vie/mana/xp est de 8.54% de l'image, suivie d'une autre barre de 8.54% de l'image d'une autre couleur pour la barre vide
  //Il faut (pour l'instant) 100xp par niveau, 100hp en tout,
  //8.54%/100 = le nombre de pixels pour 1xp
  //nouvelle taille en pixels de l'image: (getScreenHeight()/100)*90
  //8.54% de cette taille = nb de pixels qu'il faut

  float pixels = ((getScreenWidth()/100)*95/100*8.54);
  //calcul du nombre d'xp du niveau actuel:
  //int actual_xp = 100-Personnage->level*100-Personnage->xp;
  int actual_xp=Personnage->xp;

  //le calcul du nombre de pixels pour afficher le texte suis la même logique que les pixels

  //variables de taille du texte et chaine de charactère pour afficher les nombres
  char num[3];
  int textH = 55;
  int textW = 35;

  //affichage des barres
  drawImage( (Personnage->health*pixels/100)-pixels+PSW, PSH, "life_bar.png", W, H);
  drawImage( actual_xp*pixels/100-pixels+PSW, PSH, "xp_bar.png", W, H);
  drawImage( Personnage->mana*pixels/100-pixels+PSW, PSH, "mana_bar.png", W, H);
  drawImage( PSW, PSH, "inventory.png", W, H);

  //affichage du level
  float PxTextXlevel = ((getScreenWidth()/100)*47);
  float PxTextYlevel = ((getScreenWidth()/100)*2.8);
  sprintf(num,"%d",Personnage->level);
  drawText( PxTextXlevel, PxTextYlevel, num, textH, textW);


  float PxTextXActuel = ((getScreenWidth()/100)*35.1); //X ne change pas pour les 3 premier nombres
  float PxTextYVie = ((getScreenWidth()/100)*7.2);
  float PxTextYXP = ((getScreenWidth()/100)*11.2);
  float PxTextYMana = ((getScreenWidth()/100)*15.2);

  //affichage des valeurs des barres
  sprintf(num,"%d",Personnage->health);
  drawText( PxTextXActuel, PxTextYVie, num, textH, textW);
  sprintf(num,"%d",actual_xp);
  drawText( PxTextXActuel, PxTextYXP, num, textH, textW);
  sprintf(num,"%d",Personnage->mana);
  drawText( PxTextXActuel, PxTextYMana, num, textH, textW);

  PxTextXActuel = ((getScreenWidth()/100)*47); //on redéfinit X pour les 3 autres nombres, y ne change pas

  //affichage des valeurs max des barres
  drawText( PxTextXActuel, PxTextYVie, "100", textH, textW);
  drawText( PxTextXActuel, PxTextYXP, "100", textH, textW);
  drawText( PxTextXActuel, PxTextYMana, "100", textH, textW);

  //affichage des items équipés
  //Les images des items ont les mêmes noms que les items eux-même, cela facilite leur affichage graçe à la fonction
  //display_object dans perso.c
  drawImage( (getScreenWidth()/100)*75.75, (getScreenHeight()/100)*37, Personnage->char_armor->name_object, 110, 110);
  drawImage( (getScreenWidth()/100)*60.75, (getScreenHeight()/100)*37, Personnage->char_weapon->name_object, 110, 110);

  //affichage de l'accessoire
  char accessory[20];
  if(Personnage->accessory==green_amulet) sprintf(accessory, "%s", "green amulet");
  if(Personnage->accessory==ruby_ring) sprintf(accessory, "%s", "ruby ring");
  if(Personnage->accessory==crystal_ring) sprintf(accessory, "%s", "crystal ring");
  drawImage( (getScreenWidth()/100)*60.75, (getScreenHeight()/100)*9, accessory, 110, 110);


  //affichage des items de l'inventaire
  inventory_t * Inventaire = getInventaire();
  for(int i=15*partie_items, j=0, k=0; i<Inventaire->nb_objects && i < partie_items+15; i++, j++){
    if(i%5==0 && i!=0 && i!=15){
      j=0;
      k++;
    }
    drawImage( (j*9.25+3.05)*PW+PSW, (k*15.25+61)*PH+PSH, Inventaire->object[i]->name_object, 60, 60);
    //strcpy(item[i], display_object(*(Inventaire->object[i])));
  }
  faire_rendu();
}

/**
 * \fn void showInventory()
 * \brief Gère les interractions avec l'inventaire
 */
void showInventory(){
  //les pixels de l'image
  int W = 95*getScreenWidth()/100;
  int H = getScreenHeight();

  //les pixels qui représentent 1% de l'image
  int PW = W/100;
  int PH = H/100;

  //les pixels qui représentent les coordonnées de l'image
  int PSW = 2.5*getScreenWidth()/100;
  int PSH = 0;
  //l'inventaire est séparé en deux parties étant donné que l'image contient 15 cases d'inventaire
  //et que l'inventaire peut contenir 30 items
  int partie_items = 0;
  afficher_inv(PH, PW, H, W, PSH, PSW, partie_items);
  int running = 1;
  while(running) {
  	SDL_Event e;
  	while(SDL_PollEvent(&e)) {
  		switch(e.type) {
        case SDL_KEYDOWN:
        {
          //l'état du clavier à l'instant actuel
          const Uint8 *state = SDL_GetKeyboardState(NULL);

          //si c'est la touche d'inventaire, ou la touche échap, ou la touche entrée
          if(state[SDL_SCANCODE_I] || state[SDL_SCANCODE_ESCAPE] || state[SDL_SCANCODE_RETURN]){
            running = 0;
          }

          break;
        }
        case SDL_MOUSEBUTTONDOWN:
        //quand on clique, si on clique au dessus du sélecteur, on va placer une case.
        //Sinon, on regarde si on a cliqué dans une case du sélecteur.
        {
          int mouse_x, mouse_y;
          SDL_GetMouseState(&mouse_x, &mouse_y);
          //si on est sur la fleche vers le bas
          printf("souris y: %d x: %d, y: %d%% x: %d%% \n", mouse_y, mouse_x, mouse_y/PH, (mouse_x-PSW)/PW);
          printf("coordonnées: y: %.2f, %.2f, x: %.2f, %.2f\n", 74.7*PH, 93.66*PH, 43.82*PW+PSW, 51.6*PW+PSW);
          if(mouse_y > 82.7*PH && mouse_y < 102.66*PH && mouse_x > 47.82*PW+PSW && mouse_x < 55.6*PW+PSW){
            partie_items = 1;
            printf("partieitem %d\n", partie_items);
            afficher_inv(PH, PW, H, W, PSH, PSW, partie_items);
          }
          else if(mouse_y < 80.66*PH && mouse_y > 59.55*PH && mouse_x > 47.82*PW+PSW && mouse_x < 55.6*PW+PSW){
            partie_items = 0;
            printf("partieitem %d\n", partie_items);
            afficher_inv(PH, PW, H, W, PSH, PSW, partie_items);
          }
        break;
      }
      }
    }
  }
    float X = getX();
  float Y = getY();
  afficher_Map( X, Y);
  faire_rendu();

}

/**
 * \fn void afficher_selecteur(int x, int y)
 * \brief Gère l'affichage du sélecteur de sprite dans l'éditeur de map
 * \param[in] Abscisse du joueur
 * \param[in] Ordonnée du joueur
 */
void afficher_selecteur(int x, int y){
  int x_select = (getScreenWidth()-1200)/2;
  afficher_Map( x, y);
  drawImage( x_select, getScreenHeight()-150, "item_selector.png", 1200, 150);
  faire_rendu();
}

/**
 * \fn void afficher_Map(float x, float y)
 * \brief Gère l'affichage de la map et du joueur en SDL
 * \param[in] Abscisse du joueur
 * \param[in] Ordonnée du joueur
 */
void afficher_Map(float x, float y){
  int ** map = getMap();
  float X = getX();
  float Y = getY();
  character_t * Personnage = getPersonnage();
  //le nombre de sprites à afficher, tout comme la position du joueur, dépend de la taille de l'écran
  float nbSpriteX = getScreenWidth()/getSpriteW();
  float nbSpriteY = getScreenHeight()/getSpriteW();

  //on veux savoir quelle sprite de joueur afficher
  char sprite[30] = "";
	strcat(sprite, Personnage->class_char);
	strcat(sprite, "_");
	strcat(sprite, Personnage->gender);
	strcat(sprite, "_");
  if (X>x) strcat(sprite, "left");
  else if (X<x) strcat(sprite, "right");
  else if (Y>y) strcat(sprite, "forward");
  else if (Y<y) strcat(sprite, "back");
  else strcat(sprite, "back");

  //on rend accessible les nouvelles coordonnées du joueur pour les monstres/quetes
  setX(x);
  setY(y);
  //il faut empêcher tout débordement de la map
  float x_player=x;
  float y_player=y;
  if(y_player>=nbSpriteY/2) y_player = nbSpriteY/2;
  if(x_player>=nbSpriteX/2) x_player = nbSpriteX/2;

  if(y-nbSpriteY/2<0) y=nbSpriteY/2;
  if(x-nbSpriteX/2<0) x=nbSpriteX/2;
  if(y+nbSpriteY/2+2>999) y=999-(nbSpriteY/2+2);
  if(x+nbSpriteX/2+2>999) x=999-(nbSpriteX/2+2);

  //puis afficher la portion de la map ou le joueur est présent
  for(int i=y-nbSpriteY/2; i<y+(nbSpriteY/2)+2;i++){
    for(int j=x-nbSpriteX/2; j<x+(nbSpriteX/2)+2; j++){
        float x2 = j-(x-nbSpriteX/2);
        float y2 = i-(y-nbSpriteY/2);
      //chaque nombre dans la matrice corresponds à une sprite
      char sprite1[40] = ""; //on définit le nom du sprite de couche inférieure
      char sprite2[40] = ""; //et celui de couche supérieure
      switch(map[i][j]){
        //avant d'afficher le joueur, on gère tout ce qui passe sous ses pieds
        case 5: sprintf(sprite1, "map_grass"); break;
        case 1: sprintf(sprite1, "map_grass");
                sprintf(sprite2, "map_tree1"); break;
        case 3: sprintf(sprite1, "map_grass");
                sprintf(sprite2, "map_tree2"); break;
        case 6: sprintf(sprite1, "map_grass");
                sprintf(sprite2, "map_house"); break;
        case 2: sprintf(sprite1, "map_water");
                sprintf(sprite2, "map_grass_water"); break;
        //gestion des routes et virages
        case 4: sprintf(sprite1, "map_path.png");
                char path = 'x';
                if(map[i-1][j] == 4 && map[i+1][j]==4 && map[i][j+1]==4 && map[i][j-1]==4) break;
                  path = ' ';
                if(map[i-1][j] == 4 && map[i+1][j]==4 && map[i][j+1]==4){
                  path = '6';
                }else if(map[i-1][j] == 4 && map[i+1][j]==4 && map[i][j-1]==4){
                  path = '4';
                }else if(map[i][j-1] == 4 && map[i][j+1]==4 && map[i-1][j]==4){
                  path = '5';
                }else if(map[i][j-1] == 4 && map[i][j+1] ==4 && map[i+1][j]==4){
                  path = '3';
                }else if(map[i][j+1] == 4 && map[i+1][j]==4){
                  path = '7';
                }else if(map[i][j-1] == 4 && map[i-1][j]==4){
                  path = '9';
                }else if(map[i-1][j] == 4 && map[i][j+1]==4){
                  path = '0';
                }else if(map[i][j-1] == 4 && map[i+1][j]==4){
                  path = '8';
                }else if(map[i][j-1] == 4 || map[i][j+1]==4){
                  path = '2';
                }else if(map[i-1][j] == 4 || map[i+1][j]==4){
                  path = '1';
                }
                if(path != ' ' && path != '0') sprintf(sprite2, "map_grass_path%c", path);
                if(path == '0'){
                   sprintf(sprite2, "map_grass_path10");
                }
                break;
      }
      //on gère les biomes
      if(!est_dans_village(j, i)){
        if(est_dans__biome_neige(j,i)){
            if(strcmp(sprite1, "map_path.png") !=0) strcat(sprite1, "_snow");
           if(sprite2[0]) strcat(sprite2, "_snow");
        }
        else if(est_dans__biome_feu(j,i)){
           if(strcmp(sprite1, "map_path.png") !=0) strcat(sprite1, "_fire");
           if(sprite2[0]) strcat(sprite2, "_fire");
        }
      }

      //on affiche les sprites
      drawImage( x2*getSpriteW(), y2*getSpriteW(), sprite1, getSpriteW(), getSpriteW());
      if(sprite2[0]){
        //on affiche le deuxieme sprite si il existe
        drawImage( x2*getSpriteW(), y2*getSpriteW(), sprite2, getSpriteW(), getSpriteW());
      }
    }
  }
  //puis on affiche le joueur si il est aux mêmes coordonnée
  drawImage( (x_player*getSpriteW()+(x-(int)x))-30, (y_player*getSpriteW()+(y-(int)y))-30, sprite, 60,60);

}


/**
 * \fn void afficher_menu_perso(char*name, char*class_char, char*gender)
 * \brief Gère l'affichage du menu de création de personnage
 * \param[in] nom du perso
 * \param[in] classe du perso
 * \param[in] genre du perso
 */
void afficher_menu_perso(char*name, char*class_char, char*gender){
	fond_blanc();
  fond_blanc();
	for(int i=100; i<=550; i+=150){
		drawImage( 700, i, "button.png", 130, 100);
	}

	drawText( 725, 125, "Warrior", 25, 12);
	drawText( 725, 275, "Wizard", 25, 12);
	drawText( 725, 425, "Hunter", 25, 12);
	drawText( 725, 575, "Priest", 25, 12);
	drawText( 500, 650, "Appuyez su entrée pour continuer", 25, 12);
	drawImage( 300, 550, "button.png", 130, 100);
	drawImage( 500, 550, "button.png", 130, 100);

	drawText( 325, 575, "Male", 25, 12);
	drawText( 525, 575, "Female", 25, 12);
	char perso[30];
	//on définit le nom de l'image du perso en fonction de ses caractéristiques
	sprintf(perso, "%s_%s_back", class_char, gender);
	drawImage( 350, 125, perso, 200, 200);
	drawText( 375, 375, "Name :", 25, 12);
	drawText( 450, 375, name, 25, 12);
	faire_rendu();
}

/**
 * \fn void afficher_menu_perso(char*name, char*class_char, char*gender)
 * \brief Gère les interractions avec le menu de création de personnage
 * \param[in] nom du perso
 * \param[in] classe du perso
 * \param[in] genre du perso
 */
void afficher_creation(char*name, char*class_char, char*gender){
  fond_blanc();
  printf("start affichage creation\n");
  int running;
  printf("start text input\n");
  SDL_StartTextInput();
  printf("end text input\n");
  running = 1;
  char in[50]="";
  printf("affichage menu perso\n");
  afficher_menu_perso(name, class_char, gender);
  printf("fin affichage menu perso\n");
  while ( running ==1 ) {
    SDL_Event ev;
    while ( SDL_PollEvent( &ev ) ) {
      if ( ev.type == SDL_TEXTINPUT  ) {
        strcat(in, ev.text.text);
        strcpy(name, in);
        afficher_menu_perso(name, class_char, gender);
      } else if ( ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && strlen(in)) {
        in[strlen(in)-1]='\0';
        strcpy(name, in);
        afficher_menu_perso(name, class_char, gender);
      } else if ( ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE ) {
        running = 2;
      } else if ( ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_RETURN ) {
        running = 3;
      }
      if(ev.type== SDL_MOUSEBUTTONDOWN)
      {
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        //si on est dans la largeur du menu
        if(mouse_x>700 && mouse_x<830){
          //si on est à la hauteur d'une case du sélecteur
            int pos = mouse_y-100;
            int i=1;
            for(int j=0; j<pos+150 ;i++, j+=150){
              if(pos >= j && pos <= j+150) break;
            }
            switch(i){
              case 1:
                strcpy(class_char, "warrior");
                afficher_menu_perso(name, class_char, gender);
                break;
              case 2:
                strcpy(class_char, "wizard");
                afficher_menu_perso(name, class_char, gender);
                break;
              case 3:
                strcpy(class_char, "hunter");
                afficher_menu_perso(name, class_char, gender);
                break;
              case 4:
                strcpy(class_char, "priest");
                afficher_menu_perso(name, class_char, gender);
                break;
            }
        }
        if(mouse_x>300 && mouse_x<430 && mouse_y>550 && mouse_y<650){
            strcpy(gender, "man");
            afficher_menu_perso(name, class_char, gender);
        }
        if(mouse_x>500 && mouse_x<630 && mouse_y>550 && mouse_y<650){
            strcpy(gender, "woman");
            afficher_menu_perso(name, class_char, gender);
        }

      }
    }
    SDL_Delay(20);
  }
  SDL_StopTextInput();
}

/**
 * \fn int afficher_menu(char menu[4][30])
 * \brief Gère l'affichage du menu pricipal
 * \param[in] tableau de chaines de caractères qui seront affichées sur les boutons du menu
 * \return l'action choisie par le joueur dans le menu
 */
int afficher_menu(char menu[4][30]){
  fond_blanc();
  for(int i = 0, y=100; i<4; i++, y+=150){
    drawImage( 500, y, "button.png", 475, 130);
    drawText(525, y+25, menu[i], 25, 12);
  }
  faire_rendu();
  SDL_Event e;
  int running = -1;
  while(running==-1) {
      if (SDL_WaitEvent(&e) != 0) {
        switch(e.type) {
          case SDL_QUIT: running = 0;
          break;
          case SDL_MOUSEBUTTONDOWN:
          {
            int mouse_x, mouse_y;
            SDL_GetMouseState(&mouse_x, &mouse_y);
            //si on est dans la largeur du menu
            if(mouse_x>500 && mouse_x<975){
              //si on est à la hauteur d'une case du sélecteur
                int pos = mouse_y-100;
                int i=1;
                for(int j=0; j<pos+150 ;i++, j+=150){
                  if(pos >= j && pos <= j+150) break;
                }
                switch(i){
                  case 1: running = 0; break; //nouvelle partie
                  case 2: break; //charger partie
                  case 3: running = 2; break; //editeur carte
                  case 4: running=3; break; //quitter jeu
                }
              }

            }
          break;
      }
    }
    //SDL_Delay(80);
  }
  return running;
}

/**
 * \fn void afficher_quete(float x, float y, char * phrase, char*image, char etat)
 * \brief Gère l'affichage des quêtes
 * \param[in] abscisse de l'objet à afficher
 * \param[in] ordonnée de l'objet à afficher
 * \param[in] phrase de début/fin de quête à afficher si besoin
 * \param[in] nom de l'image ou du pnj à afficher
 * \param[in] etat de la quête (D = début (on affiche la phrase de début), F = fin, P = pnj (pour afficher le pnj) B = but (on vois l'objectif))
 */
void afficher_quete(float x, float y, char * phrase, char*image, char etat){
  int Tw = 9;
  int long_message;
  int char_par_ligne = 90;
  int num_lignes;
  int pixels_bulle;
  char nom[30];
  switch(etat){
    case 'P':
      drawImage( x, y, image, 60, 60);
      break;
    case 'F':
      long_message = strlen(phrase);
      //le numéro de lignes est égal à la taille du texte divisé, + 1 ligne pour le nom du pnj
      num_lignes = (long_message/char_par_ligne)+2;

      //si le messae est petit, la bulle fait la longueur du message
      if(num_lignes == 2){
        pixels_bulle = long_message*Tw;
        drawImage( x-pixels_bulle/4, y-110, "bulle.png", pixels_bulle+40, 120);
        drawText(x-pixels_bulle/4+20, y-70, phrase, 25, Tw);
      }else{ //sinon elle fait la longueur d'une ligne, et on affiche le texte ligne par ligne
        pixels_bulle = 90*Tw;
        drawImage( x-pixels_bulle/4, y-(60*num_lignes-10), "bulle.png", char_par_ligne*Tw+40, 60*num_lignes);
        for(int j = 0, i = 1; i<num_lignes; i++){
          char ligne[91];
          int k;
          for(k=0; j<i*90 && j<long_message; j++, k++){
            ligne[k] = phrase[j];
            ligne[k+1] = '\0';
          }
          int pixel_y = y-(25*(num_lignes-i))-25*num_lignes;
          drawText(x-pixels_bulle/4+20, pixel_y, ligne, 25, Tw);
        }
      }
      sprintf(nom, "%s", image);
      strcat(nom, " :");
      drawText(x-pixels_bulle/4+20, y-60*num_lignes+30, nom, 25, Tw);
      break;
    case 'D':
      long_message = strlen(phrase);
      //le numéro de lignes est égal à la taille du texte divisé, + 1 ligne pour le nom du pnj
      num_lignes = (long_message/char_par_ligne)+2;

      //si le messae est petit, la bulle fait la longueur du message
      if(num_lignes == 2){
        pixels_bulle = long_message*Tw;
        drawImage( x-pixels_bulle/4, y-110, "bulle.png", pixels_bulle+40, 120);
        drawText(x-pixels_bulle/4+20, y-70, phrase, 25, Tw);
      }else{ //sinon elle fait la longueur d'une ligne, et on affiche le texte ligne par ligne
        pixels_bulle = 90*Tw;
        drawImage( x-pixels_bulle/4, y-(60*num_lignes-10), "bulle.png", char_par_ligne*Tw+40, 60*num_lignes);
        for(int j = 0, i = 1; i<num_lignes; i++){
          char ligne[91];
          int k;
          for(k=0; j<i*90 && j<long_message; j++, k++){
            ligne[k] = phrase[j];
            ligne[k+1] = '\0';
          }
          int pixel_y = y-(25*(num_lignes-i))-25*num_lignes;
          drawText(x-pixels_bulle/4+20, pixel_y, ligne, 25, Tw);
        }
      }
      sprintf(nom, "%s", image);
      strcat(nom, " :");
      drawText(x-pixels_bulle/4+20, y-60*num_lignes+30, nom, 25, Tw);
      break;
    case 'B':
      drawImage( x, y, image, 60, 60);
      break;

  }
}

/**
 * \fn int detecter_mouvement(float * x, float * y)
 * \brief Gère le mouvement du personnage
 * \param[in] abscisse du perso
 * \param[in] ordonnée du perso
 * \return 1 si le personnage a bougé, 0 sinon
 */
int detecter_mouvement(float * x, float * y){
  int ** map = getMap(); 
  //l'état du clavier à l'instant actuel
  const Uint8 *state = SDL_GetKeyboardState(NULL); //en sdl
  //si c'est une touche de mouvement
  if(state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN]){
    //on gère les colisions et la vitesse du perso
    //on a besoin de regarder à quel endroit de la map on est et ce qu'il *y a après
    //on fait cohabiter le sdl et le terminal pour un code le plus optimisé possible
    if (state[SDL_SCANCODE_RIGHT] && (map[(int)(floor(*y))][(int)(floor(*x+getVitessePerso()))]==4 || map[(int)(floor(*y))][(int)(floor(*x+getVitessePerso()))]==5)) *x+=getVitessePerso();
    else if (state[SDL_SCANCODE_LEFT] && (map[(int)(floor(*y))][(int)(floor(*x-getVitessePerso()))]==4 || map[(int)(floor(*y))][(int)(floor(*x-getVitessePerso()))]==5)) *x-=getVitessePerso();
    if (state[SDL_SCANCODE_UP] && (map[(int)(floor(*y-getVitessePerso()))][(int)(floor(*x))]==4 || map[(int)(floor(*y-getVitessePerso()))][(int)(floor(*x))]==5)) *y-=getVitessePerso();
    else if (state[SDL_SCANCODE_DOWN] && (map[(int)(floor(*y+getVitessePerso()))][(int)(floor(*x))]==4 || map[(int)(floor(*y+getVitessePerso()))][(int)(floor(*x))]==5)) *y+=getVitessePerso();
    if(*x<0) *x=0;
    if(*y<0) *y=0;
    if(*x>999) *x=999;
    if(*y>999) *y=999;
    return 1;
  }
  return 0;
}

/**
 * \fn void detecter_touches(int * running)
 * \brief Gère les touche échap pour le menu et i pour l'inventaire
 * \param[in] l'état du jeu à modifier si le joueur appuis sur échap
 */
void detecter_touches(int * running){
  SDL_Event e;
  while(SDL_PollEvent(&e)) {
    switch(e.type) {
      //la gestion du clavier hors déplacements se fait ici
      case SDL_KEYDOWN:
      {
        const Uint8 *state = SDL_GetKeyboardState(NULL); //en sdl
        //si c'est la touche d'inventaire
        if(state[SDL_SCANCODE_I]){
          showInventory();
        }
        else if(state[SDL_SCANCODE_ESCAPE]){
          *running = 0;
        }
        break;
      }
      case SDL_MOUSEBUTTONDOWN:
      //quand on clique, si on clique au dessus du sélecteur, on va placer une case.
      //Sinon, on regarde si on a cliqué dans une case du sélecteur.
      {
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        break;
      }
    }
  }
  SDL_Delay(5);
}

/**
 * \fn void gestion_editeur(float * x, float * y, int* selected, int *running)
 * \brief Gère l'éditeur de map
 * \param[in] abscisse du joueur
 * \param[in] ordonnée du joueur
 * \param[in] sprite sélectionné
 * \param[in] état de l'éditeur à changer si le joueur appuis sur échap
 */
void gestion_editeur(float * x, float * y, int* selected, int *running){
  int ** map = getMap(); 
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  //si c'est une touche de mouvement
  if(state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN]){
    //on gère les colisions et la vitesse du perso
    //on a besoin de regarder à quel endroit de la map on est et ce qu'il y a après
    if (state[SDL_SCANCODE_RIGHT] ) *x+=getVitessePerso();
    else if (state[SDL_SCANCODE_UP] ) *y-=getVitessePerso();
    else if (state[SDL_SCANCODE_DOWN] )*y+=getVitessePerso();
    else if (state[SDL_SCANCODE_LEFT]) *x-=getVitessePerso();
    if(*x<0) *x=0;
    if(*y<0) *y=0;
    if(*x>1000) *x=999;
    if(*y>1000) *y=999;
    afficher_selecteur(*x, *y);

  }

  SDL_Event e;
  while(SDL_PollEvent(&e)) {
    switch(e.type) {
      //la gestion du clavier hors déplacements se fait ici
      case SDL_MOUSEBUTTONDOWN:
      //quand on clique, si on clique au dessus du sélecteur, on va placer une case.
      //Sinon, on regarde si on a cliqué dans une case du sélecteur.
      {
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        //si on est dans le sélecteur
        if(mouse_y>getScreenHeight()-150){
          printf("%d, %d\n", mouse_x, mouse_y);
          //si on est à la hauteur d'une case du sélecteur
          if(mouse_y>getScreenHeight()-100 && mouse_y<getScreenHeight()){
            //la position de x sur l'image
            int pos = mouse_x-((getScreenWidth()-1200)/2+245);
            for(int j=0,i = 1; j<pos+85 ;i++, j+=100){
              if(pos >= j && pos <= j+85){
                //i corresponds au numéro de la case du sprite sélectionné,
                //et aussi au numéro du sprite dans la matrice de la map,
                //et ça c'est pratique
                printf("%d\n", i);
                if(i==8){
                  remove("Map.txt");
                  FILE *map_file = fopen("Map.txt", "w");
                  for(int i=0; i<1000; i++){
                    for(int j=0; j<1000; j++){
                      fprintf(map_file, "%d;", map[i][j]);
                    }
                    fprintf(map_file, "\n");
                  }

                  fclose(map_file);
                }
                if(i==9){
                  *running=0;
                  break;
                }
                *selected = i;
              }
            }
          }
        }
        //sinon on détecte la bonne position du sprite pour l'afficher sur l'écran, et on l'enregistre
        else{
          int h=*y-getScreenHeight()/125/2;
          for(int j=0; j+125<mouse_y;j+=125, h++);
          int w=*x-getScreenWidth()/125/2;
          for(int j=0; j+125<mouse_x;j+=125, w++);

          //une fois qu'on a trouvé les bonnes coordonées on modifie la map pour l'afficher en direct
          map[h][w]= *selected;
          afficher_selecteur(*x, *y);
        }
      break;
    }
    }
  }
  SDL_Delay(5);
}
