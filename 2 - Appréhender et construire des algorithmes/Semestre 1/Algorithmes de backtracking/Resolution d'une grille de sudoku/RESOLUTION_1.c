/* Vous devez implémenter en C l’algorithme de backtracking suivant, en respectant les consignes suivantes :
    - votre programme devra gérer des grilles 4x4 (constante N=4).
    - votre programme devra :
    • lire un fichier de grille de sudoku 4x41
    • afficher la grille initiale,
    • résoudre la grille,
    • afficher la grille finale (grille complète),
    • afficher le temps CPU de l’étape de résolution.
    - vous testerez ce programme RESOLUTION_1 avec les grilles 4x4 disponibles sur
    Moodle
    - Voici l'algo :
    "constante entier N := 3;
    constante entier TAILLE := (N*N);
    type tGrille = tableau[TAILLE] [TAILLE] de entier;
    fonction backtracking(tGrille grille, int numeroCase) délivre booléen c'est
        ligne : entier;
        colonne : entier;
        resultat : booléen;
    début
        resultat := FAUX;
        si numeroCase = TAILLE * TAILLE alors
            //on a traité toutes les cases, la grille est résolue
            resultat := VRAI;
        sinon
            // On récupère les "coordonnées" de la case
            ligne := numeroCase / TAILLE;
             colonne := numeroCase % TAILLE;
            si grille[ligne][colonne]!=0 alors
                // Si la case n’est pas vide, on passe à la suivante
                // (appel récursif)
                resultat := backtracking(grille, numeroCase+1);
            sinon
                pour valeur de 1 à TAILLE faire
                    si absentSurLigne(valeur,grille,ligne) ET absentSurColonne(valeur,grille,colonne) ET absentSurBloc(valeur,grille,ligne,colonne) alors
                        // Si la valeur est autorisée on l'inscrit dans la case...
                        grille[ligne][colonne] := valeur;
                        // ... et on passe à la suivante : appel récursif
                        // pour voir si ce choix est bon par la suite
                        si backtracking(grille,numeroCase+1) = VRAI alors
                            resultat := VRAI;
                        sinon
                            grille[ligne][colonne] := 0;
                        finSi
                    finSi
                finFaire
            finSi
        finSi
        retourne resultat;
    fin"
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define N 4
#define TAILLE (N*N)
typedef int tGrille[TAILLE][TAILLE];

void chargerGrille(tGrille g);
void afficherGrille(tGrille g);
bool possible(tGrille grille, int numLigne, int numColonne, int valeur);
bool backtracking(tGrille grille, int numeroCase);

int main()
{
    tGrille g;

    chargerGrille(g);
    printf("Grille initiale\n");
    afficherGrille(g);
    
    clock_t begin = clock();
    for (int i=0; i<N*N; i++)
    {
        backtracking(g, i);
    }
    clock_t end = clock();

    printf("Grille finale\n");
    afficherGrille(g);
    double tmpsCPU = (end - begin)*1.0 / CLOCKS_PER_SEC;
    printf( "Temps CPU = %.3f secondes\n",tmpsCPU);
}

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

void afficherGrille(tGrille g)
{
    int compteurLig = 0;
    int compteurCol = 0;

    for (int i=0; i<N; i++)
    {
        printf("+------------");
    }
    printf("+\n");

    for (int lig=0; lig<N*N; lig++)
    {
        compteurCol = 0;

        if (compteurLig == N)
        {
            for (int i=0; i<N; i++)
            {
                printf("+------------");
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
        printf("+------------");
    }
    printf("+\n\n");
}

bool possible(tGrille grille, int numLigne, int numColonne, int valeur) {
    int lig, col;

    // Vérification de la ligne
    for (lig = 0; lig < TAILLE; lig++) {
        if (grille[numLigne][lig] == valeur) {
            return false;
        }
    }

    // Vérification de la colonne
    for (lig = 0; lig < TAILLE; lig++) {
        if (grille[lig][numColonne] == valeur) {
            return false;
        }
    }

    // Calcul des indices de début du bloc
    int debutLigne = numLigne - (numLigne % N);
    int debutColonne = numColonne - (numColonne % N);

    // Vérification du bloc
    for (lig = debutLigne; lig < debutLigne + N; lig++) {
        for (col = debutColonne; col < debutColonne + N; col++) {
            if (grille[lig][col] == valeur) {
                return false;
            }
        }
    }

    // Si la valeur n'est présente nulle part
    return true;
}

bool backtracking(tGrille grille, int numeroCase) {
    int ligne, colonne;
    bool resultat = false;

    if (numeroCase == TAILLE * TAILLE) {
        return true; // Toutes les cases ont été traitées, la grille est résolue
    } else {
        ligne = numeroCase / TAILLE;
        colonne = numeroCase % TAILLE;

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
    }

    return resultat;
}
