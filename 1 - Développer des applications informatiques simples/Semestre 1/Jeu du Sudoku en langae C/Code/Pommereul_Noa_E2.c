/**
 * \brief Programme principal pour résoudre un Sudoku en C.
 * \author Pommereul Noa
 * \version 1.0
 * \date 26 novembre 2023
 *
 * Ce programme permet de résoudre un Sudoku de taille N*N,
 * a partir d'une grille se trouvant dans un autre fichier.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Définition de la taille de la grille (9x9 pour le Sudoku classique).
/**
* \def N
* \brief Constante pour le format de la grille.
*
*/
#define N 3

/**
* \def TAILLE
* \brief Constante pour la taille de la grille.
*
*/
#define TAILLE (N*N)

/**
* \typedef tGrille
* \brief type tableau en 2D de [TAILLE][TAILLE] caractères
*
* Le type typTab sert de stockage pour la grille de sudoku
* qui est charger a partir d'un fichier.
*
*/
typedef int tGrille[TAILLE][TAILLE];

//prototypes
void chargerGrille(tGrille g);
void afficherGrille(tGrille g);
void saisir(int *valeur);
bool possible(tGrille grille, int numLigne, int numColonne, int valeur);
bool grillePleine(tGrille grille);

/*****************************************************
 *                PROGRAMME PRINCIPAL                *
*****************************************************/

/**
* \fn int main()
* \brief Programme principal.
* \return Code de sortie du programme (0 : sortie normale).
* 
* Le programme principal permet d'appeller les fonctions permettant de jouer au jeu du sudoku.
*
*/
int main() {
    tGrille grille1;
    int numLigne, numColonne, valeur;

    chargerGrille(grille1);

    while(!grillePleine(grille1)) {
        afficherGrille(grille1);
        printf("Indices de la case ?\n");
        saisir(&numLigne);
        saisir(&numColonne);
        if (grille1[numLigne-1][numColonne-1] != 0) {
            printf("IMPOSSIBLE, la case n'est pas libre.\n");
        } else {
            printf("Valeur a inserer ? ");
            saisir(&valeur);
            if (possible(grille1, numLigne-1, numColonne-1, valeur)) {
                grille1[numLigne-1][numColonne-1] = valeur;
            }
        }
    }
    afficherGrille(grille1);
    printf("Grille pleine, fin de partie");
    return EXIT_SUCCESS;
}

/*****************************************************
 *     FONCTIONS UTILES POUR MANIPULER LA GRILLE     *
*****************************************************/

/**
 * \fn void chargerGrille(tGrille g)
 * \brief Affiche la grille de Sudoku.
 * \param g Grille à afficher.
 * 
 * Charger la grille a partir d'un fichier extérieur.
 * 
*/
void chargerGrille(tGrille g){
    char nomFichier[30];
    FILE * f;

    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
    if (f==NULL) {
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
        exit(EXIT_FAILURE);
    } else {
        fread(g, sizeof(int), TAILLE*TAILLE, f);
    }
    fclose(f);
}

/**
 * \fn void afficherGrille(tGrille g)
 * \brief Affiche la grille de Sudoku.
 * \param g Grille à afficher.
 * 
 * Affiche la grille de Sudoku selon un affichage défini dans le maquettage.
*/
void afficherGrille(tGrille g) {
    int lig, col;
    // Affichage des numéros des colonnes
    printf("   ");
    for (col = 0; col < TAILLE; col++) {
        if ((col + 1 == 3) || (col + 1 == 6)) {
            printf(" %d  ", col + 1);
            col++;
        }
        printf(" %d", col + 1);
    }
    printf("\n");
    // Affichage de la ligne supérieure
    printf("  +-------+-------+-------+\n");
    // Boucle pour parcourir chaque ligne de la grille
    for (lig = 0; lig < TAILLE; lig++) {
        // Affichage du numéro de la ligne
        printf("%d | ", lig + 1);
        // Boucle pour parcourir chaque colonne de la grille
        for (col = 0; col < TAILLE; col++) {
            // Affichage de la valeur de la case ou d'un point si la case est vide
            if (g[lig][col] == 0) {
                printf(". ");
            } else {
                printf("%d ", g[lig][col]);
            }
            // Affichage d'une barre verticale tous les 3 chiffres
            if ((col + 1) % 3 == 0 && col < TAILLE - 1) {
                printf("| ");
            }
        }
        printf("|");
        // Passage à la ligne suivante
        printf("\n");
        // Affichage d'une ligne horizontale tous les 3 lignes
        if ((lig + 1) % 3 == 0 && lig < TAILLE - 1) {
            printf("  +-------+-------+-------+\n");
        }
    }
    // Affichage de la ligne inférieure
    printf("  +-------+-------+-------+\n");
}

