#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Définition de la taille de la grille (9x9 pour le Sudoku classique)
#define N 3
#define TAILLE (N*N)

//types
typedef int tGrille[TAILLE][TAILLE];

typedef struct {
    int valeur;
    bool candidats[TAILLE+1]; // la case d’indice 0
                              // est neutralisée
    int nbCandidats;
} tCase2;