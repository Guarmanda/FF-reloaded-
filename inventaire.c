/**
 * \file      inventaire.c
 * \author    Nathalie Karman, Alexandre Papot
 * \version   1.0
 * \date     Mars 2019
 * \brief    Module qui crée l'inventaire du joueur et les objets du jeu
 *
 * \details    Module à l'origine du jeu : le joueur crée un ou des personnages, et démarre sa partie avec un inventaire.
 *\ Ce fichier est celui qui définit aussi le type object_t qui est celui qui est stocké dans l'inventaire
 */

#include <inventaire.h>

 /**
  * \fn   int value(int type, int state)
  * \brief Fonction qui renvoie la valeur symbolique ou réelle d'un objet
  * \details Possède plusieurs \a dictionnaires qui, à partir des paramètres,
  *         affectent la valeur à l'objet
  * \param[in] type est l'entier qui définit le type de l'objet
  * \param[in] state entier qui correspond à l'indice respectif du type, dans un des dictionnaires \a en local
  * \return la valeur de l'objet ou KO_state si le type n'existe pas
  */
 int value(int type, int state){
   int tab_armor[4] = {10,20,30,40}; /*les valeurs sont des pourcentages*/
   int tab_weapon[5] = {3,5,7,7,10};        /*valeur symboliques qui sont définies dans inventaire.h*/
   int tab_potion[13] = {30,70,30,70,30,70,Stunt,Bleed,Slow,Silence,Poison,Blind,Sleep};
   int tab_objet[1]={tente};

   switch(type){
        case armor: return tab_armor[state];break;
        case weapon: return tab_weapon[state];break;
        case potion: return tab_potion[state];break;
        case tente: return tab_objet[state]; break;
   }
   return KO_state;   /*code d erreur si aucun cas de type connu*/
 }

 /**
  * \fn  void affectation_object(object_t* object)
  * \brief Fonction qui affecte à l'objet, une chaîne de caractère : sa \a description
  * \param[in] object est un \a object_t, son champ \a name_object lui sera affecté ici
  */
 void affectation_object(object_t* object){

        object->value_object= value(object->type_object, object->state_object);

        if(object->type_object == armor){      /*type armure*/

          switch (object->state_object) {

             case 0: creer_string(&object->name_object,"cloth armor"); break;
             case 1: creer_string(&object->name_object,"leather armor");  break;
             case 2: creer_string(&object->name_object,"silver armor"); break;
             case 3: creer_string(&object->name_object,"golden armor"); break;
          }
       }
       else if(object->type_object == weapon){ /*weapon */

          switch (object->state_object) {
             case 0: creer_string(&object->name_object,"dagger"); break;
             case 1: creer_string(&object->name_object,"staff"); break;
             case 2:  creer_string(&object->name_object,"axe"); break;
             case 3:  creer_string(&object->name_object,"bow"); break;
             case 4:  creer_string(&object->name_object,"sword"); break;
          }
       }else if(object->type_object == tente){ /*pour la tente qui fait la sauvegarde */

           creer_string(&object->name_object,"tent");

       }else{

             switch (object->state_object) {
                case 0: creer_string(&object->name_object,"mana potion"); break;
                case 1: creer_string(&object->name_object,"super mana potion"); break;
                case 2: creer_string(&object->name_object,"health potion"); break;
                case 3: creer_string(&object->name_object,"super health potion"); break;
                case 4: creer_string(&object->name_object,"phoenix potion"); break;
                case 5: creer_string(&object->name_object,"super phoenix potion"); break;
                case 6: creer_string(&object->name_object,"anti stunt potion"); break;
                case 7: creer_string(&object->name_object,"anti bleeding potion"); break;
                case 8: creer_string(&object->name_object,"anti slow potion"); break;
                case 9: creer_string(&object->name_object,"anti silence potion"); break;
                case 10: creer_string(&object->name_object,"anti poison potion"); break;
                case 11: creer_string(&object->name_object,"anti blind potion"); break;
                case 12: creer_string(&object->name_object,"speed potion"); break;
                case 13: creer_string(&object->name_object,"lucidity potion"); break;

             }
       }

 }

 /**
  * \fn  object_t* create_object(int type, int etat)
  * \brief Fonction de création d'un objet \a object_t spécifique
  * \details La fonction est utile QUE lorsque le programmeur sait quel objet
  *   sera attribué
  * \param[in] type est un entier qui est spécifié dans \a inventaire.h en enumération
  * \param[in] etat est un entier qui définit la spécificité de l'objet
  * \return pointeur sur l'objet créé
  */
 object_t* create_object(int type, int etat){

    object_t * new_item = malloc(sizeof(object_t));
    new_item->type_object = type;
    new_item->state_object = etat;
    new_item->value_object = value(new_item->type_object, new_item->state_object);
    affectation_object(new_item);
    return new_item;
 }
 /**
  * \fn static int loot_type (int niveau_adversaire)
  * \brief Fonction qui génère le type d'un objet (récompense) \object_t
  * \param[in]  niveau_adversaire le niveau de l'adversaire vaincu
  * \return un entier qui représente le type
  */
