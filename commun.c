#include <stdlib.h>
#include <commun.h>

const err_t OK = 1;
const err_t KO = 0;

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
 * \fn string creer_string(string string_param)
 * \brief Creer une chaine de caractere dynamiquement
 * \param[in] chaine de caractere a passer en parametre "exemple de chaine"
 * \return Un string (char*)
 */
string creer_string(string string_param){

	/* on alloue en memoire les caracteres de la chaine +1*/
	string new_string = malloc((sizeof(char)*strlen(string_param))+1);

	int i;
	for(i = 0; i < strlen(string_param);i++){
		/*a chaque case on met le caractere qui correspond*/
		new_string[i] = string_param[i];
	}

	/*On met le marqueur de fin de chaine*/
	new_string[i] = '\0';

	return new_string;
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
		return OK;
	}
	else{
		return KO;
	}
}

/**
 * \fn void modifier_string(string *string_old, string string_new)
 * \brief Modifie un string
 * \param[in] pointeur de pointeur chaine de caractere (string* AKA char**)
 * \param[in] la nouvelle chaine de caractere
 */

void modifier_string(string *string_old, string string_new){
	supprimer_string(string_old); /*on free l'ancienne chaine*/
	*string_old = creer_string(string_new); /*on alloue la nouvelle chaine*/
}

void viderBuffer(){

    int c = 0;

    while (c != '\n' && c != EOF)
        c = getchar();
}
int lire(char *chaine, int longueur){

    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL){

        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL){

            *positionEntree = '\0';
        }else{

            viderBuffer();
			}

        return 1;

    }else{

        viderBuffer();
        return 0;
    }
}
