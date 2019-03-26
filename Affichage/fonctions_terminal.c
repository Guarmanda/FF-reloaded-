#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <fonctions_affichage.h>



void drawText (int x, int y, char * z, int a, int b);
void drawImage (int x, int y, char * z, int a, int b);

int colornum(int fg, int bg)
{
    int B, bbb, ffff;

    B = 1 << 7;
    bbb = (7 & bg) << 4;
    ffff = 7 & fg;

    return (B | bbb | ffff);
}

short curs_color(int fg)
{
    switch (7 & fg) {           /* RGB */
    case 0:                     /* 000 */
        return (COLOR_BLACK);
    case 1:                     /* 001 */
        return (COLOR_BLUE);
    case 2:                     /* 010 */
        return (COLOR_GREEN);
    case 3:                     /* 011 */
        return (COLOR_CYAN);
    case 4:                     /* 100 */
        return (COLOR_RED);
    case 5:                     /* 101 */
        return (COLOR_MAGENTA);
    case 6:                     /* 110 */
        return (COLOR_YELLOW);
    case 7:                     /* 111 */
        return (COLOR_WHITE);
    }
}

int is_bold(int fg)
{
    /* return the intensity bit */

    int i;

    i = 1 << 3;
    return (i & fg);
}

void init_colorpairs(void)
{
    int fg, bg;
    int colorpair;

    for (bg = 0; bg <= 7; bg++) {
        for (fg = 0; fg <= 7; fg++) {
            colorpair = colornum(fg, bg);
            init_pair(colorpair, curs_color(fg), curs_color(bg));
        }
    }
}

void setcolor(int fg, int bg)
{
    /* set the color pair (colornum) and bold/bright (A_BOLD) */

    attron(COLOR_PAIR(colornum(fg, bg)));
    if (is_bold(fg)) {
        attron(A_BOLD);
    }
}

void faire_rendu(){
		refresh();
}

void quitter_affichage(){
  curs_set(1);
  clear();
  endwin();
}

void init_affichage(){
  initscr(); // initialize Ncurses
  fenetre = newwin( 24, 80, 0, 0 ); // création d'une fenêtre
  //initialisation des couleurs terminal
  if (has_colors() == FALSE) {
      endwin();
      puts("Vottre terminal ne supporte pas les couleurs");
      exit(1);
  }
  start_color();
  init_colorpairs();
  SCREEN_WIDTH = 80;
  SCREEN_HEIGHT = 24;
  SPRITE_W = 1;
  VITESSE_PERSO = 0.2; //on est en terminal, le perso sera plus rapide qu'en sdl
}

void fond_blanc(){
  setcolor(7, 7);
  for(int i=0; i<=SCREEN_HEIGHT; i++){
    for(int j=0; j<=SCREEN_WIDTH; j++){
      mvaddstr( i, j, "0" );
    }
  }
}
