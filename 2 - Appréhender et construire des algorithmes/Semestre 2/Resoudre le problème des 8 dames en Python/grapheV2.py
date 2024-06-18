from time import time

class Graphe:
    def __init__(self, n):
        self.n = n
        self.graphe = {}

    def creer_graphe(self):
        for i in range(self.n):
            for j in range(self.n):
                noeud = (i, j)
                self.graphe[noeud] = []
                # Ajout des menaces dans les colonnes
                for k in range(self.n):
                    if k != i:
                        self.graphe[noeud].append((k, j))
                # Ajout des menaces dans les diagonales
                for k in range(1, self.n):
                    if 0 <= i - k < self.n and 0 <= j - k < self.n:
                        self.graphe[noeud].append((i - k, j - k))
                    if 0 <= i - k < self.n and 0 <= j + k < self.n:
                        self.graphe[noeud].append((i - k, j + k))

def is_safe(graphe, noeud, reines):
    for reine in reines:
        if reine[0] == noeud[0] or reine[1] == noeud[1] or abs(reine[0] - noeud[0]) == abs(reine[1] - noeud[1]):
            return False
    return True

def resoudre(graphe, reines=[], ligne=0):
    if len(reines) == graphe.n:
        return [reines]
    solutions = []
    for noeud in graphe.graphe:
        if noeud[0] == ligne and is_safe(graphe.graphe, noeud, reines):
            result = resoudre(graphe, reines + [noeud], ligne + 1)
            solutions.extend(result)
    return solutions

def afficherSolutions(solutions, n):
    if solutions:
        print("Nombre total de solutions:", len(solutions))
        for i, reines in enumerate(solutions):
            print("Solution", i + 1)
            plateau = [['.' for _ in range(n)] for _ in range(n)]
            for reine in reines:
                plateau[reine[0]][reine[1]] = 'Q'
            for ligne in plateau:
                print(' '.join(ligne))
            print()
    else:
        print("Pas de solution trouvée.")

def resoudre_probleme(n, ligne, colonne):
    t1 = time()
    graphe = Graphe(n)
    graphe.creer_graphe()
    reines = [(ligne, colonne)]
    solutions = resoudre(graphe, reines, ligne + 1)
    t2 = time()
    afficherSolutions(solutions, n)
    print(f"Temps d'execution : {t2-t1}s")

# Appel de la fonction principale avec la taille du plateau
n = int(input("Entrez la taille du plateau (par exemple, pour 8x8, entrez 8): "))
while True:
    try:
        ligne = int(input("Entrez le numéro de ligne de la première dame (0 à {}): ".format(n - 1)))
        colonne = int(input("Entrez le numéro de colonne de la première dame (0 à {}): ".format(n - 1)))
        if 0 <= ligne < n and 0 <= colonne < n:
            break
        else:
            print("Coordonnées invalides. Veuillez réessayer.")
    except ValueError:
        print("Veuillez saisir des nombres entiers.")

resoudre_probleme(n, ligne, colonne)
