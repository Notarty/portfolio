from time import time

def print_solution(solution, nbdame):
    # Affiche une solution sous forme de grille
    for row in solution:
        # Convertit chaque ligne de la solution en une chaîne de caractères
        # 'q' représente une dame placée, '.' représente une case vide
        print(' '.join('q' if cell == 1 else '.' for cell in row))
    print()

def backtracking(g, case, nbdame, solutions):
    # Algorithme de backtracking pour trouver toutes les solutions possibles
    if case == nbdame:
        # Si toutes les dames sont placées, ajoute la configuration actuelle à la liste des solutions
        solutions.append([row[:] for row in g])
    else:
        # Parcours de chaque ligne pour placer une dame dans la colonne 'case'
        for numligne in range(nbdame):
            if possible(g, numligne, case, nbdame):
                # Si la position est valide, place une dame et explore les configurations suivantes
                g[numligne][case] = 1
                backtracking(g, case + 1, nbdame, solutions)
                # Retire la dame pour explorer d'autres possibilités
                g[numligne][case] = 0

def possible(g, lig, col, nbdame):
    # Vérifie si une position est valide pour placer une dame
    # Vérification de la ligne
    for i in range(col):
        if g[lig][i] == 1:
            return False
    
    # Vérification de la diagonale supérieure gauche
    for i, j in zip(range(lig, -1, -1), range(col, -1, -1)):
        if g[i][j] == 1:
            return False
    
    # Vérification de la diagonale inférieure gauche
    for i, j in zip(range(lig, nbdame), range(col, -1, -1)):
        if g[i][j] == 1:
            return False
    
    return True

# Demande à l'utilisateur le nombre de dames
nbdame = int(input("Quelle est le nombre de dames que vous souhaitez : "))

# Liste pour stocker les solutions trouvées
solutions = []

# Crée une grille vide de taille nbdame x nbdame
grille = [[0] * nbdame for _ in range(nbdame)]

# Trouve toutes les configurations possibles en utilisant le backtracking
t1 = time()
backtracking(grille, 0, nbdame, solutions)
t2 = time()

if solutions:
    # Si des solutions sont trouvées
    print("Nombre de solutions trouvées:", len(solutions))
    # Demande à l'utilisateur s'il veut afficher toutes les solutions
    afficher_toutes = input("Voulez-vous afficher toutes les solutions (oui/non) ? ").lower().strip() == "oui"
    if afficher_toutes:
        # Affiche toutes les solutions trouvées
        print("Solutions trouvées:")
        for sol in solutions:
            print_solution(sol, nbdame)
    else:
        # Affiche uniquement la première solution trouvée
        print("Une solution trouvée:")
        print_solution(solutions[0], nbdame)
    print(f"Temps d'execution : {t2-t1}s")
else:
    # Si aucune solution n'est trouvée, affiche un message approprié
    print("Pas de solution possible.")
