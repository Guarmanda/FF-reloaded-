/**
 * \file perso_monstre.c
 * \brief Fonctions qui sont rattachées aux adversaires/bestiaire
 * \author Karman Nathalie; Papot Alexandre
 * \date 3 avril 2019
 * \ Ce fichier englobe les fonctions propres à la création des monstres et dans leur biome
*/

#include <perso_commun.h>

/**
 * \fn static void creer_dragon(character_t** monstre)
 * \brief Fonction qui crée un dragon et lui affecte son nom
 * \details on définit que l' \a EVASION =0 puisque c'est un BOSS
 * \param[in] monstre est un pointeur sur character_t*, on lui affectera les stats imaginées
 */
static void creer_dragon(character_t** monstre){
   creer_string(&(*monstre)->name,"Dragon");

   EVASION = 0; /*boss*/
}
/**
 * \fn static void creer_wolf(character_t** monstre)
 * \brief Fonction qui crée un wolf et lui affecte son nom
 * \details les fonctions des bestiaires sont à améliorer/finir
 * \param[in] monstre est un pointeur sur character_t*, on lui affectera les stats imaginées
 */
static void creer_wolf(character_t** monstre){
    creer_string(&(*monstre)->name,"Wolf");

}
/**
 * \fn static void creer_snake(character_t** monstre)
 * \brief Fonction qui crée un snake et lui affecte un nom
 * \details les fonctions des bestiaires sont à améliorer/finir
 * \param[in] monstre est un pointeur sur character_t*, on lui affectera les stats imaginées
 */
static void creer_snake(character_t** monstre){
    creer_string(&(*monstre)->name,"Snake");

}
/**
 * \fn static void creer_skeleton(character_t** monstre)
 * \brief Fonction qui crée un skeleton et lui affecte un nom
 * \details les fonctions des bestiaires sont à améliorer/finir
 * \param[in] monstre est un pointeur sur character_t*, on lui affectera les stats imaginées
 */
static void creer_skeleton(character_t** monstre){
    creer_string(&(*monstre)->name,"Skeleton");

}
/**
 * \fn static void creer_goblin(character_t** monstre)
 * \brief Fonction qui crée un goblin
 * \details les fonctions des bestiaires sont à améliorer/finir
 * \param[in] monstre est un pointeur sur character_t*, on lui affectera les stats imaginées
 */
static void creer_goblin(character_t** monstre){

    creer_string(&(*monstre)->name,"Goblin");

}
/**
 * \fn static void creer_thief(character_t** monstre)
 * \brief Fonction qui crée un thief
 * \details les fonctions des bestiaires sont à améliorer/finir
 * \param[in] monstre est un pointeur sur character_t*, on lui affectera les stats imaginées
 */
static void creer_thief(character_t** monstre){
    creer_string(&(*monstre)->name,"Thief");
}

/**
 * \fn static void name_and_details(character_t** monstre)
 * \brief Fonction qui va regarder le niveau du monstre à créer et lancer la création du monstre
 * \details pseudo-aléatoire et taux de chance de tomber contre quelques monstres spécifiques selon le niveau
 * \param[in] monstre est un pointeur sur character_t*, on lui affectera les stats imaginées
 */
static void name_and_details(character_t** monstre){

   int chance_vs_advers= entier_aleatoire(1,100); /*pourcentage de chance de tomber sur un monstre spécifique*/

   if((*monstre)->level > 7){

       if (chance_vs_advers > 80)          /*20% de chance que ce soit cet adversaire*/
           creer_dragon(monstre);
       else if (chance_vs_advers > 60)
           creer_dragon(monstre);/*  strcpy(monstre->name, "Manticore");*/
       else if  (chance_vs_advers > 40)
             creer_dragon(monstre);/*  strcpy(monstre->name,"Terrible r");*/
       else if  (chance_vs_advers > 20)
               creer_dragon(monstre);/*  strcpy(monstre->name,"Gryffin");*/
       else
             creer_dragon(monstre); /*  strcpy(monstre->name,"Minotaur");*/

   }else if((*monstre)->level  > 4){

       if (chance_vs_advers > 80)
               creer_wolf(monstre);
       else if (chance_vs_advers > 60)
               creer_wolf(monstre);
       else if  (chance_vs_advers > 40)
               creer_wolf(monstre);
       else if  (chance_vs_advers > 20)
            creer_wolf(monstre);
       else
           creer_wolf(monstre);

   }else{

       if(chance_vs_advers > 80)
           creer_skeleton(monstre);
       else if(chance_vs_advers > 60)
           creer_goblin(monstre);
       else if(chance_vs_advers > 40)
           creer_snake(monstre);
       else if  (chance_vs_advers > 20)
           creer_wolf(monstre);
       else
           creer_thief(monstre);
    }

}
/**
 * \fn static void init_stats_monstre(character_t** monstre)
 * \brief Fonction qui initialise les stats générales d'un monstre
 * \details fera appel à des fonctions locales
 * \param[in] monstre est un pointeur sur character_t*, on lui affectera les stats imaginées
 */
