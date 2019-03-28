/**
 *
 \brief Structure des quêtes: coordonnées du pnj, de l'objectif, phrases de début/fin, xp, statut, nom de l'image d'objectif
*/
typedef struct quete_s{
  int pnj_x; /*!< Abscisse du pnj */
  int pnj_y; /*!< Ordonnée du pnj */
  char phrase_debut[400]; /*!< Chaine de caractères pour la phrase du début */
  char phrase_fin[400]; /*!< Chaine de caractères pour la phrase de fin */
  char pnj_nom[30]; /*!< Chaine de caractères le nom du pnj */
  int statut; /*!< Satut (0 non commencé, 1 commencée, 2 objectif récupéré, 3 objectif raporté au pnj) */
  int but_x; /*!< Abscisse de l'objectif */
  int but_y; /*!< Ordonnée de l'objectif */
  int xp; /*!< Expérience raportée */
  char nom_img[30]; /*!< Nom de l'image de l'objectif */
  char pnj_img[30]; /*!< Nom de l'image du pnj */

}quete_t;

quete_t * quetes[100]; /*!< Tableau de pointeurs de structures quêtes */
void afficher_quetes();
void charger_quetes();
