#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "towerdefend.h"
#include "maSDL.h"

//typedef Tunite* ** TplateauJeu;

TplateauJeu AlloueTab2D(int largeur, int hauteur){
    TplateauJeu jeu;
    jeu = (Tunite***)malloc(sizeof(Tunite**)*largeur);
    for (int i=0;i<largeur;i++){
        jeu[i] = (Tunite**)malloc(sizeof(Tunite*)*hauteur);
    }
    return jeu;  //tab2D contenant des pointeurs
}
void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur){
    for (int i=0;i<largeur;i++){
        for (int j=0;j<hauteur;j++){
            jeu[i][j] = NULL;
        }
    }
}

/*
void ecritCheminVersleHaut  : permet d'initilaiser le tab chemin de distance cases (avec des coord x y) dans une direction, a partir d'un point x y donne

int **chemin  : tab de coordonnees x y du chemin
int *ichemin  : indice de la case du chemin d'ou on part
int *xdepart, int *ydepart : valeur en x y de depart pouri la premiere case
int distance  : distance sur laquelle on va ecrire des coordonnees dans le tab chemin
int *distanceMaxRestante : securite pour ne pas sortir de la plage d'indice de chemin
*/
void ecritCheminVersleHaut(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance){

        int y;
        for (y=*ydepart;y>*ydepart-distance;y--){
            chemin[*ichemin][X]= *xdepart;
            chemin[*ichemin][Y]= y;
            (*ichemin)++;
        }
        *ydepart=y;

}
void ecritCheminVerslaDroite(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance){

        int x;
        for (x=*xdepart;x<*xdepart+distance;x++){
            chemin[*ichemin][X]= x;
            chemin[*ichemin][Y]= *ydepart;
            (*ichemin)++;
        }
        *xdepart=x;

}
void ecritCheminVerslaGauche(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance){

        int x;
        for (x=*xdepart;x>*xdepart-distance;x--){
            chemin[*ichemin][X]= x;
            chemin[*ichemin][Y]= *ydepart;
            (*ichemin)++;
        }
        *xdepart=x;

}

/*int **initChemin(){
    int **chemin = (int**)malloc(sizeof(int*)*NBCOORDPARCOURS);

    for (int j=0;j<NBCOORDPARCOURS;j++){
        chemin[j] = (int*)malloc(sizeof(int)*2);  //2 cases :indice 0 pour la coord en X, indice 1 pour la coord en Y
    }

    int ydepart = 18;  //et non 19
    int xdepart = 5;  //5 = milieu de la fenetre de 11 de largeur (0-10)
    int i = 0;  //parcourt les i cases du chemin
    int distanceMaxRestante = NBCOORDPARCOURS;

    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3, &distanceMaxRestante);
    ecritCheminVerslaDroite(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVerslaGauche(chemin, &i, &xdepart, &ydepart, 5, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVerslaDroite(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3, &distanceMaxRestante);
    ecritCheminVerslaGauche(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3, &distanceMaxRestante);

    return chemin;  //tab2D contenant des pointeurs
}*/

