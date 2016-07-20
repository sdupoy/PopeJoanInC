// Mini projet Langage C
// Nain Jaune
// Dupoy Simon
// Benoit Feuillet
// Version finale 21/01

#include <stdio.h>
#include <stdlib.h>

#include "FonctionsJouer.h"

void Jouer(){
	int choix, nb, nbCartes;
	Participants parts = NULL;
	effacerEcran;
	afficherMenu();
	choix = saisirChoix();
	switch(choix){
		case 1 :
			effacerEcran;
			nb = nbJoueurs();
			nbCartes = nombreCarte(nb);
			parts = initialiserPartie(nb);
			break ;		
		case 2 :
			effacerEcran;
			printf("Chargement...\n");
			printf("Fonction en cours d'implémentation\n");
			quitter();
			return ;
			break ;
		case 3 :
			effacerEcran;
			printf("Affichage des règles\n");
			afficherRegles();
			printf("Appuyer sur Entrée pour lancer une partie\n");
			while(getchar()!='\n');
			effacerEcran;
			nb = nbJoueurs();
			nbCartes = nombreCarte(nb);
			parts = initialiserPartie(nb);
			break;
		case 4 :
			effacerEcran;
			quitter();
			return ;
			break ;
		default :
			effacerEcran;
			printf("Erreur dans le choix...\n");
			printf("Jeu terminé.");
			quitter();
			return ;
			break ;
	}
	effacerEcran;
	miseJetons(parts);
	sleep(4);
	distribuerCartes(parts, nbCartes);
	printf("Le jeu a été mélangé. Distribution...\n");
	sleep(5);
	effacerEcran;
	afficherMains(parts);
	sleep(5);
	effacerEcran;
	printf("La manche commence ...\n");
	jouerUneManche(parts,nb);
}
