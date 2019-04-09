#include <commun.h>

const err_t OK_state = 1;
const err_t KO_state = 0;

/**
 * \fn entier_aleatoire(int min, int max)
 * \brief Renvoie un entier aléatoire borné par deux valeurs
 * \param[in] int, valeur minimum de l'entier aléatoire (borne min)
 * \param[in] int, valeur maximum de l'entier aléatoire (borne max)
 * \return (int) ou ERR_RAND (-110)
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
 * \return un code d erreur ou de validation
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
* \fn int supprimer_string(string *string_param)
* \brief Supprime une chaine de caractere
* \param[in] pointeur de pointeur chaine de caractere (string* AKA char**)
* \return err_t OK/KO (1/0)
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
 * \fn void modifier_string(string *string_old, string string_new)
 * \brief Modifie un string
 * \param[in] pointeur de pointeur chaine de caractere (string* AKA char**)
 * \param[in] la nouvelle chaine de caractere
 */
/*
 on free l'ancienne chaine
void modifier_string(string *string_old, string string_new){
	supprimer_string(string_old);
	*string_old = creer_string(&string_new,);
}
*/

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
 * \brief pour lecture correcte via clavier en faisant appel à la fonction viderBuffer()
 * \param[in] pointeur sur une chaine de caractere
 * \param[in] longueur de la chaine qui servira à limiter la saisie de l'utilisateur
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
