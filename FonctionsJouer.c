// Mini projet Langage C
// Nain Jaune
// Dupoy Simon
// Benoit Feuillet
// Version finale 21/01

#define TAILLE 10
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "FonctionsJouer.h"


void afficherMenu(){
	printf("\n\t\t\tMenu\n\n");
	printf("\t1 - Jouer une partie \n");
	printf("\t2 - Charger une partie \n");
	printf("\t3 - Afficher les règles \n");
	printf("\t4 - Quitter le jeu \n\n");
}

void afficherRegles(){
	printf("Le but du jeu\nUne manche est gagnée par le joueur qui se débarrasse de toutes ses cartes en premier.\nDes mises sont faites en début de manche grâce à des jetons sur des cartes spécifiques (7 de Carreau, 10 de Carreau, Valet de Trèfle, Dame de Pique et Roi de Coeur). Ces cartes spécifiques  rapportent un certain nombre de jetons. Le joueur qui ne sera plus capable de miser en début de manche sera éliminé.\n\nLe déroulement d'une manche\nLors d'une manche, un joueur tiré au sort commence à se défausser de ses cartes en formant une suite. Lorsqu'il ne peut plus continuer sa suite, c'est au joueur situé après lui de poursuivre la suite, et ainsi de suite. Si aucun joueur ne parvient à se défausser, la défausse est réinitialisée et la parole revient au joueur qui s'est défaussé en dernier.\n");
}


int saisirChoix(){
	int choix = 0;
	char saisie[10];
	do{
	    printf("Que souhaitez-vous faire? ");
	    fgets(saisie,10,stdin); // Saisie sécurisée
		sscanf(saisie,"%d ",&choix);
	    if(choix!=1 && choix!= 2 && choix!=3 && choix!=4){
	    	// Informer l'utilisateur de son mauvais choix
	        printf("Mauvaise saisie ! Merci de vous appliquer !\n");
	    }
	}while(choix!=1 && choix!= 2 && choix!=3 && choix!=4);
	return choix;
}

int nbJoueurs(){
	int nb = 0;
	char saisie[10];
	do{
		printf("RAPPEL : Vous devez être entre 3 et 8 joueurs pour jouer.\n");
		printf("Combien de joueurs sont présents pour cette partie? ");
		fgets(saisie,10,stdin); // Saisie sécurisée
		sscanf(saisie,"%d ",&nb);
		if(nb<3 || nb>8){ // On veut un nombre de joueurs correct
	        printf("Mauvaise saisie ! Merci de vous appliquer !\n");
	    }
	}while(nb<3 || nb>8); // On vérifie que le nombre de joueurs est correct
	return nb;
}

int indiceTireAuSort(int nb){
	int premierJoueur=0;
	srand(time(NULL));
	premierJoueur = rand()%nb;
	return premierJoueur;
}

void quitter(){
	printf("\n\n\t\tVous quittez le jeu.\n");
}

Participants initialiserPartie(int nb){
	int i = 0, nbJ = 0, prems = 0;
	char * nomsJoueurs[TAILLE];
	Participants partics = NULL;
	printf("Vous avez lancé une partie pour %d joueurs.\n", nb);
	// On définit le nombre de jetons en fonction du nombre de joueurs
	if(nb<5){
		nbJ = 50; 
	}
	else{
		nbJ = 35;
	}
	// On stocke le nom des joueurs dans un tableau
	for(i=0 ; i<nb ; i++){
		nomsJoueurs[i] = saisirUnNom();
	}
	// On tire au sort le joueur qui commence
	prems = indiceTireAuSort(nb);
	printf("Le Joueur %s commence !!\n", nomsJoueurs[prems]);
	sleep(3);
	// On créé la liste chainée
	for(i=prems ; i<nb ; i++){
		partics = insertTail(partics, nomsJoueurs[i], nbJ, i);
	}
	for(i=0 ; i<prems ; i++){
		partics = insertTail(partics, nomsJoueurs[i], nbJ, i);
	}
	return partics;
}

