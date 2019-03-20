#include <stdlib.h>
#include <commun.h>

int entier_aleatoire(int min, int max, int*alea){
	if(min >= max)
		return 1;
	*alea = min+rand()%(max-min);
	return 0;
}


/**
 * \fn string creer_string(string string_param)
 * \brief Creer une chaine de caractere dynamiquement 
 * \param[in] chaine de caractere a passer en parametre "exemple de chaine"
 * \return Un string (char*)
 */

const err_t OK = 1;
const err_t KO = 0;

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

int supprimer_string(string *string_param){

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