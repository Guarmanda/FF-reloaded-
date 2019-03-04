#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include "fonctions_sdl.h"





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
	SDL_QueryTexture(texte_tex, NULL, NULL, &(txtDestRect.w), &(txtDestRect.h));
	SDL_RenderCopy(renderer, texte_tex, NULL, &txtDestRect);
}

void drawImage (SDL_Renderer * renderer, int x, int y, char * string){
	// x et y les coordonnées,
	SDL_Rect imgDestRect;

	imgDestRect.x = x;
	imgDestRect.y = y;
	//l'optimisation de l'affichage de l'image a ses défauts:
	//on est obligé de dire quelle largeur/hauteur fera l'image.
	//Mais cette version est bien plus optimisée que celle en exemple sur umtice,
	//et ne fait pas planter la sdl au bout de 7 affichages de la map
	//alors le choix est vite fait
	if(strstr(string, "map")){
		imgDestRect.w = 125;
		imgDestRect.h = 125;
	}
	if(strstr(string, "selector")){
		imgDestRect.w = 1200;
		imgDestRect.h = 150;
	}
	if(strstr(string, "button")){
		imgDestRect.w = 475;
		imgDestRect.h = 130;
	}
	if(strstr(string, "player")){
		imgDestRect.w = 60;
		imgDestRect.h = 60;
	}
	SDL_Texture *image_tex = IMG_LoadTexture(renderer, string);
	SDL_RenderCopy(renderer, image_tex, NULL, &imgDestRect);
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
