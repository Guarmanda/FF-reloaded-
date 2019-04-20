include makefile.compilation

all:
	@read -p "sdl ou terminal? " PARAM; \
	make $$PARAM;

SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include
AFF_DIR=./Affichage/
PARAM=${1}
INCLUDE_SDL=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image -I${SDLINC_DIR}
INCLUDE_NCURSES=-lncurses
INCLUDES=-I./ -lm -I${AFF_DIR}

BIN_SDL=fonctions_sdl.o affichages_sdl.o
BIN_TERMINAL=fonctions_terminal.o affichages_terminal.o
#objets indépendants des fichiers d'affichage
OBJ=map.o commun.o inventaire.o perso_commun.o map_menace.o perso_monstre.o perso_joueur.o sauvegarde.o
#objets dépendants des fichiers d'affichage
OBJ_DEP_AFF=combat.o quete.o game.o main.o level_editor.o menu_principal.o



PROG=programme

sdl: clean $(OBJ) $(BIN_SDL) $(OBJ_DEP_AFF)
	$(CCLNK) $(CFLAGS) $(OBJ) ${BIN_SDL} $(OBJ_DEP_AFF) -o ${PROG} ${INCLUDES} ${INCLUDE_SDL}

terminal: clean $(OBJ) $(BIN_TERMINAL) $(OBJ_DEP_AFF)
	$(CCLNK) $(CFLAGS) $(OBJ) ${BIN_TERMINAL} $(OBJ_DEP_AFF) -o ${PROG} ${INCLUDES} ${INCLUDE_NCURSES}


#Affichage
fonctions_sdl.o:
	$(CCOBJ) $(CFLAGS) ${AFF_DIR}fonctions_sdl.c -o fonctions_sdl.o ${INCLUDES} ${INCLUDE_SDL}

fonctions_terminal.o:
	$(CCOBJ) $(CFLAGS) ${AFF_DIR}fonctions_terminal.c -o fonctions_terminal.o ${INCLUDES} ${INCLUDE_NCURSES}

affichages_sdl.o:
	$(CCOBJ) $(CFLAGS) ${AFF_DIR}affichages_sdl.c -o affichages_sdl.o ${INCLUDES} ${INCLUDE_SDL}

affichages_terminal.o:
	$(CCOBJ) $(CFLAGS) ${AFF_DIR}affichages_terminal.c -o affichages_terminal.o ${INCLUDES} ${INCLUDE_NCURSES}

#Fichiers indépendants de l'affichage
map.o:
	$(CCOBJ) $(CFLAGS) $(INCLUDES) map.c -o map.o

commun.o : commun.c commun.h
	$(CCOBJ) $(CFLAGS) $(INCLUDES) commun.c -o commun.o

perso_monstre.o : perso_monstre.c perso_commun.h
	$(CCOBJ) $(CFLAGS) $(INCLUDES) perso_monstre.c -o perso_monstre.o

perso_joueur.o : perso_joueur.c perso_commun.h
	$(CCOBJ) $(CFLAGS) $(INCLUDES) perso_joueur.c -o perso_joueur.o

map_menace.o : map_menace.c map_menace.h
	$(CCOBJ) $(CFLAGS) $(INCLUDES) map_menace.c -o map_menace.o

inventaire.o : inventaire.c inventaire.h
	$(CCOBJ) $(CFLAGS) $(INCLUDES) inventaire.c -o inventaire.o

perso_commun.o : perso_commun.c perso_commun.h
	$(CCOBJ) $(CFLAGS) $(INCLUDES) perso_commun.c -o perso_commun.o

sauvegarde.o : sauvegarde.c perso_commun.h
	$(CCOBJ) $(CFLAGS) $(INCLUDES) sauvegarde.c -o sauvegarde.o


#Fichiers utilisants des fonctions d'affichage
main.o :
	$(CCOBJ) $(CFLAGS) $(INCLUDES) main.c -o main.o

combat.o : combat.c combat.h
	$(CCOBJ) $(CFLAGS) $(INCLUDES) combat.c -o combat.o

quete.o : quete.c quete.h
	$(CCOBJ) $(CFLAGS) $(INCLUDES) quete.c -o quete.o

level_editor.o:
	$(CCOBJ) $(CFLAGS) $(INCLUDES) level_editor.c -o level_editor.o

game.o:
	$(CCOBJ) $(CFLAGS) $(INCLUDES) game.c -o game.o

menu_principal.o:
	$(CCOBJ) $(CFLAGS) $(INCLUDES) menu_principal.c -o menu_principal.o


clean:
	rm -f ${PROG}
	rm -f *.o
