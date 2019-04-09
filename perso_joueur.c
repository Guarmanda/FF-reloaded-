#include <commun_perso.h>
/**
 * \file perso_joueur.c
 * \brief Fonctions qui sont rattachées au joueur principal
 * \author Karman Nathalie; Papot Alexandre
 * \date 3 avril 2019
 */

static void affectation_classe(int choix, character_t* player){

   switch (choix) {
      case 1: creer_string(&player->class_char,"warrior") ; break;
      case 2: creer_string(&player->class_char,"wizard") ; break;
      case 3: creer_string(&player->class_char,"hunter") ; break;
      case 4: creer_string(&player->class_char,"priest") ; break;
   }
}

static void affectation_genre(int choix,character_t* player){

   switch (choix) {
      case 1: creer_string(&player->gender,"man") ; break;
      case 2: creer_string(&player->gender,"woman") ; break;
   }
}

character_t* creation_char(){
    character_t* player=NULL;
    player = malloc(sizeof(character_t));

    printf("Insert your name : ");
    player->name= malloc(sizeof(char)* TAILLE_STR);
    player->liste_spell= malloc(sizeof(liste_sort_t));

    lire(player->name,TAILLE_STR);
    printf("Welcome %s!\n",player->name);

    int choix=-1;
    do{
      printf("Choose a class for your character...\n \t1: warrior\n\t2: wizard\n\t3: hunter\n\t4: priest\n");

      scanf("%d",&choix);
      viderBuffer();
   }while (choix <1 || choix >4);

   affectation_classe(choix,player);

   do{
       printf("Choose a gender for your character \n\t1: man \n\t2: woman\n");
       scanf("%d",&choix);
       viderBuffer();
   }while (choix <1 || choix >2);

    affectation_genre(choix,player);
    /*valeurs par default des statistiques */
    player->xp=0;
    player->level=1;
    player->health= player->max_health = 100;
    player->mana=  player->max_mana = 100;
    /*vie maximum que peut avoir le joueur => ces champs ci changent au fur et à mesure que le joueur change de niveau*/

    int i;
    for(i = 0; i < MAX_ETATS ; i++){
      player->state[i] = FAUX;
    }


    player->stat_intelligence = player->stat_stamina = player->stat_strength = 10;

    player->accessory=  green_amulet; /*green_amulet = protège de 10% le joueur si il n'a pas d'armure autre que cloth*/

    player->char_armor=malloc(sizeof(object_t));
    player->char_armor->type_object = armor;   /*armure*/
    player->char_armor->state_object=0;
    affectation_object(player->char_armor);

    player->char_weapon=malloc(sizeof(object_t));
    player->char_weapon->type_object = weapon; /*arme*/
    player->char_weapon->state_object= 0;   /*pas d arme*/
    affectation_object(player->char_weapon);

    return player;
}

int taking_potion(character_t **player){

   int choix;

   do{
      afficher_inventaire();
      printf("Quel objet voulez-vous prendre? [0 pour retourner au menu précédent]\n");
      scanf("%d", &choix);
      viderBuffer();  /*éviter que le joueur ne saisisse autre chose que des entiers*/
   }while(choix > Inventaire->nb_objects|| choix<0);

   while(choix != 0 && choix!= -1){
         choix--;
         printf("Vous avez choisi l'objet %d => %s\n",choix+1, Inventaire->object[choix]->name_object );

         /*on ne fait le traitement QUE SI c est un
           objet de type potion ou similaire (pas d armure par exemple)*/
         if(Inventaire->object[choix]->type_object == potion){
/*
              printf("\n\t\tvotre mana est de %d/%d \n",  (*player)->mana,(*player)->max_mana);
              printf("\n\t\tvotre vie est de %d/%d \n",  (*player)->health, (*player)->max_health);
*/
              float pourcentage =  Inventaire->object[choix]->value_object/10.0;

              if(est_mana(Inventaire->object[choix])){  /*on rentre dans le cas où c est une potion de mana*/
                 (*player)->mana += (*player)->max_mana * pourcentage;
                 (*player)->mana = ((*player)->mana  > (*player)->max_mana)? (*player)->max_mana : (*player)->mana;

              }else if(est_cure(Inventaire->object[choix])){ /*potion de vie*/

                 (*player)->health += (*player)->max_health * pourcentage ;
                 (*player)->health = ((*player)->health > (*player)->max_health)? (*player)->max_health:(*player)->health ;

              }else if(est_phoenix(Inventaire->object[choix])){
                  /*à faire si le joueur veut faire une équipe de 2 ou 3 personnages pour faire ses quetes*/

              }else{
                /* à faire ^^ */
              }

              choix = -1; /* on a appliqué la potion ou autre*/

              }else{
                  printf("L' objet choisi n'est pas une potion ou un objet qui peut être utilisé maintenant...\n");
            }

   }
   if(!choix)
      printf("Retour au menu précédent...\n" );
   return choix;
}


static void nom_etat(int ind_dico_enum, char* nom){
  switch (ind_dico_enum){
    case 0: creer_string(&nom,"Stunt"); break;
    case 1: creer_string(&nom,"Bleed"); break;
    case 2: creer_string(&nom,"Slow"); break;
    case 3: creer_string(&nom,"Silence"); break;
    case 4: creer_string(&nom,"Poison"); break;
    case 5: creer_string(&nom,"Blind"); break;
    case 6: creer_string(&nom,"Speed"); break;
    case 7: creer_string(&nom,"Sleep"); break;
  }
}

void afficher_etats(character_t* player){
  int i;
  char* temp_nom;
  for (i=0 ; i< MAX_ETATS ; i++){
       if(player->state[i] == VRAI) {
         nom_etat(i,temp_nom);
         printf("%s\n",temp_nom );
         supprimer_string(&temp_nom);
       }
  }
}
