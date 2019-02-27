#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>





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
	SDL_RWops *rwop=SDL_RWFromFile(string, "rb");
	SDL_Rect imgDestRect;
	imgDestRect.x = x;
	imgDestRect.y = y;
	SDL_Surface*image=IMG_LoadPNG_RW(rwop);
	SDL_Texture *image_tex = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image); /* on a la texture, plus besoin de l'image */
	SDL_QueryTexture(image_tex, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
	SDL_RenderCopy(renderer, image_tex, NULL, &imgDestRect);
}



SDL_Window* showWindow(){

		/* Initialisation simple */
	SDL_Init(SDL_INIT_VIDEO);
	/* Initialisation TTF */
	TTF_Init();
	/* Création de la fenêtre */
	return SDL_CreateWindow("Final Fantasy: the great shity C project",SDL_WINDOWPOS_UNDEFINED,
													SDL_WINDOWPOS_UNDEFINED,
													1680,
													1050,
													SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
}
