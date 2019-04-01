#include <affichage.h>
#include <map.h>
#include <quete.h>
#include <fonctions_affichage.h>
#include <SDL2/SDL.h>
#include <perso.h>
#include <creationPerso.h>
/**
 * \fn void showInventory()
 * \brief Affichage de l'inventaire du joueur
 */
void showInventory(){
  //la longueur des barres de vie/mana/xp est de 8.54% de l'image, suivie d'une autre barre de 8.54% de l'image d'une autre couleur pour la barre vide
  //Il faut (pour l'instant) 100xp par niveau, 100hp en tout,
  //8.54%/100 = le nombre de pixels pour 1xp
  //nouvelle taille en pixels de l'image: (SCREEN_HEIGHT/100)*90
  //8.54% de cette taille = nb de pixels qu'il faut

  float pixels = ((SCREEN_WIDTH/100)*95/100*8.54);
  //calcul du nombre d'xp du niveau actuel:
  //int actual_xp = 100-PLAYER->level*100-PLAYER->xp;
  int actual_xp=PLAYER->xp;

  //le calcul du nombre de pixels pour afficher le texte suis la même logique que les pixels

  //variables de taille du texte et chaine de charactère pour afficher les nombres
  char num[3];
  int textH = 55;
  int textW = 35;

  //affichage du level
  float PxTextXlevel = ((SCREEN_WIDTH/100)*47);
  float PxTextYlevel = ((SCREEN_WIDTH/100)*2.8);
  sprintf(num,"%d",PLAYER->level);
  drawText( PxTextXlevel, PxTextYlevel, num, textH, textW);


  float PxTextXActuel = ((SCREEN_WIDTH/100)*35.1); //X ne change pas pour les 3 premier nombres
  float PxTextYVie = ((SCREEN_WIDTH/100)*7.2);
  float PxTextYXP = ((SCREEN_WIDTH/100)*11.2);
  float PxTextYMana = ((SCREEN_WIDTH/100)*15.2);

  //affichage des barres
  int W = SCREEN_WIDTH-5*SCREEN_WIDTH/100;
  int H = SCREEN_HEIGHT-5*SCREEN_HEIGHT/100;
  drawImage( (PLAYER->health*pixels/100)-pixels+2.5*SCREEN_WIDTH/100, 0, "life_bar.png", W, H);
  drawImage( actual_xp*pixels/100-pixels+2.5*SCREEN_WIDTH/100, 0, "xp_bar.png", W, H);
  drawImage( PLAYER->mana*pixels/100-pixels+2.5*SCREEN_WIDTH/100, 0, "mana_bar.png", W, H);
  drawImage( 2.5*SCREEN_WIDTH/100, 0, "inventory.png", W, H);
  //affichage des valeurs des barres
  sprintf(num,"%d",PLAYER->health);
  drawText( PxTextXActuel, PxTextYVie, num, textH, textW);
  sprintf(num,"%d",actual_xp);
  drawText( PxTextXActuel, PxTextYXP, num, textH, textW);
  sprintf(num,"%d",PLAYER->mana);
  drawText( PxTextXActuel, PxTextYMana, num, textH, textW);

  PxTextXActuel = ((SCREEN_WIDTH/100)*47); //on redéfinit X pour les 3 autres nombres, y ne change pas

  //affichage des valeurs max des barres
  drawText( PxTextXActuel, PxTextYVie, "100", textH, textW);
  drawText( PxTextXActuel, PxTextYXP, "100", textH, textW);
  drawText( PxTextXActuel, PxTextYMana, "100", textH, textW);

  //affichage des items équipés
  //Les images des items ont les mêmes noms que les items eux-même, cela facilite leur affichage graçe à la fonction
  //display_object dans perso.c
  drawImage( (SCREEN_WIDTH/100)*75.75, (SCREEN_HEIGHT/100)*37, display_object(PLAYER->char_armor), 110, 110);
  drawImage( (SCREEN_WIDTH/100)*60.75, (SCREEN_HEIGHT/100)*37, display_object(PLAYER->char_weapon), 110, 110);

  //affichage de l'accessoire
  char accessory[20];
  if(PLAYER->accessory==green_amulet) sprintf(accessory, "%s", "green amulet");
  if(PLAYER->accessory==ruby_ring) sprintf(accessory, "%s", "ruby ring");
  if(PLAYER->accessory==crystal_ring) sprintf(accessory, "%s", "crystal ring");
  drawImage( (SCREEN_WIDTH/100)*60.75, (SCREEN_HEIGHT/100)*9, accessory, 110, 110);

  faire_rendu();

  int running = 1;
  int selected = 1;
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
          //si on est dans le sélecteur

        break;
      }
      }
    }
  }
  afficher_Map( X, Y);
  faire_rendu();

}