// chemin aleatoire
int **initChemin(void){
    int **chemin = (int**)malloc(sizeof(int*)*NBCOORDPARCOURS);

    for (int j=0;j<NBCOORDPARCOURS;j++){
        chemin[j] = (int*)malloc(sizeof(int)*2);
    }

    int ydepart = 18; //et non 19
    int xdepart = 5; //5 = milieu de la fenetre de 11 de largeur (0-10)
    int i = 0; //parcourt les i cases du chemin

    int distancesHorizontales[4];
    int directions[4];
    int valide = 0;

    /* genere un chemin aleatoire qui reste dans le plateau */
    while (valide == 0){

        distancesHorizontales[0] = 3 + rand()%3;
        distancesHorizontales[1] = 3 + rand()%3;
        distancesHorizontales[2] = 3 + rand()%3;
        distancesHorizontales[3] = 17 - distancesHorizontales[0] - distancesHorizontales[1] - distancesHorizontales[2];

        if (distancesHorizontales[3] < 3 || distancesHorizontales[3] > 5){
            continue;
        }

        if (rand()%2 == 0){
            directions[0] = 1;
        }
        else{
            directions[0] = -1;
        }

        directions[1] = -directions[0];
        directions[2] = -directions[1];
        directions[3] = -directions[2];

        int xtest = 5;
        valide = 1;

        for (int k=0; k<4; k++){
            xtest = xtest + directions[k] * distancesHorizontales[k];

            if (xtest < 0 || xtest >= LARGEURJEU){
                valide = 0;
            }
        }
    }

    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3);

    if (directions[0] == 1)
        ecritCheminVerslaDroite(chemin, &i, &xdepart, &ydepart, distancesHorizontales[0]);
    else
        ecritCheminVerslaGauche(chemin, &i, &xdepart, &ydepart, distancesHorizontales[0]);

    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 4);

    if (directions[1] == 1)
        ecritCheminVerslaDroite(chemin, &i, &xdepart, &ydepart, distancesHorizontales[1]);
    else
        ecritCheminVerslaGauche(chemin, &i, &xdepart, &ydepart, distancesHorizontales[1]);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 4);

    if (directions[2] == 1)
        ecritCheminVerslaDroite(chemin, &i, &xdepart, &ydepart, distancesHorizontales[2]);
    else
        ecritCheminVerslaGauche(chemin, &i, &xdepart, &ydepart, distancesHorizontales[2]);

    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3);

    if (directions[3] == 1)
        ecritCheminVerslaDroite(chemin, &i, &xdepart, &ydepart, distancesHorizontales[3]);
    else
        ecritCheminVerslaGauche(chemin, &i, &xdepart, &ydepart, distancesHorizontales[3]);

    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3);

    return chemin; // retourne le tableau contenant le chemin
}

// affiche les coordonnees du chemin
void afficheCoordonneesParcours(int **chemin, int nbcoord){
    printf("Liste coordonnees: ");
    for (int i=0; i<nbcoord; i++){
        printf("(%d, %d)",chemin[i][X], chemin[i][Y]);
    }
    printf("\nfin liste coordonnees\n");
}

// libere la memoire du chemin
void freeChemin(int **tab){
    for (int j=0;j<NBCOORDPARCOURS;j++){
        free(tab[j]);  //libere chaque case, qui est un tableau de 2 cases
    }
    free(tab);
}

// affiche le plateau dans la console
void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur){
    //pour un affichage sur la console, en relation avec enum TuniteDuJeu
    const char* InitialeUnite[7]={"s", "a", "r", "A", "C", "D", "G"};

    printf("\n");
    for (int j=0;j<hauteur;j++){
        for (int i=0;i<largeur;i++){
                // A ne pas donner aux etudiants
            if (jeu[i][j] != NULL){
                    printf("%s",InitialeUnite[jeu[i][j]->nom]);
            }
            else printf(" ");  //cad pas d'unité sur cette case
        }
        printf("\n");
    }
}

Tunite *creeTourSol(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourSol;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 120;
    nouv->portee = 5;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}
Tunite *creeTourAir(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourAir;
    nouv->cibleAttaquable = air;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.0;
    nouv->degats = 100;
    nouv->portee = 3;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}