void miseJetons(Participants parts){
	Joueur * courant = parts;
	printf("Mises :\n\t4 sur le Roi de Coeur\n\t3 sur la Dame de Pique\n\t2 sur le Valet de Trèfle\n\t1 sur le 10 de Carreau\n\t5 sur le Nain Jaune (7 de Carreau)\n");
	while(courant != NULL){
		courant->nbJetons = courant->nbJetons - 15;
		if(courant->nbJetons<0){
			printf("Le joueur %s est éliminé...", courant->nom);
			parts = elimineJoueur(parts, courant->nom); // Si le joueur ne peut pas miser, il est éliminé de la partie
		}
		else{
			printf("Le joueur %s mise... Il lui reste %d jetons.\n", courant->nom, courant->nbJetons);
			}
		courant = courant->JSuivant; 
	}
	printf("\n");
}

Participants elimineJoueur(Participants parts, char * nom){
	if(parts==NULL){ // Impossible d'avoir une liste vide à priori
		printf("Liste vide\n");
		return parts;
		}
	if(!strcmp(nom, parts->nom)){
		Joueur * head;
		head = parts->JSuivant;
		return head;
	}
	Joueur * courant = parts;
	while(courant->JSuivant!=NULL && !strcmp(nom, parts->nom)){
		courant = courant->JSuivant;
		}
	if(courant->JSuivant==NULL) return parts; // le joueur à éliminer n'est pas dans la liste (impossible à priori)
	Joueur * next = (courant->JSuivant)->JSuivant;
	courant->JSuivant = next;
	return parts;
}

void distribuerCartes(Participants parts, int nbC){
	int i;
	Joueur * courant = parts;
	Deck deck;
	Deck_creer(&deck);
	Deck_melanger(&deck);
	Deck_affiche(deck);
	// On distribue le même nombre de cartes à chaque joueur
	while(courant!=NULL){
		for(i=0 ; i<nbC ; i++){
			Carte carte = Deck_prendreCarte(&deck);
			courant->main = distribuerCartesAUnJoueur(&(courant->main), carte);	
		}
		
		courant=courant->JSuivant;
	}
}

int carteEstPresente(MainJoueur main, Carte carte){
	int trouve = 0;
	while(main!=NULL && trouve==0){
		if(Carte_egale(main->carte, carte)){
			trouve=1;
		}
		else{
			main = main->suivant;
		}
	}
	return trouve;
}


MainJoueur retirerCarte(MainJoueur main, Carte carte){
	if(main == NULL){return main;}
	if(Carte_egale((main)->carte, carte)){
		CarteEnMain * Tete;
		Tete = main->suivant;
		main = Tete;
		return main;
	}
	CarteEnMain * temp;
	for(temp=main ; temp->suivant!=NULL && !Carte_egale((temp->suivant)->carte, carte) ; temp = temp->suivant){}
	
	if(temp->suivant==NULL) return main; // Carte pas dans la liste	(impossible car on teste si la carte est présente avant)
	CarteEnMain * Suivant = (temp->suivant)->suivant;
	temp->suivant = Suivant;
	return main;
}
	

void afficherJ(Participants parts){
	if(parts==NULL){
		printf("Pas de joueurs..\n");
	}
	else{
		while(parts != NULL) {
			printf("Le joueur %s a %d jetons.\n", parts->nom, parts->nbJetons);
			parts = parts->JSuivant; 
		}
	}
	printf("\n");
}

void afficherMains(Participants parts){
	while(parts!=NULL){
		MainJoueur tete = parts->main;
		printf("Le joueur %s (%d jetons) avec la main :\n[", parts->nom, parts->nbJetons);
		if(parts->main==NULL){
			printf("La main est vide\n");
			}
		while((parts->main)->suivant!=NULL){
			printf("%s - ", Carte_affiche((parts->main)->carte));
			parts->main = (parts->main)->suivant;
			}
		printf("%s", Carte_affiche((parts->main)->carte));
		printf("]\n\n");
		parts->main = tete;
		parts = parts->JSuivant;
	}
}

int nombreCarte(int nb){
	int res;
	switch(nb){
		case 3 :
			res = 15;
			break ;
		case 4 :
			res = 12;
			break ;
		case 5 :
			res = 9;
			break ;
		case 6 :
			res = 8;
			break ;
		case 7 :
			res = 7;
			break ;
		case 8 :
			res = 6;
			break ;
		default :
			res = 0;
			break ;
	}
	return res;
}

char * saisirUnNom(){
    char saisie[16];
	char * nom = NULL;
	nom = malloc(16*sizeof(char));
	printf("Entrez le nom d'un joueur (15 caractères max) : ");
	fgets(saisie,16,stdin); // Saisie sécurisée
	sscanf(saisie,"%s", nom);
	return nom;
}

