#include <commun_perso.h>
/**
 * \file perso_joueur.c
 * \brief Fonctions qui sont rattachées au joueur principal
 * \author Karman Nathalie; Papot Alexandre
 * \date 3 avril 2019
 */
static void affectation_classe(int choix, character_t* player){

   switch (choix) {
      case 1: player->class_char=creer_string("warrior") ; break;
      case 2: player->class_char=creer_string("wizard") ; break;
      case 3: player->class_char=creer_string("hunter") ; break;
      case 4: player->class_char=creer_string("priest") ; break;
   }
}

static void affectation_genre(int choix,character_t* player){

   switch (choix) {
      case 1: player->gender=creer_string("man") ; break;
      case 2: player->gender=creer_string("woman") ; break;
   }
}
character_t* creation_char(){
    character_t* player=NULL;

    player = malloc(sizeof(character_t));

    printf("Insert your name : ");
    player->name= malloc(sizeof(char)* TAILLE_STR);
    lire(player->name,TAILLE_STR);
    printf("Bienvenue %s!\n",player->name);
    int choix=-1;
    do{
      printf("Choose a class for your character : \n");
      printf("warrior, wizard, hunter, priest (1 à 4) \n");
      scanf("%d",&choix);
      viderBuffer();
   }while (choix <1 || choix >4);
   affectation_classe(choix,player);
   do{
       printf("Choose a gender for your character (man => 1 /woman => 2) : \n");
       scanf("%d",&choix);
       viderBuffer();
   }while (choix <1 || choix >4);
   affectation_genre(choix,player);

    player->xp=0;
    player->level=1;
    player->health=100;
    player->mana=100;
    player->max_health =100;       /*vie maximum que peut avoir le joueur selon son niveau*/
    player->max_mana = 100;        /*valeur par default */

    int i ;

    for( i = 0; i < MAX_ETATS ; i++){
      player->state[i] = FAUX;

    }

    player->stat_intelligence = 10;
    player->stat_stamina = 10;
    player->stat_strength = 10;

    player->accessory=  green_amulet;
                     /*green_amulet = 0*/
    player->char_armor.type_object = 0;   /*armure*/
    player->char_armor.state_object=0;   /*cloth*/
    player->char_weapon.type_object = 1; /*arme*/
    player->char_weapon.state_object= 0;   /*dagger*/
    player->char_weapon.value_object= 30;

    return player;
}

int taking_potion(character_t **player){
   int choix;
   char* temp;
   do{
      int i;
      for( i =0; i< Inventaire->nb_objects ; i++){
          temp=display_object(*Inventaire->object[i]);
         printf("objet %d => %s\n",i+1, temp );
      }
      printf("quel objet voulez-vous prendre? [0 pour retourner au menu précédent]\n");
      scanf("%d", &choix);
   }while (choix > Inventaire->nb_objects || choix<0 );

   while(choix != 0 && choix!= -1){
      /*if(choix > 0){*/
         choix--;
         printf("vous avez choisi\n" );
         temp =display_object(*Inventaire->object[choix]);
         printf("objet %d => %s\n",choix+1, temp );

         if(Inventaire->object[choix]->type_object == potion){ /*on ne rentre QUE si c est un
            objet de type potion ou similaire*/

            object_t* choix_potion= Inventaire->object[choix];
            printf("\n\t\tvotre mana est de %d/%d \n",  (*player)->mana,(*player)->max_mana);
            printf("\n\t\tvotre vie est de %d/%d \n",  (*player)->health, (*player)->max_health);

            float pourcentage = choix_potion->value_object/10.0;

            if(choix_potion->state_object <= 1){  /*on rentre dans le cas où c est une potion mana: 0 à 1*/
               (*player)->mana += (*player)->max_mana * pourcentage;
               (*player)->mana = ((*player)->mana  > (*player)->max_mana)? (*player)->max_mana: (*player)->mana;

            }else if(choix_potion->state_object <= 3){ /*potion de vie: 2 à3*/

               (*player)->health += (*player)->max_health * pourcentage ;
               (*player)->health = ((*player)->health > (*player)->max_health)? (*player)->max_health:(*player)->health ;


            }else if(choix_potion->state_object <= 5){

         /*      apply_state_modifier(player,choix_potion->value_object,VRAI);*/

            }else if(choix_potion->state_object <= 13){
            /*   apply_state_modifier(player,choix_potion->value_object,VRAI);*/
            }
            printf("\n\t\tvotre mana est de %d/%d\n",  (*player)->mana,(*player)->max_mana);
            printf("\n\t\tvotre vie est de %d/%d\n",  (*player)->health, (*player)->max_health);

            choix = -1;

            }else{
                  printf("l objet choisi n'est pas une potion ou un objet qui peut être utilisé maintenant...\n");
            }

   }
   if(!choix)
      printf("Retour au menu précédent...\n" );
   return choix;
}
