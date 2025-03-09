# 🏭 Job-Shop Scheduling Problem (JSSP)

## 📌 Description
Ce projet est une implémentation en **C++** du **Job-Shop Scheduling Problem (JSSP)**.  
Il permet de :
- Lire un fichier texte contenant des **jobs** et **machines** avec leurs temps d'exécution.
- Calculer la **machine ayant la durée d'occupation la plus longue**.
- Générer un **vecteur de Bierwirth** pour représenter l'ordre d'exécution des opérations.
- Évaluer l'ordonnancement en calculant le **plus long chemin**.


## 🚀 Fonctionnalités
✅ **Lecture et traitement des fichiers de jobs**  
✅ **Calcul de la charge des machines**  
✅ **Génération et mélange du vecteur de Bierwirth**  
✅ **Évaluation et affichage du plus long chemin**  

## 🛠 Technologies utilisées
- **Langage :** C++  
- **Structures de données :** `std::vector`  
- **Lecture de fichiers :** `ifstream`  
- **Algorithme de Bierwirth** pour la génération d’un ordre aléatoire  
- **Gestion dynamique de la mémoire** (`new/delete`)  

## 🏃‍♂️ Exécution du programme
### 1️⃣ Compilation
```sh
g++ -o jobshop main.cpp instance.cpp lire_graphe.cpp bierwirth.cpp evaluer.cpp -std=c++11
