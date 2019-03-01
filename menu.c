#include <stdio.h>
#include <stdlib.h>

void new_game(){
    creation_char();
    creation_objects();
    load_map();

}

extern int choice=0;

switch(choice){
    case 1: new_game();
    case 2 : load_game();
    case 3: quit_game();
}
