from time import time

class Graphe:
    def __init__(self, n):
        self.n = n
        self.graphe = {}

    def creergraphe(self):
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

def resoudre(graphe, reines=[], row=0):
    if row == graphe.n:
        return [reines]
    solutions = []
    for noeud in graphe.graphe:
        if noeud[0] == row and is_safe(graphe.graphe, noeud, reines):
            result = resoudre(graphe, reines + [noeud], row + 1)
            solutions.extend(result)
    return solutions

def Affichagesolutions(solutions, n):
    if solutions:
        print("Nombre total de solutions:", len(solutions))
        for i, reines in enumerate(solutions):
            print("Solution", i + 1)
            plateau = [['.' for _ in range(n)] for _ in range(n)]
            for reine in reines:
                plateau[reine[0]][reine[1]] = 'Q'
            for row in plateau:
                print(' '.join(row))
            print()
    else:
        print("Pas de solution trouvée.")

def resoudre_problem(n):
    t1 = time()
    graphe = Graphe(n)
    graphe.creergraphe()
    solutions = resoudre(graphe)
    t2 = time()
    Affichagesolutions(solutions, n)
    print(f"Temps d'execution : {t2-t1}s")

# Appel de la fonction principale avec la taille du plateau
resoudre_problem(8)
