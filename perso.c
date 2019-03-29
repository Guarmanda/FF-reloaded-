#include <perso.h>
#include <commun.h>

/*partie des tests de l inventaire*/

void init_tab_sort(spell_t** tab_sort){
   int i;
   (*tab_sort[0]).nom_sort=creer_string("Fire 1");
   (*tab_sort[1]).nom_sort=creer_string("Thunder 1");
   (*tab_sort[2]).nom_sort=creer_string("Air 1");
   (*tab_sort[3]).nom_sort=creer_string("Ice 1");

   for(i = 0; i < 4; i++){

      tab_sort[i].valeur_sort = 20;
   }

   tab_sort[4].nom_sort=creer_string("Double Fire");
   tab_sort[5].nom_sort=creer_string("Double Thunder");
   tab_sort[6].nom_sort=creer_string("Double Air");
   tab_sort[7].nom_sort=creer_string("Double Ice");
   tab_sort[8].nom_sort=creer_string("Demi");   /*si niveau du target <= niv lanceur de sort + gerer aleatoire comme "evader"*/
   tab_sort[9].nom_sort=creer_string("Ultima"); /*super sort kek*/
   tab_sort[10].nom_sort=creer_string("Ultima 2"); /*9999 dégats*/

   for( ; i < 8; i++){
      tab_sort[i].valeur_sort = 40;
   }
   tab_sort[i].valeur_sort =50 ;
   tab_sort[i++].valeur_sort =70 ;
   tab_sort[i++].valeur_sort =90 ;
   for(i = 0; i<= 10; i++){
      tab_sort[i].type_sort = offensif;
   }

   /*sorts specifiques pour les monstres*/
   tab_sort[11].nom_sort=creer_string("Blind"); /*gerer avec aleatoire + chance  + level du lanceur de sort*/
   tab_sort[12].nom_sort=creer_string("Sleep");
   tab_sort[13].nom_sort=creer_string("Slow");
   tab_sort[14].nom_sort=creer_string("Stunt");
   tab_sort[15].nom_sort=creer_string("Bleed");
   tab_sort[16].nom_sort=creer_string("Berserk");
   int j;
   for(j=1 ; i < TAILLE_TAB_SORT; i++,j++){
      tab_sort[i].type_sort = modifie_etat;
      tab_sort[i].valeur_sort = j ;
   }

}


char* allocating_monster_name(int level){
     int randomizer = 0;

     randomizer = entier_aleatoire(1,100);   /*faire une fonction qui fasse le job*/

     char* monster_name= malloc(sizeof(char)*TAILLE_STR);  /*faire une fonction qui alloue et realloue plus tard 40 char */

     if(level > 8){

         if (randomizer > 80) {
            strcpy(monster_name, "Dragon");

         }
         else if (randomizer > 60){
            strcpy(monster_name, "Manticore");
         }
         else if  (randomizer > 40){
            strcpy(monster_name,"Terrible r");
         }
         else if  (randomizer > 20){
            strcpy(monster_name,"Gryffin");
         }
         else
            strcpy(monster_name,"Minotaur");

       }else if(level > 6){

         if (randomizer > 80) {
           strcpy(monster_name,"Dark troll");
         }
         else if (randomizer > 60){
           strcpy(monster_name,"Dark elf");
         }
         else if  (randomizer > 40){
           strcpy(monster_name,"Black wizard");
         }
         else if  (randomizer > 20){
           strcpy(monster_name,"Oger");
         }
         else
            strcpy(monster_name,"Your aaa");
       }else if(level > 4){
           if (randomizer > 80) {
             strcpy(monster_name,"Ghost");
         }
         else if (randomizer > 60){
          strcpy(monster_name,"Undead");
         }
         else if  (randomizer > 40){
           strcpy(monster_name,"Centaur");
         }
         else if  (randomizer > 20){
          strcpy(monster_name,"Troll");
         }
         else
            strcpy(monster_name, "Orc");

         }else{
           if(randomizer > 80) {
            strcpy(monster_name,"Wolf");
           }
         else if(randomizer > 60){
             strcpy(monster_name,"Snake");
         }
         else if(randomizer > 40){
            strcpy(monster_name,"Skeleton");
         }
         else if  (randomizer > 20){
            strcpy(monster_name, "Goblin");
         }
         else
            strcpy(monster_name,"Thief");
         }

   return monster_name;
}

character_t* monster_creation(int level){
     character_t* monster = NULL;
     monster= malloc(sizeof(character_t));

     char* nom_monstre= allocating_monster_name(monster->level);
     strcpy(monster->name,nom_monstre);

     monster->level = level;
     monster->max_health= monster->health = 20*level;
     monster->max_mana = monster->mana = 20*level;

     int i ;

     for(i= 0; i<7 ;i++){
       monster->state[i] = 0;
     }
    /*espace pour les sorts*/


     monster->stat_intel = 3;
     monster->stat_stamina = 3;
     monster->stat_strength = 3;

                 /*green_amulet = 0*/
     monster->char_armor.type_object = armor;   /*armure*/
     monster->char_armor.state_object=0;   /*cloth*/


     monster->char_weapon.type_object = weapon; /*arme*/
     monster->char_weapon.state_object= 0;   /*dagger*/
     monster->char_weapon.value_object= 5;

     return monster;
}

character_t* creation_char(){
    character_t* player=NULL;

    player = malloc(sizeof(character_t));

    printf("Insert your name : ");

    lire(player->name,40);
    printf("Bienvenue %s!\n",player->name);
    printf("Choose a class for your character : \n");
    printf("warrior, wizard, hunter, priest \n");
    lire(player->class_char,8);

    player->xp=0;
    player->level=1;
    player->health=100;
    player->mana=100;
    player->max_health =100;       /*vie maximum que peut avoir le joueur selon son niveau*/
    player->max_mana = 100;        /*valeur par default */

    int i ;

    for( i = 0; i < 7 ; i++){
      player->state[i] = 0;

    }
    player->spell= malloc(sizeof(spell_t)*7);

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

void attribution_sort(character_t* perso){

}
