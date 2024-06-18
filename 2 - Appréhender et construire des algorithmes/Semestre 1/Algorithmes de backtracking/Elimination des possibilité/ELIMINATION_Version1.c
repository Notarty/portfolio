#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 3
#define TAILLE (N * N)

typedef struct {
    int valeur;
    int candidats[TAILLE];
    int nbCandidats;
} tCase1;

typedef tCase1 tGrille[TAILLE][TAILLE];

int chargerGrille(tGrille g, char nomFichier[30]);
void afficherGrille(tGrille g);
bool possible(tGrille g, int numLigne, int numColonne, int valeur);
void initialiserCandidats(tGrille g, int *nbCandidatsTotal);
void ajouterCandidat(tCase1 *laCase, int val);
void retirerCandidat(tCase1 *laCase, int val);
bool estCandidat(tCase1 laCase, int val);
int nbCandidats(tCase1 laCase);
void retirerTousCandidats(tGrille g, int numLigne, int numColonne, int valeur, int *nbCandidatsElimines);
void afficherStats(char nomGrille[30], int nbCasesVides, int nbCasesRemplies, int nbCandidatsTotal, int nbCandidatsElimines);

int main() {
    tGrille g;
    bool progression;
    char nomGrille[30];
    int nbCasesVides;
    int nbCasesVidesTotal;
    int nbCasesRemplies = 0;
    int nbCandidatsTotal = 0;
    int nbCandidatsElimines = 0;
    int indice;

    nbCasesVides = chargerGrille(g, nomGrille);
    nbCasesVidesTotal = nbCasesVides;
    initialiserCandidats(g, &nbCandidatsTotal);
    progression = true;

    while ((nbCasesVides != 0) && (progression)) {
        progression = false;

        // Technique du singleton nu
        for (int lig = 0; lig < TAILLE; lig++) {
            for (int col = 0; col < TAILLE; col++) {
                if (g[lig][col].valeur == 0) {
                    if (nbCandidats(g[lig][col]) == 1) {
                        indice = 1;
                        while ((indice <= TAILLE) && (!(estCandidat(g[lig][col], indice)))) {
                            indice++;
                        }
                        g[lig][col].valeur = indice;
                        nbCasesVides--;
                        retirerTousCandidats(g, lig, col, indice, &nbCandidatsElimines);

                        nbCasesRemplies++;
                        progression = true;
                    }
                }
            }
        }
    }
    afficherGrille(g);
    afficherStats(nomGrille, nbCasesVidesTotal, nbCasesRemplies, nbCandidatsTotal, nbCandidatsElimines);

    return EXIT_SUCCESS;
}

int chargerGrille(tGrille g, char nomFichier[30]) {
    int valeursGrille[TAILLE][TAILLE];
    int nbCasesVides = 0;
    FILE * f;

    do{
        printf("Nom du fichier ? ");
        scanf("%s", nomFichier);
        f = fopen(nomFichier, "rb");
        if (f == NULL){
            printf("ERREUR sur le fichier %s\n", nomFichier);
            exit(EXIT_FAILURE);
        }else{
            fread(valeursGrille, sizeof(int), TAILLE*TAILLE, f);
        }
        printf("\n");
    }while (f == NULL);
    fclose(f);

    for (int lig=0; lig<TAILLE; lig++){
        for (int col=0; col<TAILLE; col++){
            g[lig][col].valeur = valeursGrille[lig][col];
            
            if (valeursGrille[lig][col] == 0){
                nbCasesVides++;
            }
        }
    }

    return nbCasesVides;
}

void afficherGrille(tGrille g)
{
    int compteurLig = 0;
    int compteurCol = 0;

    printf("   ");
    for (int col=1; col<=N*N; col++)
    {
        if (compteurCol == N)
        {
            printf(" ");
            compteurCol = 0;
        }
        printf(" %d ", col);
        compteurCol++;
    }

    printf("\n");
    printf("  +---------+---------+---------+\n");

    for (int lig=0; lig<N*N; lig++)
    {
        compteurCol = 0;

        if (compteurLig == N)
        {
            printf("  +---------+---------+---------+\n");
            compteurLig = 0;
        }
        printf("%d |", lig+1);

        for (int col=0; col<N*N; col++)
        {
            if (compteurCol == N)
            {
                printf("|");
                compteurCol = 0;
            }
            if (g[lig][col].valeur == 0)
            {
                printf(" . ");
            }
            else
            {
                printf(" %d ", g[lig][col].valeur);
            }
            compteurCol++;
        }
        printf("|");
        printf("\n");
        compteurLig++;
    }
    printf("  +---------+---------+---------+\n\n");
}

