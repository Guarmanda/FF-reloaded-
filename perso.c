#include <perso.h>
#include <commun.h>

/*partie des tests de l inventaire*/

void init_tab_sort(spell_t* tab_sort){ /*à initialiser au début de la partie*/
   int i;

   if(tab_sort != NULL){
     tab_sort[0].nom_sort=creer_string("Feu 1");
     tab_sort[1].nom_sort=creer_string("Eclair 1");
     tab_sort[2].nom_sort=creer_string("Air 1");
     tab_sort[3].nom_sort=creer_string("Eau 1");

     for(i = 0; i < 4; i++){

        tab_sort[i].valeur_sort = 20;
     }

     tab_sort[4].nom_sort=creer_string("Double Feu");
     tab_sort[5].nom_sort=creer_string("Double Eclair");
     tab_sort[6].nom_sort=creer_string("Double Air");
     tab_sort[7].nom_sort=creer_string("Double Eau");
     tab_sort[8].nom_sort=creer_string("Demi");   /*si niveau du target <= niv lanceur de sort + gerer aleatoire comme "evader"*/
     tab_sort[9].nom_sort=creer_string("Tremblement de terre"); /*degat à tous les enemis*/
     tab_sort[10].nom_sort=creer_string("Ultima 2"); /*9999 dégats sur tous les enemis aussi*/

     for( ; i < 8; i++){
        tab_sort[i].valeur_sort = 40;
     }
     tab_sort[i].valeur_sort =50 ;  /*pour sort Demi qui joue sur les pourcentages*/
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

     /*sorts de type magie blanche */
     tab_sort[17].nom_sort=creer_string("Antidote");  /*enleve un etat */
     tab_sort[19].nom_sort=creer_string("Hologramme");  /*devient
     tab_sort[18].nom_sort=creer_string("Poudre de perlimpinpin");
    transparent*/
     int j;
     for(j=1 ; i < TAILLE_TAB_SORT - 1; i++,j++){
        tab_sort[i].type_sort = modifie_etat;
        tab_sort[i].valeur_sort = j ;
     }
      tab_sort[i].valeur_sort = 70;  /*poudre de perlimpinpin*/

   }
}

int detruire_tab_sort(spell_t** tab_sort){

    if(*tab_sort != NULL ){
      int i;
      for(i=0 ; i <TAILLE_TAB_SORT ; i++){
        printf("oui %d\n",i);
        /*à faire urgent!!!!*/
        /*free(&(tab_sort[i]->nom_sort));
        supprimer_string(&((*tab_sort[i]).nom_sort));*/

      }
      free(*tab_sort);
      return(0);
    }else
      return(1);
}
/*
void attribution_sort(character_t* joueur, spell_t* tab_sort, int indice){


    int i;
    for(i=0 ; i< MAX_SORTS && joueur->spell !=NULL;i++ );

    if(joueur->accessory>0){
      if(i==MAX_SORTS){
        printf("Vous devez supprimer un sort pour pouvoir affecter le nouveau...\n");
        return;
      }
    }

    joueur->spell[i] = tab_sort[i];

}*/


static int name_and_spells(character_t** monstre){
      int i;
/*

         */
         printf("\t\t\t monstre %s est niveau %d \n",(*monstre)->name, (*monstre)->level );
     return 1;
}

