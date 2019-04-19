/**
 * \file perso_joueur.c
 * \brief Fonctions qui sont rattachées au joueur
 * \author Karman Nathalie; Papot Alexandre
 * \date 3 avril 2019
 * \ Ce fichier englobe les fonctions propres au Personnage que le joueur incarne
*/

#include <perso_commun.h>

/**
 * \fn static void affectation_classe(int choix, character_t* player)
 * \brief Fonction qui affecte la chaine de caractere correcte à la classe du joueur
 * \details pourrait y avoir 4 personnages comme prévu et encore 8 autres classes pour l'affectation désirée
 * \param[in] choix est la saisie du joueur dans le terminal
  * \param[in] player est le personnage qui aura sa classe affectée
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
*	\brief crée une chaîne de caracteres au champ \a gender
*	\param[in] choix du joueur qui va de 1 à 2
*	\param[in] player pour lui affecter les statistiques selon le choix
*/
static void affectation_genre(int choix,character_t* player){

   switch (choix){
      case 1: creer_string(&player->gender,"man") ; break;
      case 2: creer_string(&player->gender,"woman") ; break;
   }
}

/**
*	\fn static void check_classe(int choix, character_t* player);
*	\brief change les statistiques en accord avec la classe choisie par le joueur
*	\param[in] choix du joueur qui va de 1 à 4
*	\param[in] player pour lui affecter les statistiques selon le choix de l utilisateur
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
                      int nb_al=entier_aleatoire(0,3);
                      attribution_sort(nb_al,player); /* on lui donne un sort aléatoire*/
                      attribution_sort(nb_al+1,player); /* on lui donne un sort aléatoire*/
                      player->char_weapon->state_object= 1;   /*staff pour wizard*/
                      }break;
      case 3:{
                      player->stat_intelligence = 10;
                      player->stat_strength = 8;
                      player->stat_stamina = 7;
                      player->char_weapon->state_object= 3;   /*bow pour hunter*/
                      }break;
      case 4:{
                      player->stat_intelligence = 14;
                      player->stat_strength = 1;
                      player->stat_stamina = 10;
                      attribution_sort(19,player);  /*lui donne l'habileté de se protéger*/
                      player->char_weapon->state_object= 1;   /*staff pour priest*/
                      }break;
    }
}
/**
*	\fn character_t* creation_char(void)
*	\brief Fonction qui crée le personnage principal du jeu
* \return character_t* pointeur sur le character_t créé
*/
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
      printf("Choose a class for your character...\n \t1: warrior\n\t2: wizard\n\t3: hunter\n\t4: priest\nVotre choix : ");

      scanf("%d",&choix);
      viderBuffer();
   }while (choix <1 || choix >4);

   affectation_classe(choix,player);
   player->char_weapon=malloc(sizeof(object_t));

   check_classe(choix,player);


   do{
       printf("Choose a gender for your character \n\t1: man \n\t2: woman\nVotre choix : ");
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

    player->accessory=  green_amulet; /*green_amulet = protège de 10% le joueur */

    player->char_weapon->type_object = weapon; /*arme*/
    player->char_weapon->value_object= value(player->char_weapon->type_object, player->char_weapon->state_object);
    affectation_object(player->char_weapon);

    player->char_armor=malloc(sizeof(object_t));
    player->char_armor->type_object = armor;
    player->char_armor->state_object=0;      /*même armure pour tous*/
    player->char_armor->value_object= value(player->char_armor->type_object, player->char_armor->state_object);
    affectation_object(player->char_armor);

    return player;
}

/**
*	\fn int taking_potion(void)
*	\brief Fonction utile dans module \a combat.c
*	\
*	\return 0 pour retourner au menu principal, sinon elle renvoie l'indice de l'objet choisi
*/
int taking_potion(){

   int choix;

   do{

      if( afficher_inventaire() != 0){
        printf("\nTapez 0 pour retourner au menu précédent.\nVotre choix : " );
        scanf("%d", &choix);
        viderBuffer();
      }else{
        choix=0;
      }
   }while(choix > Inventaire->nb_objects || choix < 0);


   if(choix){

         printf("Vous avez choisi l'objet %d => %s\n",choix, Inventaire->object[choix-1]->name_object );

         /*on ne fait le traitement QUE SI c est un
           objet de type potion ou similaire (pas d armure par exemple)*/
         if(Inventaire->object[choix-1]->type_object == potion){

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

          }else{
                printf("L' objet choisi n'est pas une potion ou un objet qui peut être utilisé maintenant...\n");
                choix=0;  /*on retourne au menu précédent puisque il s'est trompé*/
          }

   }
   sleep(1);

   if(choix==0){
     clear_screen();
   }else
      printf("Votre mana est de: %d/%d et votre vie est de %d/%d)\n", Personnage->mana, Personnage->max_mana,  Personnage->health,  Personnage->max_health);

   return choix;
}
/**
 * \fn static int recup_sort(character_t* perso, int compteur)
 * \brief Fonction qui récupère l'indice du sort souhaité par l'utilisateur
 * \details
 * \param[in] perso type \character_t est le personnage pris en compte
 * \param[in] saisie entier saisi par l'utilisateur
 * \return renvoie -2 si la saisie est pas bien faite, sinon retourne l'indice du champ \a indice_tab_sorts
 */
static int recup_sort(character_t* perso, int saisie){
      liste_sort_t* temp;
      temp = perso->liste_spell;
      int cpt=1;

      while(temp!= NULL && cpt!=saisie){
          temp=temp->sort_suivant;
          cpt++;
      }

      debut_liste(&perso);
      return (saisie<= cpt && temp != NULL ) ? temp->indice_tab_sorts   : -2;
}

/**
 * \fn int joueur_sort(character_t* perso)
 * \brief Fonction qui donne au joueur, l'option de choisir un sort parmi la liste chainee
 * \details va juste positionner l'élément courant comme étant le début de la liste
 * \param[in] perso type \character_t est le personnage pris en compte
 * \return -1 si la personne veut retourner au menu d'avant ou l'indice du sort ou -2 si le joueur a mal fait la saisie
 */
int joueur_sort(character_t* perso){

    if(perso->liste_spell!= NULL){
        afficher_sorts(perso);
        int cpt;
        do{
          printf("Quel sort voulez-vous? [0 pour retourner au menu précédent]\nVotre choix : " );
          scanf("%d",&cpt );
        }while(cpt < 0);

        return cpt == 0? -1 : recup_sort(perso,cpt);

    }else
      printf("Vous n'avez pas de sort.\n");

    sleep(1);
    return -1;

}
