#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "fonctions_sdl.h"


int nb_images=20;

//initialisation des images -> on les charge une seule fois pour économiser la ram
SDL_Texture * images[20];
char noms[20][50]= {"button.png", "item_selector.png", "map_grass.png", "map_grass_path1.png", "map_grass_path2.png", "map_grass_path3.png", "map_grass_path4.png", "map_grass_path5.png", "map_grass_path6.png", "map_grass_path7.png", "map_grass_path8.png", "map_grass_path9.png", "map_grass_path10.png", "map_grass_water.png", "map_house.png", "map_path.png", "map_water.png", "map_tree1.png", "map_tree2.png", "player1.png"};

void loadImages(SDL_Renderer * renderer){
	for(int i=0; i<nb_images; i++){
		char nom[50] = "./IMG/";
		strcat(nom, noms[i]);
		images[i] = IMG_LoadTexture(renderer, nom);
	}
}


void drawText (SDL_Renderer * renderer, int x, int y, char * string){
	TTF_Font *police = TTF_OpenFont("ChowFun.ttf", 20);
	SDL_Color couleurDoree = {204, 154, 0};
	SDL_Surface *texte = TTF_RenderUTF8_Blended(police, string, couleurDoree);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(renderer, texte);
	SDL_FreeSurface(texte); /* on a la texture, plus besoin du texte */
	/* Position ou sera mis le texte dans la fenêtre */
	SDL_Rect txtDestRect;
	txtDestRect.x = x;
	txtDestRect.y = y;
	txtDestRect.h = 25;
	txtDestRect.w = 12*strlen(string);
	SDL_RenderCopy(renderer, texte_tex, NULL, &txtDestRect);
	SDL_DestroyTexture(texte_tex);
}

void drawImage (SDL_Renderer * renderer, int x, int y, char * nom){
	// x et y les coordonnées,
	SDL_Rect imgDestRect;
	imgDestRect.x = x;
	imgDestRect.y = y;
	if(strstr(nom, "map")){
		imgDestRect.w = 125;
		imgDestRect.h = 125;
	}
	if(strstr(nom, "selector")){
		imgDestRect.w = 1200;
		imgDestRect.h = 150;
	}
	if(strstr(nom, "button")){
		imgDestRect.w = 475;
		imgDestRect.h = 130;
	}
	if(strstr(nom, "player")){
		imgDestRect.w = 60;
		imgDestRect.h = 60;
	}
	int i;
	//ici on recherche quel est l'indice de l'image qu'on veux afficher
	for(i=0; strcmp(noms[i], nom)!=0 && i<nb_images; i++);
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
