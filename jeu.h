#ifndef JEUHEADER
#define JEUHEADER

#include <echiquier.h>

/**
 * @brief Fonction utilisée dans la fonction acquisitioncoordonnées(ex si l'utilisateur rentre A5 dans un echiquier 6
 * par 6 la fonction permettra d'obtenir 1 : 0 )
 *
 * @param abscisse --> abscisse de l'échiquier (colonne)
 * @param ordonnee --> ordonnée de l'échiquier (ligne)
 * @param taillechiquier --> taaille de l'échiquier
 */
void switchbase(int* abscisse, int* ordonnee, int taillechiquier);

/**
 * @brief Permet d'actualiser l'echiquier et de déplacer une pièce si le mouvement est possible
 *
 * @param coordonneedepart --> Coordonnée de départ entrée par l'utilisateur
 * @param coordonneearriver --> Coordonnée d'arriver entrée par l'utilisateur
 * @param echiquier -->  tableau de structure de pièces
 */
void Mouvement(Coord coordonneedepart, Coord coordonneearriver, Piece** echiquier);

/**
 * @brief Verification des mouvements d'un Fou
 *
 * @param coordonneedepart --> Coordonnée de départ entrée par l'utilisateur
 * @param coordonneearriver--> Coordonnée d'arriver entrée par l'utilisateur
 * @param echiquier -->  tableau de structure de pièces
 * @return Bool--> indique si le coup est possible ou non
 */
Bool FouVerification(Coord coordonneedepart, Coord coordonneearriver, Piece** echiquier);

/**
 * @brief Fonction se répettant dans FouVerification
 *
 * @param i --> entier d'indentation
 * @param y --> ligne d'arrivée
 * @param y0 --> ligne de départ
 * @param x --> colonne d'arrivée
 * @param x0--> colonne de départ
 * @param echiquier--> tableau de structure de pièces
 * @return Bool --> indique si le coup est possible ou non
 */
Bool VerificationFou(int i, int y, int y0, int x, int x0, Piece** echiquier);

/**
 * @brief  Verification des mouvements d'un cavalier
 *
 * @param coordonneedepart --> Coordonnée de départ entrée par l'utilisateur
 * @param coordonneearriver --> Coordonnée d'arrivée entrée par l'utilisateur
 * @param echiquier -->  tableau de structure de pièces
 * @return Bool--> indique si le coup est possible ou non
 */
Bool CavalierVerification(Coord coordonneedepart, Coord coordonneearriver, Piece** echiquier);

/**
 * @brief Verification des mouvements d'une tour
 *
 * @param coordonneedepart --> Coordonnée de départ entrée par l'utilisateur
 * @param coordonneearriver --> Coordonnée d'arrivée entrée par l'utilisateur
 * @param echiquier -->  tableau de structure de pièces
 * @return Bool --> indique si le coup est possible ou non
 */
Bool TourVerification(Coord coordonneedepart, Coord coordonneearriver, Piece** echiquier);

/**
 * @brief Verification des mouvements d'un Pion
 *
 * @param coordonneedepart --> Coordonnée de départ entrée par l'utilisateur
 * @param coordonneearriver --> Coordonnée d'arrivée entrée par l'utilisateur
 * @param taille --> taille de l'échiquier
 * @param echiquier -->  tableau de structure de pièces
 * @return Bool --> indique si le coup est possible ou non

 */
Bool PionVerification(Coord coordonneedepart, Coord coordonneearriver, int taille, Piece** echiquier);

/**
 * @brief Verification des mouvements d'un Roi
 *
 * @param coordonneedepart --> Coordonnée de départ entrée par l'utilisateur
 * @param coordonneearriver --> Coordonnée d'arrivée entrée par l'utilisateur
 * @param echiquier -->  tableau de structure de pièces
 * @return Bool --> indique si le coup est possible ou non
 */
Bool RoiVerification(Coord coordonneedepart, Coord coordonneearriver, Piece** echiquier);

/**
 * @brief Verification des mouvements d'une Reine
 *
 * @param coordonneedepart --> Coordonnée de départ entrée par l'utilisateur
 * @param coordonneearriver--> Coordonnée d'arrivée entrée par l'utilisateur
 * @param echiquier -->  tableau de structure de pièces
 * @return Bool --> indique si le coup est possible ou non
 */
Bool DameVerification(Coord coordonneedepart, Coord coordonneearriver, Piece** echiquier);

