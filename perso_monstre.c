#include <perso_commun.h>

static void creer_dragon(character_t** monstre){
   creer_string(&(*monstre)->name,"Dragon");


}
static void creer_wolf(character_t** monstre){
    creer_string(&(*monstre)->name,"Wolf");


}
static void creer_snake(character_t** monstre){
    creer_string(&(*monstre)->name,"Snake");

}
static void creer_skeleton(character_t** monstre){
    creer_string(&(*monstre)->name,"Skeleton");

}
static void creer_goblin(character_t** monstre){

    creer_string(&(*monstre)->name,"Goblin");

}

static void creer_thief(character_t** monstre){
    creer_string(&(*monstre)->name,"Thief");
}

static void name_and_details(character_t** monstre){
   int i;

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
void delete_adversaire(character_t** player){

    if(*player != NULL){
      supprimer_string(&(*player)->name);
      free(*player);
      *player=NULL;
   }
}
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

static void bestiaire_foudre(character_t** monster){

    (*monster)->level= entier_aleatoire(7,10); /**/
    (*monster)->accessory=est_monstre;  /*espace foudre en haut à gauche*/
    init_stats_monstre(monster);

}


static void bestiaire_feu(character_t** monster){

    (*monster)->level= entier_aleatoire(5,7); /*en haut à droite*/
    (*monster)->accessory=est_monstre;
    init_stats_monstre(monster);

}

static void bestiaire_neige(character_t** monster){
    (*monster)->level= entier_aleatoire(5,7); /**/
    (*monster)->accessory=est_monstre;  /*espace neige en bas à gauche*/
    init_stats_monstre(monster);
}

static void bestiaire_terre(character_t** monster){

  (*monster)->level= entier_aleatoire(1,4); /**/
  (*monster)->accessory=est_monstre;  /*espace terre en bas à droite*/
  init_stats_monstre(monster);

}

character_t* monster_creation(){

   character_t* monster=NULL;
   monster = malloc(sizeof(character_t));
   monster->liste_spell= malloc(sizeof(liste_sort_t));

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
