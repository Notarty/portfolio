/**
* \file src2.c
* \brief Exemples supplémentaires de commentaires Doxygen pour différents éléments de code en C.
* \author VotreNom
* \version 1.0
* \date 7 décembre 2023
*/

#include <stdio.h>

/**
* \def NUM_DEPART
* \brief Constante représentant le numéro de la ville de départ.
*/
#define VILLE1 1

/**
* \def NUM_ARRIVE
* \brief Constante représentant le numéro de la ville d'arrivé.
*/
#define VILLE2 2

/**
* \def TMAX
* \brief Constante pour la taille maximale d'un tableau de villes.
*/
#define TMAX 100

/**
* \typedef t_villes
* \brief Tableaux contentant des éléments de type Ville.
*
* Liste des villes.
*/
typedef Ville t_villes[TMAX];

/**
* \typedef nbHabitants
* \brief Type représentant le nombre d'habitants d'une ville.
*
* Nombre d'habitants pour une ville.
*/
typedef int nbHabitants;

/**
* \struct Point
* \brief Structure représentant un point dans un espace 2D.
*/
typedef struct {
    int x; /*!< Coordonnée x du point */
    int y; /*!< Coordonnée y du point */
} Point;

/**
* \struct Ville
* \brief Structure représentant une ville.
*/
typedef struct {
    char nom[20];
    float taille;
} Ville;

/**
* \fn int calculerDistance(Point p1, Point p2)
* \brief Calcule la distance entre deux points dans un espace 2D.
* \param p1 : Premier point
* \param p2 : Deuxième point
* \return La distance entre les deux points
*/
int calculerDistance(Point p1, Point p2) {
    /**
     * \var distance
     * \brief Variable de type Point stockant les informations relatives à la distance
     * \see Point
    */
    int distance = sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
    return distance;
}

/**
* \fn char recupNomVille(t_villes t, int indice)
* \brief Récupère le nom de la ville à l'indice mis en paramètre.
* \param t : Tableau de villes
* \param indice : Indice de la ville à récupérer
* \return Le nom de la ville
*/
char recupNomVille(t_villes t, int indice)
{
    /**
     * \var ville
     * \brief Variable faisant référence à une ville à récupérer dans le tableau
     * \see Ville
    */
    Ville ville;

    ville = t[indice];
    
    return ville.nom;
}

int main() {
    Point point1 = {0, 0};
    Point point2 = {3, 4};

    int distance = calculerDistance(point1, point2);
    printf("Distance entre les points : %d\n", distance);

    return 0;
}