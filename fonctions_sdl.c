#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "fonctions_sdl.h"



int nb_images=81;


//initialisation des images -> on les charge une seule fois pour économiser la ram
SDL_Texture * images[81];
char noms[81][50]= {
//map et menu principal
"button.png", "item_selector.png", "map_grass.png", "map_grass_path1.png", "map_grass_path2.png", "map_grass_path3.png", "map_grass_path4.png",
"map_grass_path5.png", "map_grass_path6.png", "map_grass_path7.png", "map_grass_path8.png", "map_grass_path9.png", "map_grass_path10.png", "map_grass_water.png",
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
};

void loadImages(SDL_Renderer * renderer){
	for(int i=0; i<nb_images; i++){
		char nom[50] = "./IMG/";
		strcat(nom, noms[i]);
		images[i] = IMG_LoadTexture(renderer, nom);
	}
}

void unloadImages(){
	for(int i=0; i<nb_images; i++){
		SDL_DestroyTexture(images[i]);
	}
}


void drawText (SDL_Renderer * renderer, int x, int y, char * string, int h, int w){
	TTF_Font *police = TTF_OpenFont("editundo.ttf", 20);
	SDL_Color couleurDoree = {204, 154, 0};
	SDL_Surface *texte = TTF_RenderUTF8_Blended(police, string, couleurDoree);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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

void drawImage (SDL_Renderer * renderer, int x, int y, char * nom, int w, int h){
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


SDL_Window* showWindow(){

		/* Initialisation simple */
	SDL_Init(SDL_INIT_VIDEO);
	/* Initialisation TTF */
	TTF_Init();
	//adaptation de la fenêtre par raport à la taille de l'écran. On en profite pour rendre disponible ces valeurs et
	//mieux adapter chaque élément de l'affichage dans les autres fonctions
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	SCREEN_HEIGHT = dm.h;
	SCREEN_WIDTH = dm.w;
	/* Création de la fenêtre */
	return SDL_CreateWindow("Final Fantasy: the great shity C project",SDL_WINDOWPOS_UNDEFINED,
													SDL_WINDOWPOS_UNDEFINED,
													SCREEN_WIDTH,
													SCREEN_HEIGHT,
													SDL_WINDOW_SHOWN);
}
