#include <perso_commun.h>
/**
 * \file perso_joueur.c
 * \brief Fonctions qui sont rattachées au joueur principal
 * \author Karman Nathalie; Papot Alexandre
 * \date 3 avril 2019
 * \ Ce fichier englobe les fonctions propres à la structure du Personnage que le joueur incarne
 */

static void affectation_classe(int choix, character_t* player){

   switch (choix){
      case 1: creer_string(&player->class_char,"warrior") ; break;
      case 2: creer_string(&player->class_char,"wizard") ; break;
      case 3: creer_string(&player->class_char,"hunter") ; break;
      case 4: creer_string(&player->class_char,"priest") ; break;
   }
}

/**
*	\fn static void affectation_genre(int choix, character_t* player);
*	\brief crée une chaîne de caracteres au champ gender
*	\param choix du joueur qui va de 1 à 4
*	\param player pour lui affecter les statistiques selon le choix
* \return void
*/

static void affectation_genre(int choix,character_t* player){

   switch (choix){
      case 1: creer_string(&player->gender,"man") ; break;
      case 2: creer_string(&player->gender,"woman") ; break;
   }
}

/**
*	\fn static void check_classe(int choix, character_t* player);
*	\brief sauvegarde les statistiques en accord avec la classe choisie par le joueur
*	\param choix du joueur qui va de 1 à 4
*	\param player pour lui affecter les statistiques selon le choix
* \return void
*/

static void check_classe(int choix, character_t* player){

    switch (choix) {
      case 1:{
                      player->stat_intelligence = 5;
                      player->stat_strength = 10;
                      player->stat_stamina = 10;

                      }break;
      case 2:{
                      player->stat_intelligence = 14;
                      player->stat_strength = 1;
                      player->stat_stamina = 10;

                      attribution_sort(entier_aleatoire(0,3),player); /* on lui donne un sort aléatoire*/

                      }break;
      case 3:{
                      player->stat_intelligence = 10;
                      player->stat_strength = 8;
                      player->stat_stamina = 7;
                      }break;
      case 4:{
                      player->stat_intelligence = 14;
                      player->stat_strength = 1;
                      player->stat_stamina = 10;
                      attribution_sort(19,player);  /*lui donne l'habileté de se protéger*/
                      }break;
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
   check_classe(choix,player);
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

    player->accessory=  green_amulet; /*green_amulet = protège de 10% le joueur si il a une "cloth armure"*/

    player->char_armor=malloc(sizeof(object_t));
    player->char_armor->type_object = armor;   /*armure*/
    player->char_armor->state_object=0; /*type armure = cloth, la plus basique*/
    affectation_object(player->char_armor);

    player->char_weapon=malloc(sizeof(object_t));
    player->char_weapon->type_object = weapon; /*arme*/
    player->char_weapon->state_object= 0;   /*pas d arme*/
    affectation_object(player->char_weapon);




    return player;
}


/*renvoie 1 pour retourner au menu principal, sinon il renvoie 0*/
int taking_potion(){

   int choix;

   do{
      afficher_inventaire();
      printf("Votre mana est de: %d/%d et votre vie est de %d/%d)\nQuel objet voulez-vous prendre? [0 pour retourner au menu précédent]\n", Personnage->mana, Personnage->max_mana,  Personnage->health,  Personnage->max_health);
      scanf("%d", &choix);
      viderBuffer();
   }while(choix > Inventaire->nb_objects || choix < 0);


   if(choix){

         printf("Vous avez choisi l'objet %d => %s\n",choix, Inventaire->object[choix-1]->name_object );

         /*on ne fait le traitement QUE SI c est un
           objet de type potion ou similaire (pas d armure par exemple)*/
         if(Inventaire->object[choix-1]->type_object == potion){


              printf("\n\t\tvotre mana est de %d/%d \n",  Personnage->mana, Personnage->max_mana);
              printf("\n\t\tvotre vie est de %d/%d \n",  Personnage->health, Personnage->max_health);

              float pourcentage =  Inventaire->object[choix-1]->value_object/10.0;

              if(est_mana(Inventaire->object[choix-1])){  /*on rentre dans le cas où c est une potion de mana*/

              Personnage->mana += Personnage->max_mana * pourcentage;
              Personnage->mana = (Personnage->mana  > Personnage->max_mana)? Personnage->max_mana : Personnage->mana;

            }else if(est_cure(Inventaire->object[choix-1])){ /*potion de vie*/


              Personnage->health += Personnage->max_health * pourcentage ;
              Personnage->health = ( Personnage->health > Personnage->max_health)? Personnage->max_health : Personnage->health ;

            }else if(est_phoenix(Inventaire->object[choix-1])){
              /*à faire si le joueur veut faire une équipe de 2 ou 3 personnages pour faire ses quetes*/

              }else{
              /* à faire ^^ */
              }
              deleteFrom_inventaire(choix);
              /* on a fait le traitement prévu, on retourne 0 pour dire que l utilisateur a fini*/
          }else{
                printf("L' objet choisi n'est pas une potion ou un objet qui peut être utilisé maintenant...\n");
                choix=0;  /*on retourne au menu précédent puisque il s'est trompé*/
          }

   }
   sleep(1);


   if(choix==0){
     sleep(1);
     clear_screen();
     printf("Retour au menu précédent...\n" );
   }

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
