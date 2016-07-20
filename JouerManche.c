// Mini projet Langage C
// Nain Jaune
// Dupoy Simon
// Benoit Feuillet
// Version finale 21/01

#include <stdio.h>
#include <stdlib.h>

#include "FonctionsJouer.h"

void jouerUneManche(Participants parts, int nb){
	// Variables nécessaires pour la manche
	Carte Defausse;
	Carte carteJouee;
	int affiliationReussie = 0;
	int  passe = 0, aPasse=0;
	int CarteAGain = 0;
	int PremiereDefausse = 1;
	int compteurDErreur = 0;
	int arretManche = 0, arretJeu =0;
	int  nbCartesPrec, nbCartes = 0;
	char clavier[16];
	char saisie[5];
	char valeur[3];
	char couleur[2];
	char choixFinal[16];
	int final = 0;
	int score=9;
	
	// Stocker le premier joueur !
	Joueur * Prems = parts;
	
	while(!arretJeu){
	while(!arretManche){
	    
		if(parts->main!=NULL){
			// On stocke le nombre de cartes avant la défausse
		    nbCartesPrec = nbCartesJoueur(parts);
			do{
				
				effacerEcran;
				///// Choisir une carte à défausser //////
				// On tri la main. En moyenne 5 fois car le tri n'est que partiellement efficace
				// On l'affiche ensuite
		        trierMain(parts->main);
		        trierMain(parts->main);
		        trierMain(parts->main);
		        trierMain(parts->main);
		        trierMain(parts->main);
				afficheUneMain(parts);
				// On gère le cas où la défausse est vide ou réinitialisée
				if(PremiereDefausse){
					printf("La défausse est vide.\n");
				}
				else{
					printf("La défausse contient : %s\n", Carte_affiche(Defausse));
				}
				printf("\n%s, à vous de jouer. Entrer une valeur de carte.\n", parts->nom);
				while(affiliationReussie == 0){ // Tant que la saisie n'est pas validée
					fgets(clavier,16,stdin); // Saisie sécurisée grâce au fgets
	                sscanf(clavier,"%s", saisie);
					if(saisie[0] == '1' && saisie[1]=='0' && (saisie[2]=='C' || saisie[2]=='K' || saisie[2]=='T' || saisie[2]=='P')){ // Cas où la carte est un 10
						strcpy(couleur,&saisie[2]);
						saisie[2]='\0';
						strcpy(valeur, saisie);
						affiliationReussie = 1;
					}
					else if(((isdigit(saisie[0]) && saisie[0]!='0') || saisie[0]=='A' || saisie[0]=='J' || saisie[0]=='Q' || saisie[0]=='K') && (saisie[1]=='C' || saisie[1]=='K' || saisie[1]=='T' || saisie[1]=='P')){ // Cas où la carte n'est pas un 10
						valeur[0] = saisie[0];
						valeur[1]= '\0';
						strcpy(couleur, &saisie[1]);
						affiliationReussie = 1;
					}
					else if(!strcmp(saisie, "#")){ // Cas où le joueur passe son tour
						printf("Vous passez votre tour.\n\n");
						affiliationReussie = 1;
						passe = 1;
					}
					else{ // Cas d'une mauvaise saisie
						afficheUneMain(parts);
						compteurDErreur++;
						if(compteurDErreur==3){
						    printf("Trois fausses saisies, vous passez votre tour.\n\n");
						    saisie[0]='#';
						    affiliationReussie=1;
						
					    }
					    // Rappel des règles de saisie
						printf("On utilisera A pour l'As, 2 à 10 pour les cartes numériques, J,Q et K pour le valet, la dame et le roi.\nOn utilisera également T pour trèfle, C pour Coeur, P pour pique et K pour Carreau.\nOn entrera # pour passer son tour.\nEntrez une valeur de carte.\n");
					}
				}
				// On réinitialise le booléen d'affectation réussie
				affiliationReussie=0;
				
				////// Si le joueur ne passe pas son tour //////
				if(passe==0){ 
					// On créé la carte qu'il a choisit, on l'affiche
					carteJouee = Carte_creer(Carte_rvaleur(valeur), Carte_rcouleur(couleur));
					printf("%s\n", Carte_affiche(carteJouee));
			
					////// Vérifier que le joueur a la carte //////
					// Si la carte est présente dans la main du joueur, 
					// forme une suite avec la défausse ou qu'il s'agit de la première défausse
					if(carteEstPresente(parts->main, carteJouee) && (Carte_estUneSuite(carteJouee, Defausse) || PremiereDefausse) ){ 
						// La défausse n'est plus nulle, donc on force à 0 le booléen
						PremiereDefausse = 0;
						// On retire la carte de la main
						parts->main=retirerCarte(parts->main,carteJouee);
						// La défausse contient maintenant la carte qui a été jouée
						Defausse = carteJouee; 
					
						////// Tester si la carte est spéciale //////
						CarteAGain = carteEstSpeciale(carteJouee);
						if(CarteAGain){ // Si oui, créditer le joueur
							FaireLesGains(carteJouee, parts, nb);
							sleep(2);
						}
				
					} 
					// Si la carte est présente dans la main mais que ce n'est pas une suite
					else if(carteEstPresente(parts->main, carteJouee) && !Carte_estUneSuite(carteJouee, Defausse)){
						// On informe le joueur et on incremente le compteur d'erreur
						printf("Ce n'est pas une suite !\n");
						compteurDErreur++;
						sleep(3);
					}
					// Sinon, le joueur ne possède pas la carte donc...
					else{
						// On informe le joueur et on incrémente le compteur d'erreur
						printf("Ah non, vous devez posséder la carte dans votre main !\n");
						compteurDErreur++;
						sleep(3);
					}
					// On teste si le joueur vient de faire 3 erreurs
					if(compteurDErreur==3){
						// Si oui, il passe son tour
						printf("Trois fausses saisies, vous passez votre tour.\n\n");
						saisie[0]='#';
					}
				}
			// Si la main du joueur est nul, et que le gagnant n'a pas encore été désigné
			if(parts->main==NULL && score==9){
				// On mémorise l'indice du gagnant, on le rémunère et on arrete la manche
				score=parts->indiceJoueur;
				parts->nbJetons = parts->nbJetons + 10;
				saisie[0]='#';
				printf("Bravo vous avez fini de jouer pour cette manche !\nVous remportez la manche et 10 jetons pour la route !!\n");
				aPasse=0;
				sleep(1);
			}
			}while(saisie[0]!='#'); // Tant que le joueur n'a pas passé son tour
			
		}
		// On réinitialise le booléen de passage de tour et la ligne de saisie
		passe=0;
		saisie[0]='\0';
		
		// Vérifier que les joueurs n'ont pas tous passé leur tour
		// en comparant le nombre de cartes du joueur avant défausse et à la fin de son tour	
	    if(parts->main!=NULL && nbCartesJoueur(parts)==nbCartesPrec){
	        aPasse++;
	    }
	    else{
	        aPasse=0;
	    }
		if(aPasse==nb-1){
            // On réinitialise la défausse si aucun des joueurs n'a pu jouer
		    aPasse=0;
		    PremiereDefausse=1;
		    printf("Aucun joueur ne peut jouer, la défausse est réinitialisée\n");
		    sleep(3);
		}
		
		
		// On passe au joueur suivant ou on retourne en début de liste selon les cas
		if(parts->JSuivant==NULL){
		    //sauvegarde(parts);
		    //printf("SAVE !\n");
			parts=Prems;
		}
		else{
		    //sauvegarde(parts);
		    //printf("SAVE !\n");
			parts=parts->JSuivant;
		}
		
		// On réinitialise le compteur d'erreur
		compteurDErreur = 0;
	    
	    
	    // Sécurité
	    // Si le gagnant est deja mémorisé, on arrete donc la manche !
	    if(score!=9){
	        arretManche=1;
	    }
	
	}
	
	// AFFICHER LES JOUEURS !
	parts=Prems;
	parts->JSuivant = Prems->JSuivant;
	afficherJ(parts);
	sleep(3);
	printf("Voulez-vous continuer?\n\t1 pour oui\n\t0 pour non\n");
	fgets(choixFinal,16,stdin);
    sscanf(choixFinal,"%d", &final);
    // Si l'utilisateur décide de quitter, on quitte
    if(final==0){
        printf("Arret du jeu...\n");
        arretJeu = 1;
    }
    else{ // Sinon, c'est reparti
        printf("Nouvelle manche !!\n");
        parts = modifierTete(parts); // On passe la main au joueur suivant le joueur qui a commencé
        afficherJ(parts); // On affiche la nouvelle liste (ordre changé)
        miseJetons(parts); // On effectue les mises
        // On vérifie que le nombre de joueurs permet toujours de jouer une manche
        nb = nombreJoueurs(parts);
        if(nb<3){
        	printf("Désolé vous ne pouvez pas continuer, il n'y a plus assez de joueurs\nMerci d'avoir jouer :)\n");
        	arretJeu = 1;
        }
        else{
        	// Si on peut relancer une manche, on réinitialise tout
        	score=9;
		    arretJeu = 0; aPasse=0;
		    arretManche=0; compteurDErreur = 0;
		    PremiereDefausse=1;
		    passe=0;
			saisie[0]='\0';
			viderCartes(parts);
			sleep(2);
		    nbCartes = nombreCarte(nb);
			distribuerCartes(parts, nbCartes);
			printf("Le joueur %s commence :\n",parts->nom);
			sleep(2);
		}
    }
    }
}

