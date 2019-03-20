
CC=gcc

SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR} -I./ -lm -lncurses

PROG=programme

all: sdl_text

sdl_text: fonctions_sdl.o fonctions_terminal.o quete.o game.o creationPerso.o menu_principal.o map.o perso.o inventaire.o menu_inventaire.o level_editor.o main.o outils.o
	${CC} -o ${PROG} fonctions_sdl.o fonctions_terminal.o quete.o game.o creationPerso.o menu_principal.o map.o perso.o inventaire.o menu_inventaire.o level_editor.o outils.o main.o ${LIBS} ${INCLUDES}

fonctions_sdl.o:
	${CC} -o fonctions_sdl.o -c fonctions_sdl.c ${LIBS} ${INCLUDES}

fonctions_terminal.o:
	${CC} -o fonctions_terminal.o -c fonctions_terminal.c ${LIBS} ${INCLUDES}

perso.o:
	${CC} -o perso.o -c perso.c ${LIBS} ${INCLUDES}

game.o:
	${CC} -o game.o -c game.c ${LIBS} ${INCLUDES}

creationPerso.o:
	${CC} -o creationPerso.o -c creationPerso.c ${LIBS} ${INCLUDES}

menu_principal.o:
	${CC} -o menu_principal.o -c menu_principal.c ${LIBS} ${INCLUDES}

map.o:
	${CC} -o map.o -c map.c ${LIBS} ${INCLUDES}

quete.o:
	${CC} -o quete.o -c quete.c ${LIBS} ${INCLUDES}

inventaire.o:
	${CC} -o inventaire.o -c inventaire.c ${LIBS} ${INCLUDES}

outils.o:
	${CC} -o outils.o -c outils.c ${LIBS} ${INCLUDES}

menu_inventaire.o:
	${CC} -o menu_inventaire.o -c menu_inventaire.c ${LIBS} ${INCLUDES}

level_editor.o:
	${CC} -o level_editor.o -c level_editor.c ${LIBS} ${INCLUDES}

main.o:
	${CC} -o main.o -c main.c ${LIBS} ${INCLUDES}


clean:
	rm -f ${PROG}
	rm -f *.o
