/**
 * \file fonctions_sdl.c
 * \brief Fonctions de gestion SDL
 * \author Girod Valentin
 * \date mars 2019
 *
 * Contient les fonctions d'affichage et de gestion de fenêtres SDL, ainsi que le chargement/déchargement des images
 *
 */
#include <dirent.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <fonctions_affichage.h>

SDL_Renderer*renderer; /*!< Pointeur sur l'état du rendu */

int nb_images=0; /*!< Nombre d'images du jeu */
//police de caractères
TTF_Font *police;
//couleur principale du jeu
SDL_Color couleurDoree = {204, 154, 0};

//initialisation des images -> on les charge une seule fois pour économiser la ram
SDL_Texture * images[200]; /*!< Tableau de texturess des images. Comme on ne peut pas faire de sizeof(sdl_texture) on met une taille suposée assez grande */
char ** noms; /*!< Tableau des noms d'images */

/**
 * \fn void loadImages()
 * \brief Chargement de toutes les textures du jeu dans la mémoire
 */
void loadImages(){
	printf("Chargement des images...\n");
	DIR *d;
	struct dirent *dir;

	d = opendir("./IMG/");
	while ((dir = readdir(d)) != NULL) nb_images++;
	closedir(d);

	noms = malloc(sizeof(char*)*nb_images);

	d = opendir("./IMG/");
	for (int i=0;(dir = readdir(d)) != NULL; i++){
		noms[i] = malloc(sizeof(char)*strlen(dir->d_name)+1);
		strcpy(noms[i], dir->d_name);
	}
	closedir(d);
	for(int i=0; i<nb_images; i++){
		char nom[50] = "./IMG/";
		strcat(nom, noms[i]);
		images[i] = IMG_LoadTexture(renderer, nom);
		if(i==22){
			printf("%s\n", nom);
		}
	}
	printf("Images chargées: %d\n", nb_images);
}

/**
 * \fn void setcolor()
 * \brief Fonction seulement utile en terminal, mais doit être définie également ici pour permettre la compilation
 */
void setcolor(int fg, int bg);

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
 * \fn void faire_rendu()
 * \brief met l'écran à jour
 */
void faire_rendu(){
	SDL_RenderPresent(renderer);
}

/**
 * \fn void fond_blanc()
 * \brief Met le fond de la fenêtre en blanc
 */
void fond_blanc(){
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	faire_rendu();
}

/**
 * \fn void quitter_affichage()
 * \brief Quitte totallement la SDL
 */
void quitter_affichage(){
	unloadImages();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(fenetre);
	TTF_CloseFont(police);
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
 * \fn void init_affichage()
 * \brief Affiche la fenêtre du jeu en fonction de la taille de l'écran, création du renderer; les dimensions de l'écran, le renderer et la fenêtre sont des variables globales
 */
void init_affichage(){

		/* Initialisation simple */
	SDL_Init(SDL_INIT_VIDEO);
	/* Initialisation TTF */
	TTF_Init();
	//adaptation de la fenêtre par raport à la taille de l'écran. On en profite pour rendre disponible ces valeurs et
	//mieux adapter chaque élément de l'affichage dans les autres fonctions
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	police = TTF_OpenFont("editundo.ttf", 25);
	SCREEN_HEIGHT = dm.h;
	SCREEN_WIDTH = dm.w;
	/* Création de la fenêtre */
	fenetre = SDL_CreateWindow("Final Fantasy: the great shity C project, but not so shity finally",SDL_WINDOWPOS_UNDEFINED,
													SDL_WINDOWPOS_UNDEFINED,
													SCREEN_WIDTH,
													SCREEN_HEIGHT,
													SDL_WINDOW_SHOWN);

	renderer=SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetWindowFullscreen(fenetre, SDL_WINDOW_FULLSCREEN);
	loadImages();
	SPRITE_W = 125;
	VITESSE_PERSO = 0.03; //on est en sdl, le perso sera plus lent qu'en terminal
}
