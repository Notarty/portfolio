import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

# Chargement des données
CollegesDF = pd.read_csv('/colleges.csv', sep=';')

# Vérification des premières lignes du DataFrame
print(CollegesDF.head())

# Création de la colonne 'effectif_total'
CollegesDF['effectif_total'] = CollegesDF['garcons'] + CollegesDF['filles']

# Affichage des premières lignes pour vérification
print(CollegesDF.head())

# Séparation des variables
segpa = CollegesDF['nombre_eleves_segpa']
ulis = CollegesDF['nombre_eleves_ulis']
garcon = CollegesDF['garcons']
filles = CollegesDF['filles']
effectif_total = CollegesDF['effectif_total']

# Création d'un DataFrame pour les données triées
sorted_df = pd.DataFrame({
    'Segpa': segpa,
    'Ulis': ulis,
    'Garcon': garcon,
    'Filles': filles,
    'Effectif_total': effectif_total
})

# Calcul de la matrice de corrélation
correlation_matrix = sorted_df.corr()

# Affichage de la matrice de corrélation
print(correlation_matrix)

# Tracé des données
plt.xlabel("Nombre d'élèves ULIS")
plt.ylabel("Effectif total")
plt.plot(ulis, effectif_total, 'o')
plt.show()

# Tracé de la matrice de corrélation sous forme de heatmap
plt.figure(figsize=(10, 8))
sns.heatmap(correlation_matrix, annot=True, fmt=".2f", cmap='coolwarm', xticklabels=correlation_matrix.columns, yticklabels=correlation_matrix.columns)
plt.title('Correlation Matrix Heatmap')
plt.show()

# Préparation des données pour la régression linéaire multiple
X = sorted_df[['Segpa', 'Ulis', 'Garcon', 'Filles']]
y = sorted_df['Effectif_total']

# Création et entraînement du modèle
model = LinearRegression()
model.fit(X, y)

# Obtention des coefficients
intercept = model.intercept_
coefficients = model.coef_

print(f'Intercept: {intercept}')
print('Coefficients:', coefficients)

# Faire des prédictions
y_pred = model.predict(X)

# Évaluation du modèle
mse = mean_squared_error(y, y_pred)
r2 = r2_score(y, y_pred)

print(f'Mean Squared Error: {mse}')
print(f'R-squared: {r2}')

# Tracé des valeurs observées vs les valeurs prédites
plt.figure(figsize=(10, 8))
plt.scatter(y, y_pred)
plt.xlabel('Valeurs observées')
plt.ylabel('Valeurs prédites')
plt.title('Régression linéaire multiple')
plt.plot([min(y), max(y)], [min(y), max(y)], color='red')  # Ligne de meilleure fit
plt.show()
