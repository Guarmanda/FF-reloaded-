#include <stdio.h>
#include <stdlib.h>


character_t creation_char(){
    character_t* player=NULL;
    player=malloc(sizeof(character_t));
    printf("Insert your name : ");
    scanf("%s", player->name);
    printf("Choose a class for your character : \n");
    printf("warrior, wizard, hunter, priest \n");
    scanf("%s", player->class_char);
    player->xp=0;
    player->health=100;
    player->mana=100;
    for(int i = 0;i<7;i++){
      player->state[i] = 0;
    }
    player->stat_intel = 10;
    player->stat_stamina = 10;
    player->stat_strength = 10;
    player->accessoire=0; /*green_amulet = 0*/
    player->char_armor->cloth=1;
    player->char_weapon->dagger=1;
    return player;
}

void delete_player(character_t* player){
    if(player != NULL)
      free(player);
}