void afficher_selecteur(int x, int y){
  int x_select = (SCREEN_WIDTH-1200)/2;
  afficher_Map( x, y);
  drawImage( x_select, SCREEN_HEIGHT-250, "item_selector.png", 1200, 150);
  faire_rendu();
}

/**
 * \fn void showMap(float x, float y)
 * \brief Gère l'affichage de la map et du joueur en SDL
 * \param[in] Abscisse du joueur
 * \param[in] Ordonnée du joueur
 */
void afficher_Map(float x, float y){
  //le nombre de sprites à afficher, tout comme la position du joueur, dépend de la taille de l'écran
  float nbSpriteX = SCREEN_WIDTH/SPRITE_W;
  float nbSpriteY = SCREEN_HEIGHT/SPRITE_W;

  //on veux savoir quelle sprite de joueur afficher
  char sprite[30] = "";
	strcat(sprite, PLAYER->class_char);
	strcat(sprite, "_");
	strcat(sprite, PLAYER->gender);
	strcat(sprite, "_");
  if (X>x) strcat(sprite, "left");
  else if (X<x) strcat(sprite, "right");
  else if (Y>y) strcat(sprite, "forward");
  else if (Y<y) strcat(sprite, "back");
  else strcat(sprite, "back");

  //on rend accessible les nouvelles coordonnées du joueur pour les monstres/quetes
  X=x;
  Y=y;
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
        case 5: sprintf(sprite1, "map_grass.png"); break;
        case 1: sprintf(sprite1, "map_grass.png");
                sprintf(sprite2, "map_tree1.png"); break;
        case 3: sprintf(sprite1, "map_grass.png");
                sprintf(sprite2, "map_tree2.png"); break;
        case 6: sprintf(sprite1, "map_grass.png");
                sprintf(sprite2, "map_house.png"); break;
        case 2: sprintf(sprite1, "map_water.png");
                sprintf(sprite2, "map_grass_water.png"); break;
        //gestion des routes et virages
        case 4: sprintf(sprite1, "map_path.png");
                if(map[i-1][j] == 4 && map[i+1][j]==4 && map[i][j+1]==4 && map[i][j-1]==4) break;
                char path = ' ';
                if(map[i-1][j] == 4 && map[i+1][j]==4 && map[i][j+1]==4){
                  path = '6';
                }else if(map[i-1][j] == 4 && map[i+1][j]==4 && map[i][j-1]==4){
                  path = '4';
                }else if(map[i][j-1] == 4 && map[i][j+1]==4 && map[i-1][j]==4){
                  path = '5';
                }else if(map[i][j-1] == 4 && map[i][j+1] ==4 && map[i+1][j]==4){
                  path = '3';
                }else if(map[i][j-1] == 4 && map[i][j+1]==4){
                  path = '2';
                }else if(map[i-1][j] == 4 && map[i+1][j]==4){
                  path = '1';
                }else if(map[i][j+1] == 4 && map[i+1][j]==4){
                  path = '7';
                }else if(map[i][j-1] == 4 && map[i-1][j]==4){
                  path = '9';
                }else if(map[i-1][j] == 4 && map[i][j+1]==4){
                  path = '0';
                }else if(map[i][j-1] == 4 && map[i+1][j]==4){
                  path = '8';
                }
                if(path != ' '){
                  sprintf(sprite2, "map_grass_path%c", path);
                }
                break;
      }
      //on affiche les sprites
      drawImage( x2*SPRITE_W, y2*SPRITE_W, sprite1, SPRITE_W, SPRITE_W);
      if(sprite2[0]){
        //on affiche le deuxieme sprite si il existe
        drawImage( x2*SPRITE_W, y2*SPRITE_W, sprite2, SPRITE_W, SPRITE_W);
      }
    }
  }
  //puis on affiche le joueur si il est aux mêmes coordonnée
  drawImage( (x_player*SPRITE_W+(x-(int)x))-30, (y_player*SPRITE_W+(y-(int)y))-30, sprite, 60,60);

}


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
 * \fn void afficher_menu_perso()
 * \brief Fonction d'affichage du menu d'édition de personnage
 */
