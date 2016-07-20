// Mini projet Langage C
// Nain Jaune
// Dupoy Simon
// Benoit Feuillet
// Version finale 21/01

#ifndef FONCTIONS_JOUER_H
#define FONCTIONS_JOUER_H

#define effacerEcran system("clear")
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define TAILLE 10
#include "deck.h"
#include "card.h"

typedef struct CarteEnMain{
	Carte carte;
	struct CarteEnMain * suivant;
}CarteEnMain;

typedef CarteEnMain * MainJoueur;

typedef struct Joueur{
	char * nom;
	int nbJetons;
	MainJoueur main;
	int indiceJoueur;
	struct Joueur * JSuivant; 
} Joueur;

typedef Joueur * Participants;


/* Affichage de l'écran d'accueil */
void ecranAccueil();

/* Affichage de l'écran de sortie */
void ecranSortie();

/* Jouer au jeu du Nain Jaune */
void Jouer();

/* Procédure d'affichage du menu */
void afficherMenu();

/* Procédure d'affichage des règles */
void afficherRegles();

/* renvoie le choix (un entier), saisi par l'utilisateur
   \return 1 ou 0
*/
int saisirChoix();

/* renvoie le nombre de joueurs, saisi par l'utilisateur
	\ return un entier entre 3 et 8	 
*/
int nbJoueurs();

/* renvoie un chiffre aléatoire
	\ param +nb : le nombre de joueurs
	\ return un entier entre 0 et nb-1	 
*/
int indiceTireAuSort(int nb);

/* Procédure d'arret du jeu */
void quitter();

/* renvoie la liste chainee de joueurs, initialisée correctement
	\ param +nb : le nombre de joueurs
	\ return le pointeur sur le premier joueur de la liste
*/
Participants initialiserPartie(int nb);

/* réalise les mises 
	\ param +parts : la liste chainee de joueurs
*/
void miseJetons(Participants parts);

/* renvoie la liste chainee de joueurs, avec le joueur éliminé retiré
	\ param +parts : la liste chainee de joueurs
	\ return le pointeur sur le premier joueur de la liste modifiée
*/
Participants elimineJoueur(Participants parts, char * nom);

/* ditribue les cartes aux joueurs
	\ param +parts : la liste chainee de joueurs
*/
void distribuerCartes(Participants parts, int nbC);


/* renvoie 1 si la carte est présente dans la main du joueur, 0 sinon
	\ param +main : la main du joueur à vérifier
	\ param +carte : la carte dont on veut vérifier la présence
	\ return 0 ou 1
*/
int carteEstPresente(MainJoueur main, Carte carte);

/* renvoie la main du joueur, avec une carte rétirée
	\ param +main : la main du joueur
	\ param +carte : la carte que l'on souhaite retirer
	\ return 0 ou 1
*/
MainJoueur retirerCarte(MainJoueur main, Carte carte);

/* affiche le nom et les jetons de tous les joueurs
	\ param +parts : la liste chainee de joueurs
*/
void afficherJ(Participants parts);

/* affiche la main de tous les joueurs
	\ param +parts : la liste chainee de joueurs
*/
void afficherMains(Participants parts);

/* renvoie le nombre de cartes à distribuer
	\ param +nb : le nombre de joueurs
	\ return le nombre de cartes adéquate
*/
int nombreCarte(int nb);

/* renvoie le pointeur sur char d'un nom de joueur
	\ return pointeur sur char
*/
char * saisirUnNom();

/* renvoie le pointeur sur le premier joueur de la liste chainee de joueurs
	\ param +parts : la liste chainee de joueurs
	\ param +nom : le pointeur sur char du nom du joueur à insérer
	\ param +nbJetons : le nombre de jetons du joueur à insérer
	\ return la liste chainée de joueurs avec un joueur inséré en fin de liste
*/
Participants insertTail(Participants parts, char * nom, int nbJetons, int indice);

/* renvoie la main du joueur avec une carte supplémentaire
	\ param +main : le pointeur sur la main du joueur
	\ param +carte : la carte à ajouter à la main
	\ return la main du joueur
*/
MainJoueur distribuerCartesAUnJoueur(MainJoueur * main, Carte carte);


/* affiche la main d'un joueur
	\ param +parts : la liste chainee de joueurs, ici poiteur sur joueur
*/
void afficheUneMain(Joueur * joueur);

/* teste si la carte jouée est une carte qui rapporte des jetons
	\ param +carte : la carte jouée par le joueur
	\ return 0 ou 1
*/
int carteEstSpeciale(Carte carte);

/* donne le nombre de jetons adéquate au joueur qui a joué la carte spéciale 
    \ param +cJouee : la carte jouée (spéciale)
    \ param +joueur : le joueur qui a joué
    \ param +nb : le nombre de joueurs afin d'avoir la mise a créditer
*/
void FaireLesGains(Carte cJouee, Joueur * joueur, int nb);

/* calcule le nombre de cartes dans la main d'un joueur
    \ param +joueur : le joueur en question
    \ return le nombre de cartes
*/
int nbCartesJoueur(Joueur * joueur);

/* calcule le nombre de joueurs (notamment en début de partie, après les mises au cas où certains sont éliminés)
    \ param +parts : la liste de joueurs
    \ return le nombre de joueurs
*/
int nombreJoueurs(Participants parts);

/* modifie le premier joueur de la liste (à la fin d'une manche par exemple
	\ param +parts : la liste de joueurs
    \ return le nouveau "premier" joueur
*/
Participants modifierTete(Participants parts);

/* tri partiel d'une main
	\ param +main : la main à trier
*/
void trierMain(MainJoueur main);


/* Vide la main des joueurs
	\ param +parts : la liste de joueurs 
*/
void viderCartes(Participants parts);

/* sauvegarde une partie à la fin d'un tour (non opérationnel)
	\ param +parts : la liste de joueurs
*/
void sauvegarde(Participants parts);

/* charge une partie précedemment sauvegardée (non opérationnel)
	\ return : la liste de joueurs correctement chargée
*/
Participants charger();

/* Permet de jouer la manche
    \ param +parts : la liste de participants
    \ param +nb : le nombre de joueurs
*/
void jouerUneManche(Participants parts, int nb);


#endif /* FONCTIONS_JOUER_H */
