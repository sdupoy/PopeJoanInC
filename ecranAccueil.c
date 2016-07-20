// Mini projet Langage C
// Nain Jaune
// Dupoy Simon
// Benoit Feuillet
// Version finale 21/01

#include <stdio.h>
#define effacerEcran system("clear")

void ecranAccueil(){
	effacerEcran;
	printf("\n\n\n\t\t\tBonjour :)\n\n\tBienvenue dans le jeu du Nain Jaune\n\n\n");
	printf("\tSimon Dupoy\t\t Benoît Feuillet\n\n\n\n");
	printf("\tAppuyez sur Entrée pour continuer");
	while(getchar()!='\n'){};
	
}