Participants insertTail(Participants parts, char * nom, int nbJetons, int indice){
	Joueur * NouvJoueur;
	NouvJoueur = malloc(sizeof(Joueur));
	if(NouvJoueur==NULL){printf("Erreur"); exit(0);}
	NouvJoueur->nom = strdup(nom);
	NouvJoueur->nbJetons = nbJetons;
	NouvJoueur->indiceJoueur = indice;
	NouvJoueur->main = NULL;
	NouvJoueur->JSuivant = NULL;
	if(parts==NULL){
		return NouvJoueur;
		}
	else{
		Joueur * first;
		first = parts;
		while(parts->JSuivant!=NULL){
			parts=parts->JSuivant;
			}
		parts->JSuivant = NouvJoueur;
		return first;
	}
}


MainJoueur distribuerCartesAUnJoueur(MainJoueur * main, Carte carte){
	// On ajoute une carte dans la main d'un joueur
	MainJoueur NouvelleCarte;
	NouvelleCarte = malloc(sizeof(CarteEnMain));
	if(NouvelleCarte==NULL){printf("Erreur"); exit(0);}
	NouvelleCarte->carte = carte;
	if(* main==NULL){
		NouvelleCarte->suivant = NULL;
		* main = NouvelleCarte;
		return * main;
	}
	else{
		NouvelleCarte->suivant = * main;
		* main = NouvelleCarte;
		return * main;
	}
}

void afficheUneMain(Joueur * joueur){
		MainJoueur tete = joueur->main;
		printf("Le joueur %s (%d jetons) avec la main :\n[", joueur->nom, joueur->nbJetons);
		if(joueur->main==NULL){
			printf("La main est vide\n");
			return ;
			}
		while((joueur->main)->suivant!=NULL){
			printf("%s - ", Carte_affiche((joueur->main)->carte));
			joueur->main = (joueur->main)->suivant;
			}
		printf("%s", Carte_affiche((joueur->main)->carte));
		printf("]\n");
		joueur->main = tete;
}

int carteEstSpeciale(Carte carte){
	// On teste si la carte est spéciale
	char Vtemp[3], Ctemp;
	Carte RoiCoeur, DamePique, ValetTrefle, DixCarreau, SeptCarreau;
	Vtemp[0]='K';
	Vtemp[1]='\0';
	Ctemp='C';
	RoiCoeur = Carte_creer( Carte_rvaleur(Vtemp), Carte_rcouleur(&Ctemp));
	Vtemp[0]='Q';
	Vtemp[1]='\0';
	Ctemp='P';
	DamePique = Carte_creer( Carte_rvaleur(Vtemp), Carte_rcouleur(&Ctemp));
	Vtemp[0]='J';
	Vtemp[1]='\0';
	Ctemp='T';
	ValetTrefle = Carte_creer( Carte_rvaleur(Vtemp), Carte_rcouleur(&Ctemp));
	Vtemp[0]='1';
	Vtemp[1]='0';
	Vtemp[2]='\0';
	Ctemp='K';
	DixCarreau = Carte_creer( Carte_rvaleur(Vtemp), Carte_rcouleur(&Ctemp));
	Vtemp[0]='7';
	Vtemp[1]='\0';
	Ctemp='K';
	SeptCarreau = Carte_creer( Carte_rvaleur(Vtemp), Carte_rcouleur(&Ctemp));
	if(Carte_egale(RoiCoeur, carte) || Carte_egale(DamePique, carte) || Carte_egale(ValetTrefle, carte) || Carte_egale(DixCarreau, carte) || Carte_egale(SeptCarreau, carte)){
		return 1;
	}
	else{
		return 0;
	}
}


