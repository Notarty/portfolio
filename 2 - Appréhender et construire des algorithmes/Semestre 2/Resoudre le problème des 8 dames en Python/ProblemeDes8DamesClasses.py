from time import time

class Echiquier:
    def __init__(self, nbDames):
        # initialisation du nombre de dames, du plateau actuel et du tableau qui va contenir toutes les solutions trouver
        self.nbDames = nbDames
        self.plateau = [['.' for _ in range(nbDames)] for _ in range(nbDames)]
        self.solutions = []

    def placer_dame(self, ligne):
        # fonction qui va parcourir toutes les cases de la ligne passer en parametre jusqu'à trouver une case libre si trouver on fait appel à la récursivité pour la ligne suivante (ligne+1) sinon on revient en arriere jusq'a trouver une combinaison gagnante
        if ligne == self.nbDames: #conditions d'arrêts, c'est à dire si on a placer toute les dames, on Enregistre la solutions
            self.solutions.append([ligne[:] for ligne in self.plateau]) 
            return True

        for colonne in range(self.nbDames): # parcours les cases de la ligne
            if self.plateau[ligne][colonne] == 'Q': # condition si on tombe sur la Dames placer par l'utilisateur
                return self.placer_dame(ligne + 1)
            if self.est_possible(ligne, colonne): # teste si la case est possible
                self.plateau[ligne][colonne] = 'Q'
                self.placer_dame(ligne + 1)
                self.plateau[ligne][colonne] = '.'
        return False

    def est_possible(self, ligne, colonne):
        for i in range(self.nbDames): # Vérifier la ligne et la colonne
            if self.plateau[i][colonne] == 'Q' or self.plateau[ligne][i]== 'Q':
                return False

        for i, j in zip(range(ligne-1, -1, -1), range(colonne-1, -1, -1)):# Vérifier la diagonale gauche supérieure
            if self.plateau[i][j] == 'Q':
                return False

        for i, j in zip(range(ligne-1, -1, -1), range(colonne+1, self.nbDames)):# Vérifier la diagonale droite supérieure
            if self.plateau[i][j] == 'Q':
                return False

        for i in range(ligne + 1, self.nbDames):  # Vérifier la diagonale gauche inférieure
            j = colonne - (ligne - i)
            if j >= 0 and j < self.nbDames and self.plateau[i][j] == 'Q':
                return False

        for i in range(ligne + 1, self.nbDames):  # Vérifier la diagonale droite inférieure
            j = colonne + (ligne - i)
            if j >= 0 and j < self.nbDames and self.plateau[i][j] == 'Q':
                return False

        return True

    def afficher_solutions(self,affiche=False):
        if not self.solutions:
            print("Aucune solution trouvée.")
            return
        print("Nombre de solutions:", len(self.solutions))
        if len(self.solutions) == 1 or affiche == True:
            print("Solution :")
            solution = self.solutions[0]
            for ligne in range(self.nbDames):
                for colonne in range(self.nbDames):
                    print(solution[ligne][colonne], end=" ")
                print()
        else:
            print("Toutes les solutions :")
            for idx, solution in enumerate(self.solutions, 1):
                print("Solution", idx, ":")
                for ligne in range(self.nbDames):
                    for colonne in range(self.nbDames):
                        print(solution[ligne][colonne], end=" ")
                    print()
                print()

    def placer1Dame(self): # Fonction placant la première dame aux coordonnées donnees par l'utilisateur
        choix = input("Voulez-vous placer la première dame ? (o/n) : ")
        if choix.lower() == 'o':
            ligne = int(input("Quelle est la ligne de la première dame (1-8) : "))
            colonne = int(input("Quelle est la colonne de la première dame (1-8) : "))
            if 1 <= ligne <= self.nbDames and 1 <= colonne <= self.nbDames:
                self.plateau[ligne-1][colonne-1] = 'Q'
            else:
                print("Position invalide. La première dame ne sera pas placée.")
        else:
            print("La première dame ne sera pas placée.")

        choix_affichage = input("Voulez-vous afficher toutes les solutions ? (o/n) : ")
        if choix_affichage.lower() == 'o':
            t1 = time()
            self.placer_dame(0)
            t2 = time()
            self.afficher_solutions()
        else:
            t1 = time()
            self.placer_dame(0)
            t2 = time()
            self.afficher_solutions(True)
            print("Seule une solution est affichée.")
        print(f"Temps d'execution : {t2-t1}s")

NbDames=int(input("Le nombre de dames a placer dans l'echequier de dames*dames : "))
A1 = Echiquier(NbDames)
A1.placer1Dame()
