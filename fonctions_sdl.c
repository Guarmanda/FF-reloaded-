/**
 * \file fonctions_sdl.c
 * \brief Fonctions de gestion SDL
 * \author Karman Nathalie; Papot Alexandre; Girod Valentin
 * \date 12 mars 2019
 *
 * Contient les fonctions d'affichage et de gestion de fenêtres SDL, ainsi que le chargement/déchargement des images
 *
 */
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <fonctions_sdl.h>



int nb_images=83; /*!< Nombre d'images du jeu */
//police de caractères
TTF_Font *police;
//couleur principale du jeu
SDL_Color couleurDoree = {204, 154, 0};

//initialisation des images -> on les charge une seule fois pour économiser la ram
SDL_Texture * images[83]; /*!< Tableau de texturess des images */
char noms[83][50]= {
//map et menu principal
"button.png", "item_selector.png", "map_grass.png", "map_grass_path1.png", "map_grass_path2.png", "map_grass_path3.png", "map_grass_path4.png",
"map_grass_path5.png", "map_grass_path6.png", "map_grass_path7.png", "map_grass_path8.png", "map_grass_path9.png", "map_grass_path0.png", "map_grass_water.png",
"map_house.png", "map_path.png", "map_water.png", "map_tree1.png", "map_tree2.png", "player1.png",
//inventaire
"inventory.png", "life_bar.png", "mana_bar.png", "xp_bar.png",
//armures
"golden armor.png", "cloth armor.png", "leather armor.png", "silver armor.png",
//armes
"dagger.png", "sword.png", "staff.png", "bow.png",
//potions
"mana potion.png", "super mana potion.png", "phoenix potion.png", "super phoenix potion.png", "health potion.png", "super health potion.png", "anti blind potion.png", "anti slow potion.png", "anti bleeding potion.png", "anti poison potion.png", "anti silence potion.png", "anti stunt potion.png", "speed potion.png", "lucidity potion.png",
//accessories
"ruby ring.png", "crystal ring.png", "green amulet.png",
//personnages
"warrior_man_back.png", "warrior_man_right.png", "warrior_man_left.png", "warrior_man_forward.png",
"warrior_woman_back.png", "warrior_woman_right.png", "warrior_woman_left.png", "warrior_woman_forward.png",
"hunter_man_back.png", "hunter_man_right.png", "hunter_man_left.png", "hunter_man_forward.png",
"hunter_woman_back.png", "hunter_woman_right.png", "hunter_woman_left.png", "hunter_woman_forward.png",
"wizard_man_back.png", "wizard_man_right.png", "wizard_man_left.png", "wizard_man_forward.png",
"wizard_woman_back.png", "wizard_woman_right.png", "wizard_woman_left.png", "wizard_woman_forward.png",
"priest_man_back.png", "priest_man_right.png", "priest_man_left.png", "priest_man_forward.png",
"priest_woman_back.png", "priest_woman_right.png", "priest_woman_left.png", "priest_woman_forward.png",
"pnj.png", "bulle.png"
}; /*!< Tableau des noms d'images */

/**
 * \fn void loadImages()
 * \brief Chargement de toutes les textures du jeu dans la mémoire
 */
void loadImages(){
	for(int i=0; i<nb_images; i++){
		char nom[50] = "./IMG/";
		strcat(nom, noms[i]);
		images[i] = IMG_LoadTexture(renderer, nom);
	}
}

/**
 * \fn void unloadImages()
 * \brief Déchargement de toutes les textures du jeu
 */
void unloadImages(){
	for(int i=0; i<nb_images; i++){
		SDL_DestroyTexture(images[i]);
	}
}

/**
 * \fn void fond_blanc()
 * \brief Met le fond de la fenêtre en blanc
 */
void fond_blanc(){
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
}

/**
 * \fn void faire_rendu()
 * \brief met l'écran à jour
 */
void faire_rendu(){
	if(AFFICHAGE){
		SDL_RenderPresent(renderer);
	}
	else{
		refresh();
	}
}

/**
 * \fn void quitter_sdl()
 * \brief QUitte totallement la SDL
 */
void quitter_sdl(){
	unloadImages();
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

/**
 * \fn void drawText(int x, int y, char * string, int h, int w)
 * \brief Affiche du texte d'une certaine taille à des coordonnées données
 * \param[in] Abscisse du texte
 * \param[in] Ordonnée du texte
 * \param[in] Contenu du texte
 * \param[in] Hauteur du texte
 * \param[in] Largeur du texte
 */
void drawText (int x, int y, char * string, int h, int w){
	SDL_Surface *texte = TTF_RenderUTF8_Blended(police, string, couleurDoree);

	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_FreeSurface(texte); /* on a la texture, plus besoin du texte */
	/* Position ou sera mis le texte dans la fenêtre */
	SDL_Rect txtDestRect;
	txtDestRect.x = x;
	txtDestRect.y = y;
	txtDestRect.h = h;
	txtDestRect.w = w*strlen(string);
	SDL_RenderCopy(renderer, texte_tex, NULL, &txtDestRect);
	SDL_DestroyTexture(texte_tex);
}

/**
 * \fn void drawImage(int x, int y, char * nom, int w, int h)
 * \brief Affiche une image d'une certaine taille à des coordonnées données
 * \param[in] Abscisse de l'image
 * \param[in] Ordonnée de l'image
 * \param[in] Nom de l'image
 * \param[in] Hauteur de l'image
 * \param[in] Largeur de l'image
 */
void drawImage (int x, int y, char * nom, int w, int h){
	// x et y les coordonnées,
	SDL_Rect imgDestRect;
	imgDestRect.x = x;
	imgDestRect.y = y;
	imgDestRect.w = w;
	imgDestRect.h = h;
  char nom2[50];
  sprintf(nom2, "%s", nom);
  if(!strstr(nom2, ".png")){
    strcat(nom2, ".png");
  }
	int i;
	//ici on recherche quel est l'indice de l'image qu'on veux afficher
	for(i=0; strcmp(noms[i], nom2)!=0 && i<nb_images; i++);
	//on l'affiche ensuite
	SDL_RenderCopy(renderer, images[i], NULL, &imgDestRect);
	//SDL_DestroyTexture(image_tex);
}

/**
 * \fn void showWindow()
 * \brief Affiche la fenêtre du jeu en fonction de la tailel de l'écran, création du renderer; les dimensions de l'écran, le renderer et la fenêtre sont des variables globales
 */
void showWindow(){

		/* Initialisation simple */
	SDL_Init(SDL_INIT_VIDEO);
	/* Initialisation TTF */
	TTF_Init();
	//adaptation de la fenêtre par raport à la taille de l'écran. On en profite pour rendre disponible ces valeurs et
	//mieux adapter chaque élément de l'affichage dans les autres fonctions
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	police = TTF_OpenFont("editundo.ttf", 20);
	SCREEN_HEIGHT = dm.h;
	SCREEN_WIDTH = dm.w;
	/* Création de la fenêtre */
	pWindow = SDL_CreateWindow("Final Fantasy: the great shity C project, but not so shity finally",SDL_WINDOWPOS_UNDEFINED,
													SDL_WINDOWPOS_UNDEFINED,
													SCREEN_WIDTH,
													SCREEN_HEIGHT,
													SDL_WINDOW_SHOWN);
	renderer=SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
}
