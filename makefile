all:
	@read -p "sdl ou terminal? " PARAM; \
	make $$PARAM;

CC=gcc
SDL_DIR=./SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include
AFF=./Affichage/
PARAM=${1}
LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR} -I./ -lm -lncurses -I./Affichage/
PROG=programme

sdl: clean
	${CC} main.c map.c ${AFF}affichages_sdl.c ${AFF}fonctions_sdl.c quete.c game.c creationPerso.c menu_principal.c perso.c inventaire.c level_editor.c outils.c -o ${PROG} ${LIBS} ${INCLUDES}

terminal: clean
	${CC} main.c map.c ${AFF}affichages_terminal.c ${AFF}fonctions_terminal.c quete.c game.c creationPerso.c menu_principal.c perso.c inventaire.c level_editor.c outils.c -o ${PROG} ${LIBS} ${INCLUDES}


clean:
	rm -f ${PROG}
	rm -f *.o
