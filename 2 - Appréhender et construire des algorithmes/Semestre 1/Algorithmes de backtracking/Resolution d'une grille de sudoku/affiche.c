#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 4
#define TAILLE (N*N)
typedef int tGrille[TAILLE][TAILLE];

/*void chargerGrille(tGrille g){
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
void afficherGrille(tGrille g) {
    int lig, col;
    // Calcul du nombre de tirets à afficher
    int nombreTirets = 5 * TAILLE + N + 1;
    // Affichage de la ligne supérieure
    printf("   +");
    for (col = 0; col < nombreTirets; col++) {
        if ((col + 1) % (N + 1) == 0 && col < nombreTirets - 1) {
            printf("+");
        } else {
            printf("-");
        }
    }
    printf("\n");
    // Boucle pour parcourir chaque ligne de la grille
    for (lig = 0; lig < TAILLE; lig++) {
        printf("   | ");
        // Boucle pour parcourir chaque colonne de la grille
        for (col = 0; col < TAILLE; col++) {
            // Affichage de la valeur de la case ou d'un point si la case est vide
            if (g[lig][col] == 0) {
                printf(".  ");
            } else if (g[lig][col] < 10) {
                printf("%d  ", g[lig][col]);
            } else {
                printf("%d ", g[lig][col]);
            }
            // Affichage d'une barre verticale tous les N chiffres
            if ((col + 1) % N == 0 && col < TAILLE - 1) {
                printf("| ");
            }
        }
        printf("|\n");
        // Affichage des lignes intermédiaires
        if ((lig + 1) % N == 0 && lig < TAILLE - 1) {
            printf("   +");
            for (col = 0; col < nombreTirets - 1; col++) {
                if ((col + 1) % (N + 1) == 0 && col < nombreTirets - 2) {
                    printf("+");
                } else {
                    printf("-");
                }
            }
            printf("\n");
        }
    }
    // Affichage de la ligne inférieure
    printf("   +");
    for (col = 0; col < nombreTirets; col++) {
        if ((col + 1) % (N + 1) == 0 && col < nombreTirets - 1) {
            printf("+");
        } else {
            printf("-");
        }
    }
    printf("\n");
}
*/
void afficherGrille(tGrille g) {
    int lig, col;
    // Calcul du nombre de tirets à afficher
    int nombreTirets = 4 * N + 1;
    // Affichage de la ligne supérieure
    printf("+");
    for (col = 0; col < TAILLE; col++) {
        if ((col + 1) % N == 0 && col < TAILLE - 1) {
            printf("----+");
        } else {
            printf("----");
        }
    }
    printf("\n");
    // Boucle pour parcourir chaque ligne de la grille
    for (lig = 0; lig < TAILLE; lig++) {
        // Boucle pour parcourir chaque colonne de la grille
        for (col = 0; col < TAILLE; col++) {
            // Affichage de la valeur de la case ou d'un point si la case est vide
            if (g[lig][col] == 0) {
                printf("| . ");
            } else if (g[lig][col] < 10) {
                printf("| %d ", g[lig][col]);
            } else {
                printf("| %d", g[lig][col]);
            }
            // Affichage d'une barre verticale tous les N chiffres
            if ((col + 1) % N == 0 && col < TAILLE - 1) {
                printf("|");
            }
        }
        printf("|\n");
        // Affichage des lignes intermédiaires
        if ((lig + 1) % N == 0 && lig < TAILLE - 1) {
            printf("+");
            for (col = 0; col < TAILLE; col++) {
                if ((col + 1) % N == 0 && col < TAILLE - 1) {
                    printf("----+");
                } else {
                    printf("----");
                }
            }
            printf("\n");
        }
    }
}
int main() {
    tGrille grille1;
    chargerGrille(grille1);
    afficherGrille(grille1);
    return EXIT_SUCCESS;
}