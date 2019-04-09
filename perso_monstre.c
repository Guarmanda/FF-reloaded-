           creer_wolf(monstre);
       /*  strcpy(monstre->name,"Your angry mom");*/

   }else{
       if(chance_vs_advers > 80)
           creer_wolf(monstre);

       else if(chance_vs_advers > 60)
           creer_snake(monstre);

       else if(chance_vs_advers > 40)
           creer_skeleton(monstre);

       else if  (chance_vs_advers > 20)
           creer_goblin(monstre);

       else
           creer_thief(monstre);
      }

      return 1;

}
void init_stats_monstre(character_t* monstre){

    int i;
    int niveau = monstre->level;
    monstre->xp = 20 * niveau;
    monstre->max_health= monstre->health = 50*niveau;
    monstre->max_mana = monstre->mana = 40*niveau;

    for(i= 0; i<MAX_ETATS;i++){
      monstre->state[i] = 0;
    }

    monstre->stat_intelligence = 3*niveau;
    monstre->stat_stamina = 3*niveau;
    monstre->stat_strength = 3*niveau;

    monstre->char_armor.type_object = armor;   /*armure*/
    monstre->char_armor.state_object=0;
    monstre->char_armor.value_object= 5* niveau;   /*protection de 5% à 50%*/

    monstre->char_weapon.type_object = weapon; /*arme*/
    monstre->char_weapon.state_object= 0;   /*pas d arme*/
    monstre->char_weapon.value_object= 5 * niveau; /*attaque de 5% à 50%*/

    name_and_details(monstre);

}
void boss1(character_t* monster){

    (monster)->level = 8;
    (monster)->accessory= contre_poison;  /*espace foudre en bas à droite*/

    /* init_stats_monstre(monster);*/

}

static void bestiaire_foudre(character_t* monster){

    int niveau = entier_aleatoire(7,10); /*monstres de niv 7 à 10*/

    (monster)->level = niveau;
    (monster)->accessory=contre_ice;  /*espace foudre en bas à droite*/

   /*  init_stats_monstre(monster);*/

}


static void bestiaire_feu(character_t* monster){

    int niveau = entier_aleatoire(5,7); /*monstres de niv5-7*/
    (monster)->level=niveau;
    (monster)->accessory=contre_fire;  /*espace foudre en bas à droite*/

   /*  init_stats_monstre(monster);*/

}

static void bestiaire_neige(character_t* monster){
    (monster)->level= entier_aleatoire(5,7); /**/
    (monster)->accessory=contre_ice;  /*espace neige en bas à gauche*/
    init_stats_monstre(monster);
}

static void bestiaire_terre(character_t* monster){

    int niveau = entier_aleatoire(1,4); /*monstres de niv 1 à 4*/
    printf("on est la niv %d\n",niveau );
    (monster)->level=niveau;
    (monster)->accessory=contre_terre;
    init_stats_monstre(monster);

}

character_t* monster_creation(){

      character_t* monster = NULL;
      monster= malloc(sizeof(character_t));
      monster->liste_spell=malloc(sizeof(liste_sort_t));

      if (position_x > 500 && position_y < 500){  /*en bas à droite*/
        bestiaire_terre(monster);
      }else if( position_x > 500 && position_y > 500){
        bestiaire_feu(monster);
      }else if(position_x < 500 && position_y > 500){
       bestiaire_foudre(monster);
      }else
        bestiaire_neige(monster);

      return monster;
}
