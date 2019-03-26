

int map[1000][1000]; /*!< Matrice de la map, contenant les valeurs des sprites (0 à 6) */
//les coordonnees du joueur, accessibles de n'importe
float X; /*!< Abscisse du joueur pour usage externe (quêtes, monstres,...) */
float Y; /*!< Ordonnée du joueur pour usage externe */


/*void setRandomMap();*/
void loadMap(char*);
