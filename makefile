
CC=gcc

SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR}

PROG=programme

all: sdl_text

sdl_text: fonctions_sdl.o menu_principal.o map.o level_editor.o main.o
	${CC} -o ${PROG} fonctions_sdl.o menu_principal.o map.o level_editor.o main.o ${LIBS} ${INCLUDES}

fonctions_sdl.o: fonctions_sdl.c
	${CC} -o fonctions_sdl.o -c fonctions_sdl.c ${LIBS} ${INCLUDES}

menu_principal.o: menu_principal.c fonctions_sdl.h
	${CC} -o menu_principal.o -c menu_principal.c ${LIBS} ${INCLUDES}

map.o: map.c fonctions_sdl.h
	${CC} -o map.o -c map.c ${LIBS} ${INCLUDES}

level_editor.o: level_editor.c fonctions_sdl.h map.h
	${CC} -o level_editor.o -c level_editor.c ${LIBS} ${INCLUDES}

main.o: main.c menu_principal.h map.h level_editor.h
	${CC} -o main.o -c main.c ${LIBS} ${INCLUDES}


clean:
	rm -f ${PROG}
	rm -f *.o
