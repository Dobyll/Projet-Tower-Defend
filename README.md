# Tower Defend – Jeu de stratégie en C avec SDL2

Projet universitaire réalisé en binôme en L2 Informatique à l'Université de Poitiers.

## Le jeu
Une horde d'unités (archers, chevaliers, dragons, gargouilles) suit un chemin sur un plateau de 11 × 19 cases pour détruire la tour du Roi. Le Roi se défend avec des tours au sol et des tours aériennes.

## Fonctionnalités
- Déplacement de la horde le long d'un chemin prédéfini
- Combats selon la portée, la vitesse d'attaque et le type de cible (sol / air) ; chaque unité attaque la cible la plus faible à sa portée
- Placement automatique des tours de défense sur les cases les plus stratégiques
- Sauvegarde et chargement d'une partie en fichier binaire et en fichier texte
- Affichage graphique avec SDL2 et affichage en mode console

## Notions utilisées
- Langage C : structures, pointeurs, allocation dynamique (tableau 2D, listes chaînées), libération de la mémoire
- Lecture et écriture de fichiers binaires et texte

## Répartition du code
- **Fournis par l'enseignant** : le module d'affichage SDL (`maSDL.c`, `maSDL.h`), l'en-tête `towerdefend.h` et la structure de `main.c`
- **Écrits par le binôme** : l'ensemble de `towerdefend.c` (logique du jeu, combats, déplacements, placement des tours, sauvegarde et chargement) et le déroulement de la partie dans `main.c`

## Compilation
- **Windows** : ouvrir `projetTowerDefend.cbp` avec Code::Blocks (SDL2 pour MinGW requis).
- **Linux** : `gcc *.c -o towerdefend $(sdl2-config --cflags --libs)`

## Auteurs
- Folawe SABINO
- Saidou MAMADOU DIALLO
