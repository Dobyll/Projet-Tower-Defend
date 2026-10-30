#ifndef TOWERDEFEND_H_INCLUDED
#define TOWERDEFEND_H_INCLUDED

#include "SDL.h"

#include <stdbool.h>

#define LARGEURJEU 11
#define HAUTEURJEU 19
#define NBCOORDPARCOURS 34
#define X 0
#define Y 1

typedef enum{tourSol, tourAir, tourRoi, archer, chevalier, dragon, gargouille} TuniteDuJeu;
typedef enum{sol, solEtAir, air } Tcible;


typedef struct {
    TuniteDuJeu nom;
    Tcible cibleAttaquable;	//indique le type des unites que l'on peut attaquer
    Tcible maposition;		//indique soit  (l'air) soit  (sol), utile pour savoir
                            //qui peut nous attaquer
    int pointsDeVie;
    float vitesseAttaque;	//en seconde, plus c'est petit plus c'est rapide
    int degats;
    int portee ;			//en mètre, distance sur laquelle on peut atteindre une
                            //cible

    float vitessedeplacement;	//en m/s
    int posX, posY;			//position sur le plateau de jeu
    int peutAttaquer;		//permet de gérer le fait que chaque unité attaque une
                            //seule fois par tour ;
                            //0 = a déjà attaqué, 1 = peut attaquer ce tour-ci
                            // à remettre à 1 au début de chaque tour

} Tunite;

typedef struct T_cell{
    struct T_cell *suiv;
    Tunite *pdata; //pointeur vers une unité
} *TListePlayer;

typedef Tunite* ** TplateauJeu;  //tableau a deux dimensions de largeur 11 et hauteur 19 contenant des pointeurs (Tunite*)

TplateauJeu AlloueTab2D(int largeur, int hauteur);
void afficheCoordonneesParcours(int **t, int nbcoord);
int **initChemin(void);         //retourne le chemin emprunter par la horde, sous forme d'un tableau[NBCOORDPARCOURS][2]
void freeChemin(int **tab);

void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur);
void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur);

Tunite *creeTourSol(int posx, int posy);
Tunite *creeTourAir(int posx, int posy);
Tunite *creeTourRoi(int posx, int posy);
Tunite *creeArcher(int posx, int posy);
Tunite *creeGargouille(int posx, int posy);
Tunite *creeChevalier(int posx, int posy);
Tunite *creeDragon(int posx, int posy);

void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite);
void AjouterUniteEnFin(TListePlayer *player, Tunite *nouvelleUnite);
void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu);
bool tourRoiDetruite(TListePlayer player);
void supprimerUnite(TListePlayer *player, Tunite *UniteDetruite, TplateauJeu jeu);
int estUniteDuRoi(Tunite *u);
int estUniteDeLaHorde(Tunite *u);
int estALaBonnePortee(Tunite *attaquant, Tunite *cible);
int peutToucherCetteCible(Tunite *attaquant, Tunite *cible);
TListePlayer quiEstAPortee(TplateauJeu jeu, Tunite *UniteAttaquante);
void combat(SDL_Surface *surface, Tunite *UniteAttaquante, Tunite *UniteCible);
Tunite *getCibleLaPlusFaible(TListePlayer cibles);
void freeListeCibles(TListePlayer cibles);
void attaquePlayer(SDL_Surface *surface, TListePlayer playerAttaquant, TListePlayer *playerAdverse, TplateauJeu jeu);
int nbToursAttente(Tunite *u);
void resetPeutAttaquer(TListePlayer player, int numeroTour);
int getIndiceSurChemin(Tunite *u, int **tabParcours);
void deplaceUneUniteHorde(Tunite *u, int **tabParcours, TplateauJeu jeu);
void deplaceHorde(TListePlayer horde, int **tabParcours, TplateauJeu jeu);
void creerUniteHorde(TListePlayer *horde, int **tabParcours, TplateauJeu jeu);
int estCaseSurChemin(int x, int y, int **tabParcours);
int scoreCaseDefense(int x, int y, int portee, int **tabParcours, TplateauJeu jeu);
void creerTourDefenseRoi(TListePlayer *playerRoi, int **tabParcours, TplateauJeu jeu);
int compterUnites(TListePlayer player);
void freePlateau(TplateauJeu jeu, int largeur);
void freePlayer(TListePlayer player);

void sauvegardeBinaire(TListePlayer playerRoi, TListePlayer playerHorde, int **tabParcours);
void chargementBinaire(TListePlayer *playerRoi, TListePlayer *playerHorde, int **tabParcours);

void sauvegardeTexte(TListePlayer playerRoi, TListePlayer playerHorde, int **tabParcours);
void chargementTexte(TListePlayer *playerRoi, TListePlayer *playerHorde, int **tabParcours);


#endif // TOWERDEFEND_H_INCLUDED
