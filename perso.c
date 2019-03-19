
#include <perso.h>

character_t* creation_char(){
    character_t* player=NULL;
    player = malloc(sizeof(character_t));

    printf("Insert your name : ");
    scanf("%s", player->name);
    printf("Choose a class for your character : \n");
    printf("warrior, wizard, hunter, priest \n");
    scanf("%s", player->class_char);

    player->xp=0;
    player->level=1;
    player->health=100;
    player->mana=100;
    player->max_health=100;       /*vie maximum que peut avoir le joueur selon son niveau*/
    player->max_mana = 100;        /*valeur par default */
    int i ;

    for(i= 0; i<7 ;i++){
      player->state[i] = 0;
      player->spell[i] = 0;
    }
    player->stat_intel = 10;
    player->stat_stamina = 10;
    player->stat_strength = 10;
    player->accessory=  green_amulet;                  /*green_amulet = 0*/
    player->char_armor.type_object = 0;   /*armure*/
    player->char_armor.state_object=0;   /*cloth*/
    player->char_weapon.type_object = 1; /*arme*/
    player->char_weapon.state_object= 0;   /*dagger*/
    player->char_weapon.value_object= 30;
    return player;
}

void delete_player(character_t** player){

    if(*player != NULL){
      free(*player);
      *player=NULL;
   }
}

void affich(character_t* perso){
   printf("nom perso %s\n", perso->name);
   printf("xp = %d\n", perso->xp);
   printf("level = %d\n", perso->level);
   printf("health = %d\n", perso-> health);
   printf("mana= %d\n", perso->mana);
   printf("state= %d\n", perso->state[0]);
   printf("stat_strength = %d \n", perso->stat_strength);
   printf("stat_intel= %d \n", perso->stat_intel);
   printf("stat_stamina= %d \n", perso->stat_stamina);
   printf("class_char= %s\n", perso->class_char);
   printf("accessoire= %d\n", perso->accessory);
   char* objet= display_object(perso->char_armor);
   char* objet2= display_object(perso->char_weapon);
   printf("armure = %s\n",objet);
   printf("arme = %s\n",objet2);
}