void FaireLesGains(Carte cJouee, Joueur * joueur, int nb){
	// On calcule les gains en fonction de la carte spéciale
    int gain=0;
    char Vtemp[3], Ctemp;
	Carte RoiCoeur, DamePique, ValetTrefle, DixCarreau, SeptCarreau;
	Vtemp[0]='K';
	Vtemp[1]='\0';
	Ctemp='C';
	RoiCoeur = Carte_creer( Carte_rvaleur(Vtemp), Carte_rcouleur(&Ctemp));
	Vtemp[0]='Q';
	Vtemp[1]='\0';
	Ctemp='P';
	DamePique = Carte_creer( Carte_rvaleur(Vtemp), Carte_rcouleur(&Ctemp));
	Vtemp[0]='J';
	Vtemp[1]='\0';
	Ctemp='T';
	ValetTrefle = Carte_creer( Carte_rvaleur(Vtemp), Carte_rcouleur(&Ctemp));
	Vtemp[0]='1';
	Vtemp[1]='0';
	Vtemp[2]='\0';
	Ctemp='K';
	DixCarreau = Carte_creer( Carte_rvaleur(Vtemp), Carte_rcouleur(&Ctemp));
	Vtemp[0]='7';
	Vtemp[1]='\0';
	Ctemp='K';
	SeptCarreau = Carte_creer( Carte_rvaleur(Vtemp), Carte_rcouleur(&Ctemp));
	printf("Joli ! Cette carte rapporte des jetons !\n");
	if(Carte_egale(RoiCoeur, cJouee)==1){
	    gain = nb*4;
	    printf("Vous gagnez %d jetons !\n", gain );
	}
    else if(Carte_egale(DamePique, cJouee)==1){
        gain = nb*3;
	    printf("Vous gagnez %d jetons !\n", gain);
	}
	else if(Carte_egale(ValetTrefle, cJouee)==1){
	    gain = nb*2;
	    printf("Vous gagnez %d jetons !\n", gain );
	}
	else if(Carte_egale(DixCarreau, cJouee)==1){
	    gain = nb;
	    printf("Vous gagnez %d jetons !\n", gain );
	}
	else if(Carte_egale(SeptCarreau, cJouee)==1){
	    gain = nb*5;
	    printf("Vous gagnez %d jetons !\n", gain );
	}
	else{
	    printf("Heu... Vous êtes sur qu'il n'y a pas un souci quelque part?\n");
	}
	joueur->nbJetons = joueur->nbJetons+gain;
	printf("Vous en possédez maintenant %d\n", joueur->nbJetons);
}


int nbCartesJoueur(Joueur * joueur){
	// On calcule le nombre de cartes dans la main d'un joueur
    int resultat=0;
    MainJoueur temp=joueur->main;
    while(temp!=NULL){
        resultat++;
        temp=temp->suivant;
    }
    return resultat;
}


// Ne marche pas lors de la mise en place dans le programme!
void sauvegarde(Participants parts){
    Joueur * Tete = parts;
    FILE *pf;
    pf=fopen("save.txt","w");
    if(pf==NULL){
        printf("ERRREUR!\n");
    }
    do{
        fprintf(pf,"%d %s %d\n",parts->indiceJoueur, parts->nom, parts->nbJetons);
        while(parts->main!=NULL){
            fprintf(pf,"%d%s",Carte_valeur(parts->main->carte.valeur), Carte_couleur(parts->main->carte.couleur));
            parts->main=(parts->main)->suivant;
        }
        parts=parts->JSuivant;
    }while(parts->JSuivant!=NULL);
    fclose(pf);
    parts=Tete;
}


void trierMain(MainJoueur main){
    int i = 15;
    CarteEnMain * Tete = main;
    MainJoueur temp1=main;
    Carte Mini = main->carte;
    // On effectue plusieurs fois le tri car il n'est que partiellement efficace
    while(i>0){
        while(temp1!=NULL){
            if(Carte_inferieure((*temp1).carte, Mini)){
                Mini = temp1->carte;
                temp1->carte = Tete->carte;
                Tete->carte = Mini;
                trierMain(Tete->suivant);
            }
            else{
                temp1=temp1->suivant;
            }
        }
       i--;
    }

}


Participants modifierTete(Participants parts){
	// On modifie le premier (et dernier) joueur de la liste, en décalant les joueurs d'un cran
    Joueur * joueurTempo = parts;
    parts = parts->JSuivant;
    Joueur * NouvelleTete = parts;
    while(parts->JSuivant!=NULL){
        parts=parts->JSuivant;
    }
    parts->JSuivant = joueurTempo;
    joueurTempo->JSuivant = NULL;
    return NouvelleTete;

}


int nombreJoueurs(Participants parts){
	// On calcule le nombre de joueurs dans la liste
	int resultat=0;
	while(parts!=NULL){
		resultat++;
		parts=parts->JSuivant;
	}
	return resultat;	
}

void viderCartes(Participants parts){
	// On vide les mains de chaque joueur
	while(parts!=NULL){
		parts->main = NULL;
		parts=parts->JSuivant;
	}
}