static void init_stats_monstre(character_t** monstre){

    int i;
    int niveau = (*monstre)->level;

    (*monstre)->xp = 20 * niveau;
    (*monstre)->max_health= (*monstre)->health = 50*niveau;
    (*monstre)->max_mana = (*monstre)->mana = 40*niveau;

    for(i= 0; i<MAX_ETATS;i++){

      (*monstre)->state[i] = FAUX;
    }

    (*monstre)->stat_intelligence = 2*niveau;
    (*monstre)->stat_stamina = 2*niveau;
    (*monstre)->stat_strength = 2*niveau;

    (*monstre)->char_armor=malloc(sizeof(object_t));
    (*monstre)->char_armor->type_object = armor;   /*armure*/
    (*monstre)->char_armor->state_object=0;
    (*monstre)->char_armor->value_object= value((*monstre)->char_armor->type_object, (*monstre)->char_armor->state_object);
    affectation_object((*monstre)->char_armor);

    (*monstre)->char_weapon=malloc(sizeof(object_t));
    (*monstre)->char_weapon->type_object = weapon; /*arme*/
    (*monstre)->char_weapon->state_object= 0;   /*pas d arme*/
    (*monstre)->char_weapon->value_object= value((*monstre)->char_weapon->type_object, (*monstre)->char_weapon->state_object);
    affectation_object((*monstre)->char_weapon);

    (*monstre)->accessory = est_monstre;
    name_and_details(monstre);

}
/**
 * \fn static void bestiaire_foudre(character_t** monster)
 * \brief Fonction qui affecte le niveau prévu au monstre en paramètre
 * \param[in] monstre est un pointeur sur character_t*, on lui affectera les stats imaginées
 */
static void bestiaire_foudre(character_t** monster){

    (*monster)->level= entier_aleatoire(7,10); /**/
    (*monster)->accessory=est_monstre;  /*espace foudre en haut à gauche*/
    init_stats_monstre(monster);

}
/**
 * \fn static void bestiaire_feu(character_t** monster)
 * \brief Fonction qui affecte le niveau prévu au monstre en paramètre
 * \param[in] monstre est un pointeur sur character_t*, on lui affectera les stats imaginées
 */
static void bestiaire_feu(character_t** monster){

    (*monster)->level= entier_aleatoire(5,7); /*en haut à droite*/
    (*monster)->accessory=est_monstre;
    init_stats_monstre(monster);
}
/**
 * \fn static void bestiaire_neige(character_t** monster)
 * \brief Fonction qui affecte le niveau prévu au monstre en paramètre
 * \param[in] monstre est un pointeur sur character_t*, on lui affectera les stats imaginées
 */
static void bestiaire_neige(character_t** monster){
    (*monster)->level= entier_aleatoire(5,7); /**/
    (*monster)->accessory=est_monstre;  /*espace neige en bas à gauche*/
    init_stats_monstre(monster);
}

/**
 * \fn static void bestiaire_terre(character_t** monster)
 * \brief Fonction qui affecte le niveau prévu au monstre en paramètre
 * \param[in] monstre est un pointeur sur character_t*, on lui affectera les stats imaginées
 */
static void bestiaire_terre(character_t** monster){

  (*monster)->level= entier_aleatoire(1,4); /**/
  (*monster)->accessory=est_monstre;  /*espace terre en bas à droite*/
  init_stats_monstre(monster);

}
/**
*	\fn character_t* monster_creation(void)
*	\brief Fonction qui crée le ou les adversaires du jeu
* \details bestiaire à completer
* \return character_t* pointeur sur le character_t créé
*/
character_t* monster_creation(){
   EVASION = 15;
   character_t* monster=NULL;
   monster = malloc(sizeof(character_t));

      if (position_x > 500 && position_y < 500){  /*en bas à droite*/
        bestiaire_terre(&monster);
      }else if(position_x > 500 && position_y > 500){
        bestiaire_feu(&monster);
      }else if(position_x < 500 && position_y > 500){
       bestiaire_foudre(&monster);
      }else
        bestiaire_neige(&monster);

      return monster;
}