void afficher_menu_perso(char*name, char*class_char, char*gender){
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

void afficher_creation(char*name, char*class_char, char*gender){
  int running;
  SDL_StartTextInput();
  running = 1;
  char in[50]="";
  afficher_menu_perso(name, class_char, gender);
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

void afficher_quete(float x, float y, int id, char etat){
  int Tw = 9;
  int long_message;
  int char_par_ligne = 90;
  int num_lignes;
  int pixels_bulle;
  switch(etat){
    case 'P':
      drawImage( x, y, quetes[id]->pnj_img, 60, 60);
      break;
    case 'F':
      long_message = strlen(quetes[id]->phrase_fin)*Tw;
      //le numéro de lignes est égal à la taille du texte divisé, + 1 ligne pour le nom du pnj
      num_lignes = (long_message/char_par_ligne)+1;
      //si le messae est petit, la bulle fait la longueur du message
      if(num_lignes == 2){
        drawImage( x-long_message/4, y-110, "bulle.png", long_message+40, 120);
        drawText(x-long_message/4+20, y-67, quetes[id]->phrase_fin, 25, Tw);
      }else{ //sinon elle fait la longueur d'une ligne, et on affiche le texte ligne par ligne
        drawImage( x-long_message/4, y-110, "bulle.png", char_par_ligne+40, 120);
        for(int j = 0, i = 1; i<num_lignes; i++){
          char ligne[91];
          int k;
          for(k=0; j<i*90 && j<long_message; j++, k++){
            ligne[k] = quetes[id]->phrase_fin[j];
          }
          ligne[k] = '\0';
          drawText(x-long_message/4+20, y-67, ligne, 25, Tw);
        }
      }
      drawText(x-long_message/4+20, y-100, quetes[id]->pnj_nom, 25, Tw);
      break;
    case 'D':
      long_message = strlen(quetes[id]->phrase_debut);
      //le numéro de lignes est égal à la taille du texte divisé, + 1 ligne pour le nom du pnj
      num_lignes = (long_message/char_par_ligne)+2;

      //si le messae est petit, la bulle fait la longueur du message
      if(num_lignes == 2){
        pixels_bulle = long_message*Tw;
        drawImage( x-pixels_bulle/4, y-110, "bulle.png", pixels_bulle+40, 120);
        drawText(x-pixels_bulle/4+20, y-70, quetes[id]->phrase_debut, 25, Tw);
      }else{ //sinon elle fait la longueur d'une ligne, et on affiche le texte ligne par ligne
        pixels_bulle = 90*Tw;
        drawImage( x-pixels_bulle/4, y-(60*num_lignes-10), "bulle.png", char_par_ligne*Tw+40, 60*num_lignes);
        for(int j = 0, i = 1; i<num_lignes; i++){
          char ligne[91];
          int k;
          for(k=0; j<i*90 && j<long_message; j++, k++){
            ligne[k] = quetes[id]->phrase_debut[j];
            ligne[k+1] = '\0';
          }
          int pixel_y = y-(25*(num_lignes-i))-25*num_lignes;
          drawText(x-pixels_bulle/4+20, pixel_y, ligne, 25, Tw);
        }
      }
      char nom[30];
      sprintf(nom, "%s", quetes[id]->pnj_nom);
      strcat(nom, " :");
      drawText(x-pixels_bulle/4+20, y-(60*num_lignes-10)+30, nom, 25, Tw);
      break;
    case 'B':
      drawImage( x, y, quetes[id]->nom_img, 60, 60);
      break;

  }
}

int detecter_mouvement(float * x, float * y){
  //l'état du clavier à l'instant actuel
  const Uint8 *state = SDL_GetKeyboardState(NULL); //en sdl
  //si c'est une touche de mouvement
  if(state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN]){
    //on gère les colisions et la vitesse du perso
    //on a besoin de regarder à quel endroit de la map on est et ce qu'il *y a après
    //on fait cohabiter le sdl et le terminal pour un code le plus optimisé possible
    if (state[SDL_SCANCODE_RIGHT] && (map[(int)(floor(*y))][(int)(floor(*x+VITESSE_PERSO))]==4 || map[(int)(floor(*y))][(int)(floor(*x+VITESSE_PERSO))]==5)) *x+=VITESSE_PERSO;
    else if (state[SDL_SCANCODE_LEFT] && (map[(int)(floor(*y))][(int)(floor(*x-VITESSE_PERSO))]==4 || map[(int)(floor(*y))][(int)(floor(*x-VITESSE_PERSO))]==5)) *x-=VITESSE_PERSO;
    if (state[SDL_SCANCODE_UP] && (map[(int)(floor(*y-VITESSE_PERSO))][(int)(floor(*x))]==4 || map[(int)(floor(*y-VITESSE_PERSO))][(int)(floor(*x))]==5)) *y-=VITESSE_PERSO;
    else if (state[SDL_SCANCODE_DOWN] && (map[(int)(floor(*y+VITESSE_PERSO))][(int)(floor(*x))]==4 || map[(int)(floor(*y+VITESSE_PERSO))][(int)(floor(*x))]==5)) *y+=VITESSE_PERSO;
    if(*x<0) *x=0;
    if(*y<0) *y=0;
    if(*x>999) *x=999;
    if(*y>999) *y=999;
    return 1;
  }
  return 0;
}

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


void gestion_editeur(float * x, float * y, int* selected, int *running){
  const Uint8 *state = SDL_GetKeyboardState(NULL);

  //si c'est une touche de mouvement
  if(state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_DOWN]){
    //on gère les colisions et la vitesse du perso
    //on a besoin de regarder à quel endroit de la map on est et ce qu'il y a après
    if (state[SDL_SCANCODE_RIGHT] ) *x+=VITESSE_PERSO;
    else if (state[SDL_SCANCODE_UP] ) *y-=VITESSE_PERSO;
    else if (state[SDL_SCANCODE_DOWN] )*y+=VITESSE_PERSO;
    else if (state[SDL_SCANCODE_LEFT]) *x-=VITESSE_PERSO;
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
        if(mouse_y>SCREEN_HEIGHT-215){
          printf("%d, %d\n", mouse_x, mouse_y);
          //si on est à la hauteur d'une case du sélecteur
          if(mouse_y>SCREEN_HEIGHT-200 && mouse_y<SCREEN_HEIGHT){
            //la position de x sur l'image
            int pos = mouse_x-((SCREEN_WIDTH-1200)/2+245);
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
          int h=*y-SCREEN_HEIGHT/125/2;
          for(int j=0; j+125<mouse_y;j+=125, h++);
          int w=*x-SCREEN_WIDTH/125/2;
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