/**
 * \fn int estValide(int valeur)
 * \brief Vérifie si la valeur est dans la plage autorisée (entre 1 et TAILLE).
 * \param valeur Valeur à vérifier.
 * \return 1 si la valeur est valide, sinon 0.
 * \see saisir(int *valeur)
 * 
 * la fonction est utilisée par saisir(int *valeur).
*/
int estValide(int valeur) {
    return (valeur >= 1 && valeur <= TAILLE);
}

/**
 * \fn void saisir(int *valeur)
 * \brief Procédure pour saisir une valeur entière entre 1 et TAILLE. 
 * \param valeur Pointeur vers la valeur saisie.
*/
void saisir(int *valeur) {
    char chaine[100]; // Taille aléatoire pour stocker la saisie utilisateur
    int tempValeur;
    bool valide = false;

    while (!valide) {
        printf("Entrez une valeur entre 1 et %d : ", TAILLE);
        scanf("%s", chaine);

        // Vérification si la saisie est un entier compris entre 1 et TAILLE
        if (sscanf(chaine, "%d", &tempValeur) == 1 && estValide(tempValeur)) {
            *valeur = tempValeur;
            valide = true; // La saisie est valide, on sort de la boucle
        } else {
            printf("La valeur saisie n'est pas valide. Veuillez entrer un entier entre 1 et %d.\n", TAILLE);
        }
    }
}

/**
 * \fn bool possible(tGrille grille, int numLigne, int numColonne, int valeur)
 * \brief Vérifie si une valeur peut être ajoutée à une case particulière de la grille.
 * \param grille Grille de Sudoku.
 * \param numLigne Numéro de la ligne.
 * \param numColonne Numéro de la colonne.
 * \param valeur Valeur à vérifier.
 * \return true si la valeur peut être ajoutée à la case, sinon false.
*/
bool possible(tGrille grille, int numLigne, int numColonne, int valeur) {
    int lig, col;

    // Vérification de la ligne
    for (lig = 0; lig < TAILLE; lig++) {
        if (grille[numLigne][lig] == valeur) {
            printf("La valeur est deja presente sur la meme ligne.\n");
            return false;
        }
    }

    // Vérification de la colonne
    for (lig = 0; lig < TAILLE; lig++) {
        if (grille[lig][numColonne] == valeur) {
            printf("La valeur est deja presente sur la meme colonne.\n");
            return false;
        }
    }

    // Calcul des indices de début du bloc
    int debutLigne = numLigne - (numLigne % 3);
    int debutColonne = numColonne - (numColonne % 3);

    // Vérification du bloc
    for (lig = debutLigne; lig < debutLigne + 3; lig++) {
        for (col = debutColonne; col < debutColonne + 3; col++) {
            if (grille[lig][col] == valeur) {
                printf("La valeur est deja presente dans le meme bloc.\n");
                return false;
            }
        }
    }

    // Si la valeur n'est présente nulle part
    return true;
}

/**
 * \fn bool grillePleine(tGrille grille)
 * \brief Vérifie si la grille de Sudoku est pleine.
 * \param grille Grille de Sudoku.
 * \return true si la grille est pleine, sinon false.
 */
bool grillePleine(tGrille grille) {
    int lig, col;

    // Parcours de chaque case de la grille
    for (lig = 0; lig < TAILLE; lig++) {
        for (col = 0; col < TAILLE; col++) {
            // Si une case est vide (contient 0), la grille n'est pas pleine
            if (grille[lig][col] == 0) {
                return false;
            }
        }
    }

    // Si aucune case n'est vide, la grille est pleine
    return true;
}