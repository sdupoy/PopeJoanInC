#ifndef CARD_H
#define CARD_H

#define HEART "\E[91m\u2665\E[0m"
#define DIAMOND "\E[91m\u2666\E[0m"
#define CLUB "\u2663"
#define SPADE "\u2660"
#define JACK "\u265E"
#define QUEEN "\u265B"
#define KING "\u265A"
#define moveto(x,y) printf("\033[%d;%dH",y,x)

// Couleurs des cartes
typedef enum{Coeur,Carreau,Trefle,Pique} Couleur;

// Valeur des cartes (jeu de 52 cartes)
typedef enum{As,Deux,Trois,Quatre,Cinq,Six,Sept,Huit,Neuf,Dix,Valet,Dame,Roi} Valeur;

// Définition d'une carte
typedef struct{
	Valeur valeur;
	Couleur couleur;
} Carte;

/** Fonction qui prend la valeur d'une carte et renvoie un entier
 * correspondant.
 * param:+ valeur la valeur de la carte
 * return: un entier entre 1 (As) et 13 (Roi)
 */
int Carte_valeur(Valeur valeur);

/** Fonction qui prend la couleur d'une carte et renvoie une chaine
 * de caractères correspondant au symbole de la couleur.
 * param:+ couleur la couleur de la carte
 * return: le symbole du coeur, du carreau, du trèfle ou du pique
 */
char* Carte_couleur(Couleur couleur);

/** Fonction qui crée une carte à partir d'une valeur et d'une couleur.
 * param:+ valeur la valeur de la carte à créer
 * param:+ couleur la couleur de la carte à créer
 * return: une Carte correspondant à la couleur et à la valeur fournie
 */
Carte Carte_creer(Valeur valeur, Couleur couleur);

/** Fonction qui transforme une chaine de caractères en une Couleur.
 * param:+ couleur une chaine de caractères "C", "K", "T" et "P" pour
 * respectivement, Coeur, Carreau, Trefle et Pique.
 * return: la Couleur correspondante
 */
Couleur Carte_rcouleur(char* couleur);

/** Fonction qui transforme une chaine de caractères en une Valeur.
 * param:+ valeur une chaine de caractères correspondant à la valeur d'une carte:
 * les valeurs [2-10], "A", "J", "Q", "K" correspondent respectivement aux cartes
 * dont la valeur est entre 2 et 10, à l'As, au Valet, à la Dame et au Roi.
 * return: la Valeur correspondante
 */
Valeur Carte_rvaleur(char* valeur);

/** Fonction qui teste si une carte est inférieure à une autre carte 
 * param:+ c1 une Carte
 * param:+ c2 une Carte
 * return: 1 si c1 est inférieure à c2, 0 sinon
 */
int Carte_inferieure(Carte c1, Carte c2);

/** Fonction qui teste l'égalité de deux cartes
 * param:+ c1 une Carte
 * param:+ c2 une Carte
 * return: 1 si c1 est égale à c2, 0 sinon
 */
int Carte_egale(Carte c1, Carte c2);

/** Fonction qui teste si deux cartes se suivent. Le cas particulier du Roi est
 * pris en compte : toute carte proposée après un Roi permet de former une suite.
 * param:+ c1 une Carte
 * param:+ c2 une Carte
 * return: 1 si c1 puis c2 forment une suite, 0 sinon
 */
int Carte_estUneSuite(Carte c1, Carte c2);

/** Fonction d'affichage d'une Carte
 * param:+ carte une Carte
 * return: une chaine de caractères contenant la valeur et la couleur de la carte
 */
char* Carte_affiche(Carte carte);

#endif
