#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define N 4
#define TAILLE (N * N)
typedef int tGrille[TAILLE][TAILLE];

void chargerGrille(tGrille g) {
    char nomFichier[30];
    FILE *f;

    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
    if (f == NULL) {
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
        exit(EXIT_FAILURE);
    } else {
        fread(g, sizeof(int), TAILLE * TAILLE, f);
    }
    fclose(f);
}

// Fonction pour vérifier si une valeur est possible dans une cellule
bool possible(tGrille grille, int numLigne, int numColonne, int valeur) {
    int debutLigne = numLigne - (numLigne % N);
    int debutColonne = numColonne - (numColonne % N);

    // Vérification de la ligne, de la colonne et du bloc
    for (int i = 0; i < TAILLE; i++) {
        if (grille[numLigne][i] == valeur || grille[i][numColonne] == valeur ||
            grille[debutLigne + i / N][debutColonne + i % N] == valeur) {
            return false;
        }
    }

    return true;
}

// Fonction pour effectuer le backtracking avec les optimisations
bool backtracking(tGrille grille, int numeroCase) {
    if (numeroCase == TAILLE * TAILLE) {
        return true; // Toutes les cases ont été traitées, la grille est résolue
    }

    int ligne = numeroCase / TAILLE;
    int colonne = numeroCase % TAILLE;

    if (grille[ligne][colonne] != 0) {
        return backtracking(grille, numeroCase + 1); // Case non vide, on passe à la suivante
    } else {
        for (int valeur = 1; valeur <= TAILLE; valeur++) {
            if (possible(grille, ligne, colonne, valeur)) {
                grille[ligne][colonne] = valeur; // Essayer la valeur

                if (backtracking(grille, numeroCase + 1)) {
                    return true; // Si le choix est bon, retourne vrai
                } else {
                    grille[ligne][colonne] = 0; // Sinon, réinitialise la case
                }
            }
        }
    }

    return false;
}

void afficherGrille(tGrille g) {
    int compteurLig = 0;
    int compteurCol = 0;

    for (int i=0; i<N; i++)
    {
        printf("+");
        for (int j=0; j<N; j++)
        {
            printf("---");
        }
    }
    printf("+\n");

    for (int lig=0; lig<N*N; lig++)
    {
        compteurCol = 0;

        if (compteurLig == N)
        {
            for (int i=0; i<N; i++)
            {
                printf("+");
                for (int j=0; j<N; j++)
                {
                    printf("---");
                }
            }
            printf("+\n");
            compteurLig = 0;
        }
        printf("|");

        for (int col=0; col<N*N; col++)
        {
            if (compteurCol == N)
            {
                printf("|");
                compteurCol = 0;
            }
            if (g[lig][col] == 0)
            {
                printf(" . ");
            }
            else
            {
                if (g[lig][col] > 9)
                {
                    printf("%d ", g[lig][col]);
                }
                else
                {
                    printf(" %d ", g[lig][col]);
                }
            }
            compteurCol++;
        }
        printf("|");
        printf("\n");
        compteurLig++;
    }
    for (int i=0; i<N; i++)
    {
        printf("+");
        for (int j=0; j<N; j++)
        {
            printf("---");
        }
    }
    printf("+\n\n");
}

int main() {
    tGrille g;

    chargerGrille(g);
    printf("Grille initiale\n");
    afficherGrille(g);

    clock_t begin = clock();
    if (backtracking(g, 0)) {
        clock_t end = clock();
        printf("Grille finale\n");
        afficherGrille(g);
        double tmpsCPU = (end - begin) * 1.0 / CLOCKS_PER_SEC;
        printf("Temps CPU = %.3f secondes\n", tmpsCPU);
    } else {
        printf("Aucune solution n'existe pour cette grille.\n");
    }

    return EXIT_SUCCESS;
}