static void init_stats_monstre(character_t* monstre){

    int niveau = monstre->level;

    monstre->xp = 20 * niveau;

    monstre->max_health= monstre->health = 50*niveau;
    monstre->max_mana = monstre->mana = 40*niveau;

    int i;

    for(i= 0; i<MAX_ETATS;i++){
      monstre->state[i] = 0;
    }

    /*espace pour les sorts*/

    monstre->stat_intelligence = 3*niveau;
    monstre->stat_stamina = 3*niveau;
    monstre->stat_strength = 3*niveau;

    monstre->char_armor.type_object = armor;   /*armure*/
    monstre->char_armor.state_object=0;
    monstre->char_armor.value_object= 5* niveau;   /*protection de 5% à 50%*/

    monstre->char_weapon.type_object = weapon; /*arme*/
    monstre->char_weapon.state_object= 0;   /*pas d arme*/
    monstre->char_weapon.value_object= 5 * niveau;
  /*  monstre->spell= malloc(sizeof(monstre->spell)* MAX_SORTS);
    */

    name_and_spells(&monstre);

}
static void bestiaire_haut_gauche(character_t** monster){

    int niveau = entier_aleatoire(7,10); /*monstres de niv 7 à 10*/

    (*monster)->level = niveau;
    (*monster)->accessory=contre_ice;  /*espace foudre en bas à droite*/

    init_stats_monstre(*monster);

}
void boss1(character_t** monster){

    (*monster)->level = 8;
    (*monster)->accessory=invicible;  /*espace foudre en bas à droite*/

    init_stats_monstre(*monster);

}

static void bestiaire_haut_droite(character_t** monster){

    int niveau = entier_aleatoire(5,7); /*monstres de niv5-7*/
    (*monster)->level=niveau;
    (*monster)->accessory=contre_air;  /*espace foudre en bas à droite*/

    init_stats_monstre(*monster);

}

static void bestiaire_bas_gauche(character_t** monster){

    int niveau = entier_aleatoire(5,7); /**/

    (*monster)->level=niveau;
    (*monster)->accessory=contre_thunder;  /*espace foudre en bas à droite*/
    init_stats_monstre(*monster);

}


static void bestiaire_bas_droite(character_t** monster){

    int niveau = entier_aleatoire(1,4); /*monstres de niv 1 à 4*/
    printf("on est la niv %d\n",niveau );
    (*monster)->level=niveau;
    (*monster)->accessory=contre_fire;
    init_stats_monstre(*monster);
    /*name_and_spells(*monster);*/

}

character_t* monster_creation(){
     character_t* monster = NULL;
     monster= malloc(sizeof(character_t*));

     if (position_x > 500 && position_y < 500){  /*en bas à droite*/
        bestiaire_bas_droite(&monster);
     }else if( position_x > 500 && position_y > 500){
        bestiaire_haut_droite(&monster);
     }else if(position_x < 500 && position_y > 500){
       bestiaire_haut_gauche(&monster);
     }else
        bestiaire_bas_gauche(&monster);

   /* printf("LE MONSTRE A %d niv %d /%d\n",monster->level,monster->health,monster->max_health );*/
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
    strcpy(player->gender, "man");

    player->xp=0;
    player->level=1;
    player->health=100;
    player->mana=100;
    player->max_health =100;       /*vie maximum que peut avoir le joueur selon son niveau*/
    player->max_mana = 100;        /*valeur par default */

    int i ;

    for( i = 0; i < MAX_ETATS ; i++){
      player->state[i] = 0;

    }
    /* player->spell= NULL; faut il faire autrement?*/

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

void delete_player(character_t** player){

    if(*player != NULL){
      free(*player);
      *player=NULL;
   }
}

void affich_stats(character_t* perso){
   printf("nom perso %s\n", perso->name);
   printf("xp = %d\n", perso->xp);
   printf("level = %d\n", perso->level);
   printf("health = %d\n", perso-> health);
   printf("mana= %d\n", perso->mana);
   printf("state= %d\n", perso->state[0]);
   printf("stat_strength = %d \n", perso->stat_strength);
   printf("stat_intelligence= %d \n", perso->stat_intelligence);
   printf("stat_stamina= %d \n", perso->stat_stamina);
   printf("class_char= %s\n", perso->class_char);
   printf("accessoire= %d\n", perso->accessory);
   char* objet= display_object(perso->char_armor);
   char* objet2= display_object(perso->char_weapon);
   printf("armure = %s\n",objet);
   printf("arme = %s\n",objet2);
}
