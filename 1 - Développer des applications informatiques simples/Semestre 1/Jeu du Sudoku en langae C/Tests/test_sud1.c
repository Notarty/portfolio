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
    int candidats[TAILLE];
    int nbCandidats;
} tCase1;

/*
procédure ajouterCandidat( entF/sortF laCase : tCase1, entF val:entier) c'est 
//ajoute la valeur val à la liste des candidats de la case passée en paramètre d’entrée/sortie
debut
    
*/
/*
procédure retirerCandidat( entF/sortF laCase : tCase1,entF val : entier) c'est 
//supprime la valeur val de la liste des candidats de la case passée en paramètred’entrée/sortie
*/
/*
fonction estCandidat( entF laCase : tCase1,entF val : entier) délivre booléen c'est 
//retourne vrai si val est l’un des candidats de la case passée en paramètre d’entréeet faux sinon
*/
/*
fonction nbCandidats(entF laCase : tCase1) délivre entier c'est 
// retourne le nombre de candidats de la case passée en paramètre d’entrée.
*/