Tunite *creeTourRoi(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourRoi;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 800;
    nouv->vitesseAttaque = 1.2;
    nouv->degats = 180;
    nouv->portee = 4;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeChevalier(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = chevalier;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 400;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 250;
    nouv->portee = 1;
    nouv->vitessedeplacement = 2;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeArcher(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = archer;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.7;
    nouv->degats = 120;
    nouv->portee = 3;
    nouv->vitessedeplacement = 1;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeDragon(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = dragon;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 200;
    nouv->vitesseAttaque = 1.1;
    nouv->degats = 70;
    nouv->portee = 2;
    nouv->vitessedeplacement = 2;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeGargouille(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = gargouille;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.6;
    nouv->degats = 90;
    nouv->portee = 1;
    nouv->vitessedeplacement = 3;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}


// ajoute une unite en tete de la liste du joueur
void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite){
    TListePlayer nouv = (TListePlayer)malloc(sizeof(struct T_cell));

    nouv->pdata = nouvelleUnite;
    nouv->suiv = *player;
    *player = nouv;
}

// ajoute une unite en fin de liste
void AjouterUniteEnFin(TListePlayer *player, Tunite *nouvelleUnite){
    TListePlayer nouv = (TListePlayer)malloc(sizeof(struct T_cell));
    nouv->pdata = nouvelleUnite;
    nouv->suiv = NULL;

    if (*player == NULL){
        *player = nouv;
    }
    else{
        TListePlayer courant = *player;
        while (courant->suiv != NULL){
            courant = courant->suiv;
        }
        courant->suiv = nouv;
    }
}

// place les unites du joueur sur le plateau
void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu){
    TListePlayer courant = player;

    while (courant != NULL){
        jeu[courant->pdata->posX][courant->pdata->posY] = courant->pdata;
        courant = courant->suiv;
    }
}

// verifie si la tour du roi est detruite
bool tourRoiDetruite(TListePlayer player){
    TListePlayer courant = player;

    while (courant != NULL){
        if (courant->pdata->nom == tourRoi){
            if (courant->pdata->pointsDeVie <= 0){
                return true;
            }
            else{
                return false;
            }
        }
        courant = courant->suiv;
    }

    return true;
}

// supprime une unite de la liste et du plateau
void supprimerUnite(TListePlayer *player, Tunite *UniteDetruite, TplateauJeu jeu){
    TListePlayer courant = *player;
    TListePlayer precedent = NULL;

    if (UniteDetruite == NULL){
        return;
    }

    jeu[UniteDetruite->posX][UniteDetruite->posY] = NULL;

    while (courant != NULL && courant->pdata != UniteDetruite){
        precedent = courant;
        courant = courant->suiv;
    }

    if (courant != NULL){
        if (precedent == NULL){
            *player = courant->suiv;
        }
        else{
            precedent->suiv = courant->suiv;
        }

        free(courant->pdata);
        free(courant);
    }
}

// verifie si une unite appartient au roi
int estUniteDuRoi(Tunite *u){
    if (u->nom == tourSol || u->nom == tourAir || u->nom == tourRoi){
        return 1;
    }
    else{
        return 0;
    }
}

// verifie si une unite appartient a la horde
int estUniteDeLaHorde(Tunite *u){
    if (u->nom == archer || u->nom == chevalier || u->nom == dragon || u->nom == gargouille){
        return 1;
    }
    else{
        return 0;
    }
}

// verifie si la cible est a portee
int estALaBonnePortee(Tunite *attaquant, Tunite *cible){
    int dx = attaquant->posX - cible->posX;
    int dy = attaquant->posY - cible->posY;

    return (dx*dx + dy*dy <= attaquant->portee * attaquant->portee);
}

// verifie si l'attaquant peut toucher cette cible
int peutToucherCetteCible(Tunite *attaquant, Tunite *cible){
    if (attaquant->cibleAttaquable == solEtAir){
        return 1;
    }
    else{
        if (attaquant->cibleAttaquable == sol && cible->maposition == sol){
            return 1;
        }
        else{
            if (attaquant->cibleAttaquable == air && cible->maposition == air){
                return 1;
            }
            else{
                return 0;
            }
        }
    }
}

// renvoie la liste des cibles a portee d'une unite
TListePlayer quiEstAPortee(TplateauJeu jeu, Tunite *UniteAttaquante){
    TListePlayer cibles = NULL;

    int xmin = UniteAttaquante->posX - UniteAttaquante->portee;
    int xmax = UniteAttaquante->posX + UniteAttaquante->portee;
    int ymin = UniteAttaquante->posY - UniteAttaquante->portee;
    int ymax = UniteAttaquante->posY + UniteAttaquante->portee;

    if (xmin < 0) xmin = 0;
    if (ymin < 0) ymin = 0;
    if (xmax >= LARGEURJEU) xmax = LARGEURJEU - 1;
    if (ymax >= HAUTEURJEU) ymax = HAUTEURJEU - 1;

    for (int x = xmin; x <= xmax; x++){
        for (int y = ymin; y <= ymax; y++){

            if (jeu[x][y] != NULL){
                Tunite *cible = jeu[x][y];

                if (cible != UniteAttaquante){

                    if (estALaBonnePortee(UniteAttaquante, cible)){

                        if (peutToucherCetteCible(UniteAttaquante, cible)){

                            if (estUniteDuRoi(UniteAttaquante) && estUniteDeLaHorde(cible)){
                                AjouterUnite(&cibles, cible);
                            }
                            else{
                                if (estUniteDeLaHorde(UniteAttaquante) && cible->nom == tourRoi){
                                    AjouterUnite(&cibles, cible);
                                }
                            }

                        }
                    }

                }
            }
        }
    }

    return cibles;
}

// gere une attaque entre deux unites
void combat(SDL_Surface *surface, Tunite *UniteAttaquante, Tunite *UniteCible){

    if (UniteAttaquante == NULL || UniteCible == NULL){
        return;
    }

    if (UniteAttaquante->peutAttaquer == 1){

        UniteCible->pointsDeVie = UniteCible->pointsDeVie - UniteAttaquante->degats;

        if (UniteCible->pointsDeVie < 0){
            UniteCible->pointsDeVie = 0;
        }

        if (UniteCible->nom == tourRoi){
            printf("La tour du roi est attaquee ! PV restants : %d\n", UniteCible->pointsDeVie);
        }

        dessineAttaque(surface, UniteAttaquante, UniteCible);
        UniteAttaquante->peutAttaquer = 0;
    }
}

// retourne la cible avec le moins de points de vie
Tunite *getCibleLaPlusFaible(TListePlayer cibles){

    TListePlayer courant = cibles;
    Tunite *plusFaible = NULL;

    while (courant != NULL){

        if (plusFaible == NULL || courant->pdata->pointsDeVie < plusFaible->pointsDeVie){
            plusFaible = courant->pdata;
        }

        courant = courant->suiv;
    }

    return plusFaible;
}


// libere la liste temporaire des cibles
void freeListeCibles(TListePlayer cibles){

    TListePlayer courant = cibles;
    TListePlayer suivant;

    while (courant != NULL){

        suivant = courant->suiv;
        free(courant);
        courant = suivant;
    }
}


// gere les attaques automatiques d'un joueur
void attaquePlayer(SDL_Surface *surface, TListePlayer playerAttaquant, TListePlayer *playerAdverse, TplateauJeu jeu){

    TListePlayer courant = playerAttaquant;

    while (courant != NULL){

        Tunite *attaquant = courant->pdata;

        if (attaquant->peutAttaquer == 1){

            TListePlayer cibles = quiEstAPortee(jeu, attaquant);
            Tunite *cible = getCibleLaPlusFaible(cibles);

            if (cible != NULL){

                combat(surface, attaquant, cible);

                if (cible->pointsDeVie <= 0){
                    supprimerUnite(playerAdverse, cible, jeu);
                }

                if (estUniteDeLaHorde(attaquant) && cible->nom == tourRoi){
                    freeListeCibles(cibles);
                    return;
                }
            }

            freeListeCibles(cibles);
        }

        courant = courant->suiv;
    }
}

// calcule le nombre de tours a attendre avant une attaque
int nbToursAttente(Tunite *u){

    float dureeTour = 0.3f;
    int nb = (int)(u->vitesseAttaque / dureeTour);

    if (u->vitesseAttaque > nb * dureeTour){
        nb++;
    }

    if (nb < 1){
        nb = 1;
    }

    return nb;
}

// remet a jour peutAttaquer selon le tour
void resetPeutAttaquer(TListePlayer player, int numeroTour){

    TListePlayer courant = player;

    while (courant != NULL){

        int attente = nbToursAttente(courant->pdata);

        if (numeroTour % attente == 0){
            courant->pdata->peutAttaquer = 1;
        }
        else{
            courant->pdata->peutAttaquer = 0;
        }

        courant = courant->suiv;
    }
}

// retrouve l'indice d'une unite sur le chemin
int getIndiceSurChemin(Tunite *u, int **tabParcours){

    int i = 0;

    while (i < NBCOORDPARCOURS){

        if (tabParcours[i][X] == u->posX && tabParcours[i][Y] == u->posY){
            return i;
        }

        i++;
    }

    return -1;
}

// deplace une unite de la horde sur le chemin
void deplaceUneUniteHorde(Tunite *u, int **tabParcours, TplateauJeu jeu){

    int indiceActuel = getIndiceSurChemin(u, tabParcours);

    if (indiceActuel == -1){
        return;
    }

    int nbCasesAParcourir = (int)(u->vitessedeplacement);
    int nbCasesParcourues = 0;

    while (nbCasesParcourues < nbCasesAParcourir && indiceActuel < NBCOORDPARCOURS - 1){

        int nouvX = tabParcours[indiceActuel + 1][X];
        int nouvY = tabParcours[indiceActuel + 1][Y];

        if (jeu[nouvX][nouvY] == NULL){

            jeu[u->posX][u->posY] = NULL;

            u->posX = nouvX;
            u->posY = nouvY;

            jeu[u->posX][u->posY] = u;

            indiceActuel++;
            nbCasesParcourues++;
        }
        else{
            return;
        }
    }
}

// deplace toute la horde
void deplaceHorde(TListePlayer horde, int **tabParcours, TplateauJeu jeu){

    TListePlayer courant = horde;

    while (courant != NULL){
        deplaceUneUniteHorde(courant->pdata, tabParcours, jeu);
        courant = courant->suiv;
    }
}


// cree une unite de la horde au debut du chemin
void creerUniteHorde(TListePlayer *horde, int **tabParcours, TplateauJeu jeu){

    int x = tabParcours[0][X];
    int y = tabParcours[0][Y];

    if (jeu[x][y] == NULL){

        int choix = rand() % 4;
        Tunite *nouvelle = NULL;

        if (choix == 0){
            nouvelle = creeArcher(x, y);
        }
        else if (choix == 1){
            nouvelle = creeChevalier(x, y);
        }
        else if (choix == 2){
            nouvelle = creeDragon(x, y);
        }
        else{
            nouvelle = creeGargouille(x, y);
        }

        AjouterUnite(horde, nouvelle);
        jeu[x][y] = nouvelle;
    }
}

// verifie si une case est sur le chemin
int estCaseSurChemin(int x, int y, int **tabParcours){

    int i = 0;

    while (i < NBCOORDPARCOURS){

        if (tabParcours[i][X] == x && tabParcours[i][Y] == y){
            return 1;
        }

        i++;
    }

    return 0;
}

// calcule le score d'une case pour une tour
int scoreCaseDefense(int x, int y, int portee, int **tabParcours, TplateauJeu jeu){

    int score = 0;
    int i = 0;

    if (x < 0 || x >= LARGEURJEU || y < 0 || y >= HAUTEURJEU){
        return -1;
    }

    if (jeu[x][y] != NULL){
        return -1;
    }

    if (estCaseSurChemin(x, y, tabParcours)){
        return -1;
    }

    while (i < NBCOORDPARCOURS){

        if (i >= 6){
            int dx = x - tabParcours[i][X];
            int dy = y - tabParcours[i][Y];

            if (dx*dx + dy*dy <= portee*portee){
                score++;
            }
        }

        i++;
    }

    return score;
}


// place une tour du roi sur la meilleure case
void creerTourDefenseRoi(TListePlayer *playerRoi, int **tabParcours, TplateauJeu jeu){

    int meilleurXSol = -1;
    int meilleurYSol = -1;
    int meilleurScoreSol = -1;

    int meilleurXAir = -1;
    int meilleurYAir = -1;
    int meilleurScoreAir = -1;

    Tunite *nouvelle = NULL;

    for (int x = 0; x < LARGEURJEU; x++){
        for (int y = 0; y < HAUTEURJEU; y++){

            int scoreSol = scoreCaseDefense(x, y, 5, tabParcours, jeu);
            if (scoreSol > meilleurScoreSol){
                meilleurScoreSol = scoreSol;
                meilleurXSol = x;
                meilleurYSol = y;
            }

            int scoreAir = scoreCaseDefense(x, y, 3, tabParcours, jeu);
            if (scoreAir > meilleurScoreAir){
                meilleurScoreAir = scoreAir;
                meilleurXAir = x;
                meilleurYAir = y;
            }
        }
    }

    if (meilleurXSol == -1 && meilleurXAir == -1){
        return;
    }

    float scoreSolNormalise = (float)meilleurScoreSol / 5.0f;
    float scoreAirNormalise = (float)meilleurScoreAir / 3.0f;

    if (scoreSolNormalise > scoreAirNormalise){
        nouvelle = creeTourSol(meilleurXSol, meilleurYSol);

        AjouterUnite(playerRoi, nouvelle);
        jeu[meilleurXSol][meilleurYSol] = nouvelle;
    }
    else if (scoreAirNormalise > scoreSolNormalise){
        nouvelle = creeTourAir(meilleurXAir, meilleurYAir);

        AjouterUnite(playerRoi, nouvelle);
        jeu[meilleurXAir][meilleurYAir] = nouvelle;
    }
    else{

        if (rand() % 2 == 0){
            nouvelle = creeTourSol(meilleurXSol, meilleurYSol);

            AjouterUnite(playerRoi, nouvelle);
            jeu[meilleurXSol][meilleurYSol] = nouvelle;
        }
        else{
            nouvelle = creeTourAir(meilleurXAir, meilleurYAir);

            AjouterUnite(playerRoi, nouvelle);
            jeu[meilleurXAir][meilleurYAir] = nouvelle;
        }
    }
}

// compte le nombre d'unites dans une liste
int compterUnites(TListePlayer player){

    int nb = 0;

    while (player != NULL){
        nb++;
        player = player->suiv;
    }

    return nb;
}

// libere la memoire du plateau
void freePlateau(TplateauJeu jeu, int largeur){

    for (int i = 0; i < largeur; i++){
        free(jeu[i]);
    }

    free(jeu);
}

// libere toute la memoire d'une liste
void freePlayer(TListePlayer player){

    TListePlayer suivant;

    while (player != NULL){

        suivant = player->suiv;
        free(player->pdata);
        free(player);
        player = suivant;
    }
}

// sauvegarde la partie dans un fichier binaire
void sauvegardeBinaire(TListePlayer playerRoi, TListePlayer playerHorde, int **tabParcours){

    FILE *f = fopen("partiebin.clb", "wb");

    if (f == NULL){
        return;
    }

    for (int i = 0; i < NBCOORDPARCOURS; i++){
        fwrite(tabParcours[i], sizeof(int), 2, f);
    }

    TListePlayer courant = playerRoi;
    while (courant != NULL){
        fwrite(courant->pdata, sizeof(Tunite), 1, f);
        courant = courant->suiv;
    }

    Tunite fin;
    fin.nom = -1;
    fwrite(&fin, sizeof(Tunite), 1, f);

    courant = playerHorde;
    while (courant != NULL){
        fwrite(courant->pdata, sizeof(Tunite), 1, f);
        courant = courant->suiv;
    }

    fwrite(&fin, sizeof(Tunite), 1, f);

    fclose(f);
}

// recharge une partie depuis un fichier binaire
void chargementBinaire(TListePlayer *playerRoi, TListePlayer *playerHorde, int **tabParcours){

    FILE *f = fopen("partiebin.clb", "rb");

    if (f == NULL){
        return;
    }

    for (int i = 0; i < NBCOORDPARCOURS; i++){
        if (fread(tabParcours[i], sizeof(int), 2, f) != 2){
            fclose(f);
            return;
        }
    }

    Tunite temp;

    freePlayer(*playerRoi);
    freePlayer(*playerHorde);

    *playerRoi = NULL;
    *playerHorde = NULL;

    while (1){

        if (fread(&temp, sizeof(Tunite), 1, f) != 1){
            break;
        }

        if (temp.nom == -1){
            break;
        }

        Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
        *nouv = temp;
        AjouterUniteEnFin(playerRoi, nouv);
    }

    while (1){

        if (fread(&temp, sizeof(Tunite), 1, f) != 1){
            break;
        }

        if (temp.nom == -1){
            break;
        }

        Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
        *nouv = temp;
        AjouterUniteEnFin(playerHorde, nouv);
    }

    fclose(f);
}

// sauvegarde la partie dans un fichier texte
void sauvegardeTexte(TListePlayer playerRoi, TListePlayer playerHorde, int **tabParcours){

    FILE *f = fopen("partieseq.cls", "w");

    if (f == NULL){
        return;
    }

    for (int i = 0; i < NBCOORDPARCOURS; i++){
        fprintf(f, "%d %d\n", tabParcours[i][X], tabParcours[i][Y]);
    }

    TListePlayer courant = playerRoi;
    while (courant != NULL){
        Tunite *u = courant->pdata;

        fprintf(f, "%d %d %d %d %f %d %d %f %d %d %d\n",
                u->nom,
                u->cibleAttaquable,
                u->maposition,
                u->pointsDeVie,
                u->vitesseAttaque,
                u->degats,
                u->portee,
                u->vitessedeplacement,
                u->posX,
                u->posY,
                u->peutAttaquer);

        courant = courant->suiv;
    }

    fprintf(f, "-1\n");

    courant = playerHorde;
    while (courant != NULL){
        Tunite *u = courant->pdata;

        fprintf(f, "%d %d %d %d %f %d %d %f %d %d %d\n",
                u->nom,
                u->cibleAttaquable,
                u->maposition,
                u->pointsDeVie,
                u->vitesseAttaque,
                u->degats,
                u->portee,
                u->vitessedeplacement,
                u->posX,
                u->posY,
                u->peutAttaquer);

        courant = courant->suiv;
    }

    fprintf(f, "-1\n");

    fclose(f);
}

// recharge une partie depuis un fichier texte
void chargementTexte(TListePlayer *playerRoi, TListePlayer *playerHorde, int **tabParcours){

    FILE *f = fopen("partieseq.cls", "r");

    if (f == NULL){
        return;
    }

    for (int i = 0; i < NBCOORDPARCOURS; i++){
        if (fscanf(f, "%d %d", &tabParcours[i][X], &tabParcours[i][Y]) != 2){
            fclose(f);
            return;
        }
    }

    freePlayer(*playerRoi);
    freePlayer(*playerHorde);
    *playerRoi = NULL;
    *playerHorde = NULL;

    Tunite temp;
    int retour;

    while (1){

        retour = fscanf(f, "%d", (int *)&temp.nom);
        if (retour != 1){
            break;
        }

        if (temp.nom == -1){
            break;
        }

        if (fscanf(f, "%d %d %d %f %d %d %f %d %d %d",
               (int *)&temp.cibleAttaquable,
               (int *)&temp.maposition,
               &temp.pointsDeVie,
               &temp.vitesseAttaque,
               &temp.degats,
               &temp.portee,
               &temp.vitessedeplacement,
               &temp.posX,
               &temp.posY,
               &temp.peutAttaquer) != 10){
            break;
        }

        Tunite *nouv = (Tunite *)malloc(sizeof(Tunite));
        *nouv = temp;
        AjouterUniteEnFin(playerRoi, nouv);
    }

    while (1){

        retour = fscanf(f, "%d", (int *)&temp.nom);
        if (retour != 1){
            break;
        }

        if (temp.nom == -1){
            break;
        }

        if (fscanf(f, "%d %d %d %f %d %d %f %d %d %d",
               (int *)&temp.cibleAttaquable,
               (int *)&temp.maposition,
               &temp.pointsDeVie,
               &temp.vitesseAttaque,
               &temp.degats,
               &temp.portee,
               &temp.vitessedeplacement,
               &temp.posX,
               &temp.posY,
               &temp.peutAttaquer) != 10){
            break;
        }

        Tunite *nouv = (Tunite *)malloc(sizeof(Tunite));
        *nouv = temp;
        AjouterUniteEnFin(playerHorde, nouv);
    }

    fclose(f);
}
