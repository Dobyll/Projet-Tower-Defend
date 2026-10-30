//NOM prénom étudiant 1 : MAMADOU DIALLO Saidou
//NOM prénom étudiant 2 : SABINO Folawe

#include "SDL.h"
#include "maSDL.h"
#include "towerdefend.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



/*--------- Main ---------------------*/
int main(int argc, char* argv[])
{
    srand(time(NULL));

    SDL_Window *pWindow;
    SDL_Init(SDL_INIT_VIDEO);

    pWindow = SDL_CreateWindow(
        "Appuyez sur ECHAP pour quitter, S/C ET D/V les gerer les sauvegardes",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        LARGEURJEU*40,
        HAUTEURJEU*40,
        SDL_WINDOW_SHOWN
    );

    SDL_Surface* pWinSurf = SDL_GetWindowSurface(pWindow);  //le sprite qui couvre tout l'ecran
    SDL_Surface* pSpriteTourSol = SDL_LoadBMP("./data/TourSol.bmp");  //indice 0 dans tabSprite (via l'enum TuniteDuJeu)
    SDL_Surface* pSpriteTourAir = SDL_LoadBMP("./data/TourAir.bmp");  //indice 1 dans tabSprite (via l'enum TuniteDuJeu)
    SDL_Surface* pSpriteTourRoi = SDL_LoadBMP("./data/TourRoi.bmp"); //indice 2
    SDL_Surface* pSpriteArcher = SDL_LoadBMP("./data/Archer.bmp"); //indice 3
    SDL_Surface* pSpriteChevalier = SDL_LoadBMP("./data/Chevalier.bmp"); //indice 4
    SDL_Surface* pSpriteDragon = SDL_LoadBMP("./data/Dragon.bmp"); //indice 5
    SDL_Surface* pSpriteGargouille = SDL_LoadBMP("./data/Gargouille.bmp"); //indice 6
    SDL_Surface* pSpriteEau = SDL_LoadBMP("./data/Eau.bmp"); //indice 7  Ne figure pas dans l'enum TuniteDuJeu
    SDL_Surface* pSpriteHerbe = SDL_LoadBMP("./data/Herbe.bmp"); //indice 8 idem
    SDL_Surface* pSpritePont = SDL_LoadBMP("./data/Pont.bmp"); //indice 9 idem
    SDL_Surface* pSpriteTerre = SDL_LoadBMP("./data/Terre.bmp"); //indice 10 idem

    SDL_Surface* TabSprite[11]={pSpriteTourSol,pSpriteTourAir,pSpriteTourRoi,pSpriteArcher,pSpriteChevalier,pSpriteDragon,pSpriteGargouille,pSpriteEau,pSpriteHerbe,pSpritePont,pSpriteTerre};

    int** tabParcours=initChemin();  //tabParcours est un tableau de NBCOORDPARCOURS cases, chacune contenant un tableau de 2 cases (indice 0 pour X, indice 1 pour Y)

    if ( pSpriteTourSol )  //si le permier sprite a bien ete charge, on suppose que les autres aussi
    {
        TplateauJeu jeu = AlloueTab2D(LARGEURJEU,HAUTEURJEU);
        initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);
        affichePlateauConsole(jeu,LARGEURJEU,HAUTEURJEU);

        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
        maj_fenetre(pWindow);

        message("Welcome in TowerDfend","Ceci est un point de depart pour votre future interface de votre jeu TowerDefend");
        message("et fin","ECHAP->quitter, S/C ET D/V les gerer les sauvegardes");

        //DEFINISSEZ/INITIALISER ICI VOS VARIABLES
        int cont = 1;
        int toucheCAppuyee = 0;
        int toucheVAppuyee = 0;
        int toucheSAppuyee = 0;
        int toucheDAppuyee = 0;
        int numeroTour = 0;

        TListePlayer playerRoi = NULL;
        TListePlayer playerHorde = NULL;

        AjouterUnite(&playerRoi, creeTourRoi(tabParcours[NBCOORDPARCOURS-1][X], tabParcours[NBCOORDPARCOURS-1][Y]));

        AjouterUnite(&playerHorde, creeDragon(tabParcours[0][X], tabParcours[0][Y]));

        // boucle principale du jeu

        while ( cont != 0 ){   //VOUS DEVEZ GERER (DETECTER) LA FIN DU JEU -> tourRoiDetruite
                SDL_PumpEvents(); //do events

                //APPELEZ ICI VOS FONCTIONS QUI FONT EVOLUER LE JEU

                initPlateauAvecNULL(jeu, LARGEURJEU, HAUTEURJEU);
                PositionnePlayerOnPlateau(playerRoi, jeu);
                PositionnePlayerOnPlateau(playerHorde, jeu);

                //remettre les attaques disponibles
                resetPeutAttaquer(playerRoi, numeroTour);
                resetPeutAttaquer(playerHorde, numeroTour);

                //phase de combat
                attaquePlayer(pWinSurf, playerRoi, &playerHorde, jeu);
                attaquePlayer(pWinSurf, playerHorde, &playerRoi, jeu);

                //le deplacement
                deplaceHorde(playerHorde, tabParcours, jeu);

                //creation des unites de la horde
                if (rand() % 100 < 50){
                        creerUniteHorde(&playerHorde, tabParcours, jeu);
                }

                //creation des tours du roi
                if (rand() % 100 < 15 && compterUnites(playerRoi) < 6){
                        creerTourDefenseRoi(&playerRoi, tabParcours, jeu);
                }

                if (tourRoiDetruite(playerRoi)){
                message("GAME OVER", "La tour du roi est detruite");
                 cont = 0;
                }

                efface_fenetre(pWinSurf);
                prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);



                //affichage du jeu à chaque tour
                numeroTour++;

                maj_fenetre(pWindow);
                SDL_Delay(300);  //valeur du delai a modifier eventuellement

                //LECTURE DE CERTAINES TOUCHES POUR LANCER LES RESTAURATIONS ET SAUVEGARDES
                const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
                if ( pKeyStates[SDL_SCANCODE_V] && toucheVAppuyee == 0 ){

                        printf("Touche V detectee : chargement texte\n");

                        chargementTexte(&playerRoi, &playerHorde, tabParcours);

                        message("Chargement", "Chargement texte effectue");

                        initPlateauAvecNULL(jeu, LARGEURJEU, HAUTEURJEU);
                        PositionnePlayerOnPlateau(playerRoi, jeu);
                        PositionnePlayerOnPlateau(playerHorde, jeu);

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);

                        toucheVAppuyee = 1;
                }

                if (!pKeyStates[SDL_SCANCODE_V]){
                        toucheVAppuyee = 0;
                }

                if ( pKeyStates[SDL_SCANCODE_C] && toucheCAppuyee == 0 ){

                        printf("Touche C detectee : chargement binaire\n");

                        chargementBinaire(&playerRoi, &playerHorde, tabParcours);

                        message("Chargement", "Chargement binaire effectue");

                        initPlateauAvecNULL(jeu, LARGEURJEU, HAUTEURJEU);
                        PositionnePlayerOnPlateau(playerRoi, jeu);
                        PositionnePlayerOnPlateau(playerHorde, jeu);

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);

                        toucheCAppuyee = 1;
                }

                if (!pKeyStates[SDL_SCANCODE_C]){
                        toucheCAppuyee = 0;
                }

                if ( pKeyStates[SDL_SCANCODE_D] && toucheDAppuyee == 0 ){

                        printf("Touche D detectee : sauvegarde texte\n");

                        sauvegardeTexte(playerRoi, playerHorde, tabParcours);

                        message("Sauvegarde", "Sauvegarde texte effectue");

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);

                        toucheDAppuyee = 1;
                }

                if (!pKeyStates[SDL_SCANCODE_D]){
                        toucheDAppuyee = 0;
                }

                if ( pKeyStates[SDL_SCANCODE_S] && toucheSAppuyee == 0 ){

                        printf("Touche S detectee : sauvegarde binaire\n");

                        message("Sauvegarde", "Sauvegarde binaire effectue");

                        sauvegardeBinaire(playerRoi, playerHorde, tabParcours);

                        //Ne pas modifiez les 4 lignes ci-dessous
                        efface_fenetre(pWinSurf);
                        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                        maj_fenetre(pWindow);
                        SDL_Delay(300);

                        toucheSAppuyee = 1;
                }

                if (!pKeyStates[SDL_SCANCODE_S]){
                        toucheSAppuyee = 0;
                }

                if ( pKeyStates[SDL_SCANCODE_ESCAPE] ){
                        cont = 0;  //sortie de la boucle
                }

        }
        //fin boucle du jeu

        freePlayer(playerRoi);
        freePlayer(playerHorde);
        freePlateau(jeu, LARGEURJEU);

        SDL_FreeSurface(pSpriteTourSol); // Liberation de la ressource occupee par le sprite
        SDL_FreeSurface(pSpriteTourAir);
        SDL_FreeSurface(pSpriteTourRoi);
        SDL_FreeSurface(pSpriteArcher);
        SDL_FreeSurface(pSpriteChevalier);
        SDL_FreeSurface(pSpriteDragon);
        SDL_FreeSurface(pSpriteGargouille);
        SDL_FreeSurface(pSpriteEau);
        SDL_FreeSurface(pSpriteHerbe);
        SDL_FreeSurface(pSpritePont);
        SDL_FreeSurface(pWinSurf);
    }
    else
    {
        fprintf(stdout,"échec de chargement du sprite (%s)\n",SDL_GetError());
    }

    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    freeChemin(tabParcours);
    return 0;
}
