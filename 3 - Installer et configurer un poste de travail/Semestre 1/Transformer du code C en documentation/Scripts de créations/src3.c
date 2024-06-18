/**
* \file src3.c
* \brief Autres exemples de commentaires Doxygen pour différents aspects du code en C.
* \author VotreNom
* \version 1.0
* \date 7 décembre 2023
*/

#include <stdio.h>

/**
* \def MAX_SIZE
* \brief Taille maximale pour une structure de données.
*/
#define MAX_SIZE 50

/**
* \def JOUR_MAX
* \brief Nombre de jours maximum en un mois.
*/
#define JOUR_MAX 31

/**
* \typedef Jour
* \brief Type représentant un jour du mois.
*/
typedef int Jour;

/**
* \typedef t_jours
* \brief Tableau de jours du mois.
*/
typedef Jour t_jours[JOUR_MAX];

/**
* \struct Data
* \brief Type représentant des données.
*/
typedef struct {
    int id; /*!< Identifiant de données */
    char name[MAX_SIZE]; /*!< Nom associé aux données */
    float value; /*!< Valeur des données */
} Data;

/**
* \struct Mois
* \brief Type représentant les mois.
*/
typedef struct {
    char nom;
    int nbJours;
} Mois;

/**
* \fn void afficherDonnees(Data* data)
* \brief Affiche les détails des données.
* \param data : Pointeur vers les données à afficher.
*/
void afficherDonnees(Data* data) {
    printf("ID: %d\n", data->id);
    printf("Nom: %s\n", data->name);
    printf("Valeur: %.2f\n", data->value);
}

/**
* \fn Jour recupAnniversaire(t_jours t, int indice)
* \brief Récupère le jour d'anniversaire.
* \param t : tableaux des jours.
* \param indice : indice du jour d'anniversaire
* \return Le jour d'anniversaire à l'indice saisie par l'utilisateur.
* \see Jour
* \see t_jours
*/
Jour recupAnniversaire(t_jours t, int indice)
{
    /**
     * \var jourCible
     * \brief Stocke les informations relatives au jour choisi par l'utilisateur
    */
    Jour jourCible = t[indice];
    return jourCible;
}

int main() {
    /**
     * \var donnees
     * \brief Variable stockant les données
    */
    Data donnees = {1, "Exemple", 25.5};
    afficherDonnees(&donnees);

    return 0;
}