static int loot_type(int niveau_adversaire){

     int type_random = entier_aleatoire(1,100);

     if(type_random <5){              /* 5% de chance d avoir une armure */
       return armor;
     }else if(type_random < 15){        /* 15% de chance d avoir une arme*/
       return weapon;
     }else if(type_random < 30){        /* 30% de chance d avoir une tente*/
       return tente;
     }else{
       return potion;        /* type potion a 70% d etre lootée */
     }
}

/**
 * \fn static int loot_state(int type, int niveau_adversaire)
 * \brief Fonction qui donne une spécificité à l'objet à partir des paramètres
 * \details le type est donné de manière pseud-aléatoire à partir du paramètre
 * \param[in] type le type obtenu à partir de l'adversaire vaincu
 * \param[in] niveau_adversaire le niveau de l'adversaire vaincu
 * \return KO_state si le type n'existe pas ou l'entier qui représente la spécificité de l'objet créé
 */
static int loot_state(int type, int niveau_adversaire){

  switch(type){
      case armor : {
                     if(niveau_adversaire < 3)
                         return 0;
                     else if(niveau_adversaire < 8){
                         return entier_aleatoire(1,2);
                     }
                     else
                        return 3;
       }; break;
      case weapon : return entier_aleatoire(1,4) ;break;
      case potion : {
                     if(niveau_adversaire < 3){
                       int rand=entier_aleatoire(0,2);
                       return rand ;
                     }
                     else if(niveau_adversaire < 8){
                       int rand=entier_aleatoire(3,13);
                       return rand ;/*voir si ok*/

                     }
                    /* else{
                       return entier_aleatoire(0,14);
                       return (rand() % 12) + 2;
                     }*/
      }break;
      case tente: return 0; break;
     }
     return KO_state ;
}

 /**
  * \fn    object_t* create_loot(int niv_monstre)
  * \brief Fonction de création d'un loot \a object_t
  *
  * \param[in] niv_monstre est l'entier qui guide la création d'un nouvel objet
  * \return pointeur sur l'objet créé
  */
 object_t* create_loot(int niv_monstre){ /*va vérifier la valeur de l objet */
    /* state sera donne par un rand dans une range selon la difficulte du mob monstre->level*/

    object_t * new_item = malloc(sizeof(object_t));
    new_item->type_object = loot_type(niv_monstre);
    new_item->state_object = loot_state(new_item->type_object,niv_monstre);
    new_item->value_object = value(new_item->type_object, new_item->state_object);
    affectation_object(new_item);
    return new_item;
 }

 /**
  * \fn  void delete_object(object_t **item)
  * \brief Fonction qui supprime un objet et son champ \a name_object
  * \param[in] item est un pointeur sur l'adresse de l'objet a être supprimé
  */
 void delete_object(object_t **item){
     supprimer_string(&(*item)->name_object);
     free(*item);
     *item = NULL;
 }

 /**
  * \fn   void create_inventory(void)
  * \brief Fonction qui crée l'inventaire \a Inventaire qui est en global
  */
 void create_inventory(){

    Inventaire= malloc(sizeof (inventory_t));

    Inventaire->nb_objects =0;
    int i;
    for( i = 0; i<30; i++){
       Inventaire->object[i] = NULL;
    }

 }

 /**
  * \fn  err_t delete_inventory(void)
  * \brief Fonction qui supprime l'inventaire et ce qu'il contient
  * \details s'aide de la fonction \a delete_object
  * \return KO_state si l'inventaire n'a pas été initialisé ou OK_state
  */
 err_t delete_inventory(){
   int i;
   if(Inventaire != NULL){
     for( i = 0; i<Inventaire->nb_objects; i++){
       delete_object(&Inventaire->object[i]);
     }
     free(Inventaire);
     return OK_state;
   }
   return KO_state;

 }

 /**
  * \fn    static void affichage_type(object_t* objet, string* type_affich)
  * \brief  Fonction qui donne temporairement la description des objets du jeu
  * \details sert pour l'affichage, fonction intermédiaire : \a remplace une BDD
  */
 static void affichage_type(object_t* objet, string* type_affich){

     switch (objet->type_object){
       case weapon: creer_string(type_affich,"%% de dégats"); break;
       case armor: creer_string(type_affich,"%% de défense"); break;
       case potion:{
                     if(objet->state_object >= 0 && objet->state_object <= 5 ){
                       creer_string(type_affich, "%% de l'effet indiqué");
                     }else
                       creer_string(type_affich, "%%");
         }; break;
       case tente: creer_string(type_affich,"Passer une nuit au calme et reprendre ses esprits..."); break;

     }
 }

 /**
  * \fn  int afficher_inventaire(void)
  * \brief Fonction qui affiche tous les objets de l'inventaire
  * \return 0 si l inventaire est vide, sinon return 1
  */
 int afficher_inventaire(){

 	int i;
    if (Inventaire->nb_objects >0){
     string affiche_le_type;
    	printf("Votre inventaire contient :\n");
    	for(i = 0; i< Inventaire->nb_objects ;i++){
          affichage_type(Inventaire->object[i],&affiche_le_type);
          printf("\titem %i : %s (%d %s)\n",i+1,Inventaire->object[i]->name_object, Inventaire->object[i]->value_object,affiche_le_type);
          supprimer_string(&affiche_le_type);
    	}
      return 1;
    }

     printf("L' inventaire est vide\n");
     return 0;

 }
 /**
  * \fn   err_t fill_up_inventory(object_t* object)
  * \brief Fonction qui ajoute un objet dans l inventaire
  * \param[in] object est l'objet qui sera placé dans l'inventaire
  * \return KO_state si l'inventaire est rempli ou OK_state
  */
 err_t fill_up_inventory(object_t* object) {

    if(Inventaire->nb_objects >= 30){ /*si c est plein, on renvoie 0  car on peut pas faire un overbook*/
           return KO_state;
    }
    Inventaire->object[Inventaire->nb_objects] = object;
    Inventaire->nb_objects++;
    return OK_state;
 }
 /**
  * \fn  err_t deleteFrom_inventaire(int indice)
  * \brief Fonction qui supprime un objet de l inventaire
  * \param[in] indice est l'indice de l'objet à supprimer
  * \return OK_state si c est un objet qui existe, sinon KO_state
*/
 err_t deleteFrom_inventaire(int indice){

    if(indice<30 && indice>0){
      int i;

      delete_object(&Inventaire->object[indice-1]);

      for( i = (indice-1); i < Inventaire->nb_objects-1; i++){
          Inventaire->object[i]=Inventaire->object[i+1];
      }
      Inventaire->nb_objects--;
      return OK_state;
    }else{
      return KO_state;
    }

 }
 /**
  * \fn    int est_mana(object_t* obj)
  * \brief Fonction qui retourne 1 ou 0 si l'objet est une potion mana
  * \param[in] obj est l'objet pris en compte
*/
int est_mana(object_t* obj){
  return obj->type_object == potion && (obj->state_object <= 1);
}
/**
 * \fn  int est_cure(object_t* obj)
 * \brief Fonction qui retourne 1 ou 0 si l'objet est une potion de cure
 * \param[in] obj est l'objet pris en compte
*/
int est_cure(object_t* obj){
  return obj->type_object == potion && (obj->state_object <= 3);
}
/**
 * \fn  int est_phoenix(object_t* obj)
 * \brief Fonction qui retourne 1 ou 0 si l'objet est une potion qui redonne la vie à un personnage de l'équipe
 * \param[in] obj est l'objet pris en compte
*/
int est_phoenix(object_t* obj){
  return obj->type_object == potion && (obj->state_object <= 5);
}
