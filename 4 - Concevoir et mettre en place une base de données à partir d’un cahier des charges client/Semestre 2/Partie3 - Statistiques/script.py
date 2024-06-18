import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import r2_score

# Spécifier le bon séparateur (ajuster 'sep' en fonction du fichier brut)
data = pd.read_csv('/mnt/data/colleges_sans_0.csv', sep=';')

# Vérifier la structure des données
print(data.head())

# Conversion du DataFrame en tableau de valeurs
data_values = data.values
print(data_values)

# Vérification des noms des colonnes après conversion
print("Noms des colonnes:", data.columns)

# Ajout de la nouvelle colonne effectif_total
try:
    data['effectif_total'] = data['effectif_garcons'] + data['effectif_filles']
    print("Nouvelle colonne 'effectif_total' ajoutée avec succès")
    print(data.head())
except KeyError as e:
    print(f"Erreur lors de l'ajout de la colonne 'effectif_total' : {e}")

# 2. Mise en forme et centrage-réduction
# Vérification des types et des valeurs manquantes
print(data.info())
print(data.isnull().sum())

# Centrage-réduction
scaler = StandardScaler()
data_scaled = pd.DataFrame(scaler.fit_transform(data), columns=data.columns)

# 3. Exploration des données par représentations graphiques
# Histogrammes des variables explicatives et de la variable endogène
fig, axes = plt.subplots(2, 3, figsize=(15, 10))
sns.histplot(data['nombre_eleves_segpa'], kde=True, ax=axes[0, 0])
sns.histplot(data['nombre_eleves_ulis'], kde=True, ax=axes[0, 1])
sns.histplot(data['effectif_garcons'], kde=True, ax=axes[0, 2])
sns.histplot(data['effectif_filles'], kde=True, ax=axes[1, 0])
sns.histplot(data['effectif_total'], kde=True, ax=axes[1, 1])

# Boîtes à moustaches
fig, axes = plt.subplots(2, 3, figsize=(15, 10))
sns.boxplot(y=data['nombre_eleves_segpa'], ax=axes[0, 0])
sns.boxplot(y=data['nombre_eleves_ulis'], ax=axes[0, 1])
sns.boxplot(y=data['effectif_garcons'], ax=axes[0, 2])
sns.boxplot(y=data['effectif_filles'], ax=axes[1, 0])
sns.boxplot(y=data['effectif_total'], ax=axes[1, 1])

# Calcul des moyennes et variances
print(data.describe())

# 3b. Matrice de covariance
cov_matrix = data.cov()
print(cov_matrix)

# 4. Régression linéaire multiple
X = data[['nombre_eleves_segpa', 'nombre_eleves_ulis', 'effectif_garcons', 'effectif_filles']]
y = data['effectif_total']

# Application de la régression linéaire multiple
reg = LinearRegression()
reg.fit(X, y)

# Affichage des coefficients
coefficients = pd.DataFrame(reg.coef_, X.columns, columns=['Coefficient'])
print(coefficients)

# Prédictions et coefficient de corrélation multiple
y_pred = reg.predict(X)
r2 = r2_score(y, y_pred)
print(f'R²: {r2}')

# Affichage des paramètres obtenus
print(f'Intercept: {reg.intercept_}')
for idx, col_name in enumerate(X.columns):
    print(f"The coefficient for {col_name} is {reg.coef_[idx]}")

# Conclusion
print(f'La régression linéaire multiple nous a permis de modéliser l\'effectif total en fonction des variables explicatives avec un R² de {r2}.')
