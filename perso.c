/**
 * \file perso.c
 * \brief Fonction relative au personnage.
 * \author Papot Alexandre Karman Nathalie et Girod Valentin
 * \date 12 mars 2019
 *
 * Contient la creation/suppression du personnage et son affichage
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <perso.h>

/**
 * \fn character_t* creation_char()
 * \brief Fonction de creation du personnage
 * \return Pointeur sur personnage (character_t*)
 */

character_t* creation_char(){
    character_t* player=NULL; 
    player = malloc(sizeof(character_t));
    strcat(player->name , "jack");
    strcat(player->class_char, "warrior");
    strcat(player->gender, "man");
    player->xp=0;
    player->level=1;
    player->health=100;
    player->mana=100;
    player->max_health=100;
    player->max_mana = 100;
    int i ;
    for(i= 0; i<7 ;i++){
      player->state[i] = 0;
      player->spell[i] = 0;
    }
    player->stat_intel = 10;
    player->stat_stamina = 10;
    player->stat_strength = 10;
    player->accessory=green_amulet;
    player->char_armor.type_object = 0;   /*armure*/
    player->char_armor.state_object=0;   /*cloth*/

    player->char_weapon.type_object = 1; /*armure*/
    player->char_weapon.state_object=0;   /*dagger*/
    return player;
}

/**
 * \fn void levelling(character_t* player, character_t monster)
 * \brief Fonction qui gère l'attribution de l'experience après un combat
 *
 * \param[in] Pointeur sur structure personnage (character_t*)
 * \param[in] Structure personnage (le monstre)
 */

void levelling(character_t* player, character_t monster){
         /*à priori le nb de monstres est variables (nb param variables)*/
      int cap_xp = 50;
      int cap_reward = 50;
      player->xp += cap_xp * monster.level;
      if(player->xp >= (cap_reward * player->level)){
         player->level++;
      }
}

/**
 * \fn void delete_player(character_t* player)
 * \brief Fonction qui supprime le joueur
 * \param[in] Pointeur sur structure personnage (character_t*)
 */

void delete_player(character_t* player){
    if(player != NULL){
      free(player);
      player=NULL;
   }

}

/**
 * \fn void affich(character_t* perso)
 * \brief Fonction qui affiche le personnage
 * \param[in] Pointeur sur structure personnage (character_t*)
 */

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