/**
 * @brief Donne la position du Roi à l'instant t
 *
 * @param CoordonneeRoi --> Coordonnée du roi à modifier après mouvement
 * @param Roi --> Couleur du Roi en question
 * @param taille--> taille de l'échiquier (6 x 6 par exemple)
 * @param echiquier --> Structure de Piece
 */
void PositionRoi(Coord CoordonneeRoi, Couleur Roi, int taille, Piece** echiquier);

/**
 * @brief Fonction utile pour la fonction EchecRoi, regroupe les mouvements de toutes les pièces
 *
 * @param taille --> taille de l'échiquier (6 x 6 par exemple)
 * @param coordonnee --> Coordonnée de la case actuelle où l'on veut appliquer la fonction
 * @param coordonneeRoi--> Coordonnées aux quelles on vérifie si le roi peut être en échec
 * @param echiquier -->  Structure de Piece
 * @return Bool --> Indique si le roi est en echec par la pièce concernée
 */
Bool MouvementPieceEchec(int taille, Coord coordonnee, Coord coordonneeRoi, Piece** echiquier);

/**
 * @brief Fonction qui indique si le roi d'une couleur (NOIR ou BLANC) est en échec à un moment donné
 *
 * @param taille --> taille de l'échiquier (6 x 6 par exemple)
 * @param CoordonneeRoi --> Coordonnées du Roi dont on vérifie l'echec potentiel
 * @param echiquier -->  Structure de Piece
 * @param MiseEnEchec --> Couleur du Roi mis en échec potentiel
 * @param MetEnEchec --> Couleur de la pièce qui met en échec
 * @param tailleTabtmp --> Tailledu Tableau qui met en echec le roi
 * @return Coord* --> tableau de coordonnées de chaque pièce mettant en échec le roi
 */
Coord* EchecRoi(int taille, Coord CoordonneeRoi, Piece** echiquier, Couleur MiseEnEchec, Couleur MetEnEchec, int* tailleTabtmp);

/**
 * @brief Fonction servant dans EchecEtMat et dans le main -->indique si le Roi est bloqué à  sa place ou peut se déplacer en cas d'echec
 *
 * @param taille --> taille de l'échiquier (6 x 6 par exemple)
 * @param CoordonneRoi  --> Coordonnées du Roi qui est en echec
 * @param MiseEnEchec--> Couleur du Roi mis en échec
 * @param MetEnEchec --> Couleur de la pièce qui met en échec
 * @param echiquier -->  Structure de Piece
 * @return Bool --> Ressort Vrai si le roi peut se déplacer, l'inverse sinon
 */
Bool RoiMouvementElementaire(int taille, Coord CoordonneRoi, Couleur MiseEnEchec, Couleur MetEnEchec, Piece** echiquier);

/**
 * @brief Fonction utile dans EchecEtMat, sert à  savoir si oui ou non le Roi peut être protéger par ses coéquipiers
 *
 * @param taille --> taille de l'échiquier (6 x 6 par exemple)
 * @param echiquier  -->  Structure de Piece
 * @param coordonneePieceMetenEchec --> Piece qui met en échèque le roi
 * @param MetEnEchec --> Couleur de la pièce qui met en échec
 * @param MisenEchec --> Couleur du Roi mis en échec
 * @param coordonneeRoi --> Coordonnées du Roi qui est en echec
 * @return Bool --> ressort vrai si le contre est possible
 */
Bool EchecEtMatContre(int taille, Piece** echiquier, Coord coordonneePieceMetenEchec, Couleur MetEnEchec, Couleur MisenEchec, Coord coordonneeRoi);

/**
 * @brief Fonction primordiale pour la boucle de jeu
 *
 * @param taille  --> taille de l'échiquier (6 x 6 par exemple)
 * @param CoordonneRoi --> Coordonnées du Roi qui est en echec
 * @param MiseEnEchec --> Couleur du Roi mis en échec
 * @param MetEnEchec  --> Couleur du Roi qui met en échec
 * @param echiquier -->  Structure de Piece
 * @return Bool --> ressort VRAI si le roi est en echec et mat
 */
Bool EchecEtMat(int taille, Coord CoordonneRoi, Couleur MiseEnEchec, Couleur MetEnEchec, Piece** echiquier);

/**
 * @brief free des tableaux à deux dimensions mallocer
 *
 * @param tab --> tableau de deux dimension d'entiers
 * @param tailleTab--> taille du tableau (première dimension)
 */
void freeTab(Coord** tab, int tailleTab);

#endif
