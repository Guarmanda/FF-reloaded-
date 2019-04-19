/**
 * \file      commun.c
 * \author    Nathalie Karman, Alexandre Papot
 * \version   1.0
 * \date     Mars 2019
 * \brief    Module qui sert de boîte à outils pour tout le projet
 */

#include <commun.h>

const err_t OK_state = 1;
const err_t KO_state = 0;

/**
 * \fn entier_aleatoire(int min, int max)
 * \brief Renvoie un entier aléatoire borné par deux valeurs
 * \param[in] int, valeur minimum de l'entier aléatoire (borne min)
 * \param[in] int, valeur maximum de l'entier aléatoire (borne max)
 * \return l'entier aléatoire ou l'entier représenté par ERR_RAND (-110)
*/
int entier_aleatoire(int min, int max){
	if(min >= max){
		return ERR_RAND;	/*retourne -110 si erreur */
	}
  return min + rand() % ( max-min );

}

/**
 * \fn string creer_string(string* chaine_a_affecter, string chaine_a_copier)
 * \brief Creer une chaine de caractere dynamiquement
 * \param[in]	chaine à allouer et affecter
 * \param[in] chaine de caractere à copier selon sa taille
 * \return un code d erreur ou OK_state
 */
err_t creer_string(string* chaine_a_affecter, string chaine_a_copier){
	/* on alloue en memoire les caracteres de la chaine +1*/
	*chaine_a_affecter= malloc(sizeof(char)*strlen(chaine_a_copier)+1);
	if(*chaine_a_affecter != NULL){

		strcpy(*chaine_a_affecter,chaine_a_copier);

		return OK_state;
	}
	return ERR_DEB_MEMOIRE;
}

/**
* \fn err_t supprimer_string(string *string_param)
* \brief Supprime une chaine de caractere
* \param[in] pointeur sur chaine de caractere  char * (le type \a string = char *)
* \return OK_state ou KO_state (1/0)
*/

err_t supprimer_string(string *string_param){

	if(*string_param != NULL){ /*Si le pointeur pointe sur une zone memoire en cours d'occupation*/
		free(*string_param);
		*string_param = NULL;
		return OK_state;
	}
	else{
		return KO_state;
	}
}


/**
 * \fn void viderBuffer(void)
 * \brief vide le buffer de manière générique
*/
void viderBuffer(){	/*si depassement  */

    int temp = 0;

    while (temp != '\n' && temp != EOF)
        temp = getchar();	/*récupère le reste du texte entré (clavier) jusqu à la fin*/
}
/**
 * \fn void lire(char *chaine, int longueur)
 * \brief Fonction qui fait une saisie de manière sécure en faisant appel à la fonction \a viderBuffer()
 * \param[in] chaine la chaîne de caractère qui sera allouée
 * \param[in] longueur est la longueur limite que la chaine peut avoir
 * \return 1 si l'utilisateur n'a pas dépassé la taille maximum, sinon 0
*/
int lire(char *chaine, int longueur){	/*pour lecture correcte via clavier*/

    char *cherche_Enter = NULL;

    if ( fgets(chaine, longueur, stdin) != NULL ){	/*fgets evite le debordement de mémoire*/

        cherche_Enter = strchr(chaine, '\n');	/*recherche la touche [entree]*/
        if (cherche_Enter != NULL){

            *cherche_Enter = '\0';	/*fin de la chaîne */
        }else{	/*si l utilisateur a dépassé la taille de la chaine par défaut on va vider les caractères qui se trouvent dans le buffer*/

            viderBuffer();
			}
        return 1;
    }else{

        viderBuffer();
        return 0;
    }
}
/**
 * \fn void clear_screen(void)
 * \brief pour l affichage, on regarde l'OS et la fonction fait le traitement
*/
void clear_screen(){
  #ifdef WINDOWS
     system ( "CLS" );
  #else
     system ( "clear" );
  #endif
 }
