#ifndef DECK_H
#define DECK_H
#include "card.h"

/** Un deck représente un jeu de carte complet.
 * Le deck a été représenté sous la forme d'une pile de 52 cartes,
 * l'indice du sommet correspond à l'indice de la première carte (visible)
 * de la pile.
 */
typedef struct{
	int indiceSommet;
	Carte cartes[52];
} Deck;

/** Procédure qui crée le contenu d'un nouveau jeu de cartes
 * param:+/- deck le jeu de cartes à créer
 * return: void
 */
void Deck_creer(Deck* deck);

/** Procédure qui mélange le contenu d'un jeu de cartes
 * param:+/- deck le jeu à mélanger
 * return: void
 */
void Deck_melanger(Deck* deck);

/** Fonction qui 'tire' la carte située sur le dessus du tas. Le jeu de cartes
 * contient ainsi une carte de moins.
 * param:+/- deck le jeu de cartes
 * return: la première carte du tas, une erreur est levée si le jeu de cartes est vide
 */
Carte Deck_prendreCarte(Deck* deck);

/** Procédure qui ajoute une carte à un deck
 * param:+/- deck le jeu de cartes
 * param:+ carte la carte que l'on veut ajouter au jeu
 * return: void
 */
void Deck_ajouterCarte(Deck* deck, Carte carte);

/** Procédure qui affiche le deck sous la forme [carte1, carte2, ..., carte52]
 * param:+ deck le jeu de cartes
 * return: void
 */
void Deck_affiche(Deck deck);

/** Fonction qui renvoie la première carte du jeu de cartes sans modifier ce 
 * dernier.
 * param:+ deck le jeu de cartes
 * return: la première carte du tas, une erreur est levée si le jeu de cartes est vide
 */
Carte Deck_premiereCarte(Deck deck);

/** Fonction qui renvoie l'indice du sommet du deck
 * param:+ deck le jeu de cartes
 * return: l'indice du sommet du deck; -1 correspond à un deck vide
 */
int Deck_sommet(Deck deck);

/** Fonction qui teste si un deck est vide
 * param:+ deck le jeu de cartes
 * return: 1 si deck ne contient aucune carte, 0 sinon.
 */
int Deck_vide(Deck deck);

#endif