bool possible(tGrille g, int numLigne, int numColonne, int valeur) {
    // Vérification de la ligne
    for (int col = 0; col < TAILLE; col++) {
        if (g[numLigne][col].valeur == valeur) {
            return false;
        }
    }

    // Vérification de la colonne
    for (int lig = 0; lig < TAILLE; lig++) {
        if (g[lig][numColonne].valeur == valeur) {
            return false;
        }
    }

    // Détection du bloc 3x3 indiqué par les coordonnées
    int debutLigne = (numLigne / N) * N;
    int debutColonne = (numColonne / N) * N;

    for (int lig = debutLigne; lig < debutLigne + N; lig++) {
        for (int col = debutColonne; col < debutColonne + N; col++) {
            if (g[lig][col].valeur == valeur) {
                return false;
            }
        }
    }

    return true;
}


void initialiserCandidats(tGrille g, int *nbCandidatsTotal) {
    for (int lig=0; lig<TAILLE; lig++){
        for (int col=0; col<TAILLE; col++){
            if (g[lig][col].valeur == 0){
                g[lig][col].nbCandidats = 0;
                for (int i=1; i<=TAILLE; i++){
                    if (possible(g, lig, col, i)){
                        ajouterCandidat(&g[lig][col], i);
                    }
                    else{
                        g[lig][col].candidats[i] = false;
                    }
                }
            }else{
                g[lig][col].nbCandidats = 0;
                for (int i=1; i<=TAILLE; i++){
                    g[lig][col].candidats[i] = false;
                }
            }

            *nbCandidatsTotal += g[lig][col].nbCandidats;
        }
    }
}

void ajouterCandidat(tCase1 *laCase, int val) {
    laCase->candidats[laCase->nbCandidats] = val;
    laCase->nbCandidats++;
}

void retirerCandidat(tCase1 *laCase, int val) {
    bool candidatTrouve = false;
    for (int i = 0; i < laCase->nbCandidats; i++) {
        if (laCase->candidats[i] == val) {
            candidatTrouve = true;
            // Décalage des éléments suivants vers la gauche
            for (int j = i; j < laCase->nbCandidats - 1; j++) {
                laCase->candidats[j] = laCase->candidats[j + 1];
            }
            laCase->nbCandidats--;
        }
        // Si le candidat a été trouvé, on réduit l'index pour vérifier à nouveau l'élément actuel après le décalage
        if (candidatTrouve) {
            i--;
            candidatTrouve = false;
        }
    }
}


bool estCandidat(tCase1 laCase, int val) {
    for (int i = 0; i < laCase.nbCandidats; i++) {
        if (laCase.candidats[i] == val) {
            return true;
        }
    }
    return false;
}

int nbCandidats(tCase1 laCase) {
    return laCase.nbCandidats;
}

void retirerTousCandidats(tGrille g, int numLigne, int numColonne, int valeur, int *nbCandidatsElimines) {
    // Vérification de la ligne
    for (int col = 0; col < TAILLE; col++) {
        if (g[numLigne][col].valeur == 0 && estCandidat(g[numLigne][col], valeur)) {
            retirerCandidat(&g[numLigne][col], valeur);
            (*nbCandidatsElimines)++;
        }
    }

    // Vérification de la colonne
    for (int lig = 0; lig < TAILLE; lig++) {
        if (g[lig][numColonne].valeur == 0 && estCandidat(g[lig][numColonne], valeur)) {
            retirerCandidat(&g[lig][numColonne], valeur);
            (*nbCandidatsElimines)++;
        }
    }

    // Détection du bloc 3x3 indiqué par les coordonnées
    int debutLigne = (numLigne / N) * N;
    int debutColonne = (numColonne / N) * N;

    for (int lig = debutLigne; lig < debutLigne + N; lig++) {
        for (int col = debutColonne; col < debutColonne + N; col++) {
            if (g[lig][col].valeur == 0 && estCandidat(g[lig][col], valeur)) {
                retirerCandidat(&g[lig][col], valeur);
                (*nbCandidatsElimines)++;
            }
        }
    }
}

void afficherStats(char nomGrille[30], int nbCasesVides, int nbCasesRemplies, int nbCandidatsTotal, int nbCandidatsElimines) {
    printf("******   RESULTATS POUR %s   ******\n\n", nomGrille);
    printf("Nombre de cases remplies = %d sur %d\t", nbCasesRemplies, nbCasesVides);
    printf("Taux de remplissage = %.3f %%\n\n", 100.0*nbCasesRemplies/nbCasesVides);
    printf("Nombre de candidats elimines = %d\t", nbCandidatsElimines);
    printf("Pourcentage d'elimination = %.3f %%\n\n", 100.0*nbCandidatsElimines/nbCandidatsTotal);
}