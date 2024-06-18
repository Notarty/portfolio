/**
* \file src1.c
* \brief Ce fichier contient des exemples de commentaires Doxygen pour les différentes parties du code en C.
* \author VotreNom
* \version 1.0
* \date 7 décembre 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
* \def TMAX
* \brief Constante pour la taille maximale d'un tableau.
*/
#define TMAX 100

/**
* \def BON
* \brief Constante pour le nombre de fruits et légumes à manger par jour
*/
#define BON 5

/**
* \typedef typTab
* \brief Type tableau de TMAX caractères.
*
* Le type typTab sert de stockage provisoire pour ordonner
* les éléments (caractères) d’une liste.
*/
typedef char typTab[TMAX];

/**
* \typedef nomFruits
* \brief Type pour les noms des fruits
*
* Permet de connaître le nom des fruits.
*/
typedef char nomFruits;

/**
* \struct fiche
* \brief Structure des informations sur un patient.
*/
typedef struct {
    char no[15]; /*!< Numéro de sécurité sociale du patient */
    char nom[15]; /*!< Son nom */
    char prenom[15]; /*!< Son prénom */
    int age; /*!< Son âge */
} fiche;

/**
* \struct alimentation
* \brief Structure de l'alimentation des patients
*/
typedef struct {
    int fruits;
    int legumes;
} alimentation;

/**
* \fn bool estV(char* ch)
* \brief Fonction qui indique si une chaîne est vide.
* \param ch : la chaîne à tester.
* \return true si la chaîne est vide, false sinon.
* Consiste à vérifier si la chaîne est NULL.
*/
bool estV(char* ch) {
    /**
     * \var test
     * \brief Permet de tester l'alimentation du patient
    */
    bool test;

    /**
     * \see bool bonneAlim(int nbFruits, int nbLegumes)
    */
    test = bonneAlim(5, 6);

    return (ch == NULL);
}

/**
* \fn bool bonneAlim(int nbFruits, int nbLegumes)
* \brief Fonction qui indique si un patient mange 5 fruits et légumes par jour
* \param nbFruits : nombre de fruits mangés par le patient
* \param nbLegumes : nombre de légumes mangés par le patient
* \return true si le patient mange au moins 5 fruits et légumes par jour, false sinon.
*/
bool bonneAlim(int nbFruits, int nbLegumes)
{
    /**
     * \var alim
     * \brief stocke les informations relatives aux fruits et légumes
     * \see aliimentation
    */
    alimentation alim;

    alim.fruits = nbFruits;
    alim.legumes = nbLegumes;

    return(nbFruits >= BON) && (nbLegumes >= BON);
}

int main() {
    // Exemple d'utilisation des structures et des fonctions définies ci-dessus
    fiche patient;
    patient.age = 30;
    strcpy(patient.nom, "Doe");
    strcpy(patient.prenom, "John");
    strcpy(patient.no, "123456789012345");

    printf("Nom: %s\n", patient.nom);
    printf("Prénom: %s\n", patient.prenom);
    printf("Âge: %d\n", patient.age);
    printf("Numéro de sécurité sociale: %s\n", patient.no);

    // Test de la fonction estV
    char chaineTest[100] = "Bonjour";
    bool estVide = estV(chaineTest);
    if (estVide)
        printf("La chaîne est vide\n");
    else
        printf("La chaîne n'est pas vide\n");

    return EXIT_SUCCESS;
}
