#include "JSSP.h"

// Fonction pour lire le graphe et calculer la somme des durées sur la machine la plus utilisée
void lire_graphe(const string& nom_fichier, Instance& instance) {
    ifstream fichier(nom_fichier);  // Ouvrir le fichier en mode lecture
    if (!fichier) {
        cerr << "Erreur lors de l'ouverture du fichier." << endl;
        exit(1);  // Quitter le programme en cas d'erreur
    }

    // Lire le nombre de jobs et de machines
    fichier >> instance.n_j >> instance.n_m;

    // Initialiser un tableau pour cumuler les durées de chaque machine
    vector<int> durees_machines(instance.n_m, 0);  // Tableau des durées, initialisé à 0 pour chaque machine
    
    // Créer une structure pour stocker les machines et durées des jobs
    instance.machines.resize(instance.n_j, vector<int>(instance.n_m));
    instance.durees.resize(instance.n_j, vector<int>(instance.n_m));

    // Lire les données des jobs et cumuler les durées pour chaque machine
    for (int i = 0; i < instance.n_j; ++i) {
        for (int j = 0; j < instance.n_m; ++j) {
            int machine, duree;
            fichier >> machine >> duree;  // Lire la machine et la durée
            durees_machines[machine] += duree;  // Cumuler la durée pour cette machine
            instance.machines[i][j] = machine;  // Machine pour le job i, opération j
            instance.durees[i][j] = duree;      // Durée pour le job i, opération j
        }
    }

    // Trouver la machine avec la durée cumulée maximale
    instance.opt = *max_element(durees_machines.begin(), durees_machines.end());

    fichier.close();  // Fermer le fichier après lecture
}

// Fonction pour mélanger le tableau
void shuffle(std::vector<int>& arr) {
    srand(static_cast<unsigned int>(time(0)));  // Initialisation de la graine
    for (int i = arr.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        std::swap(arr[i], arr[j]);  // Échanger arr[i] avec arr[j]
    }
}
/*
int* V_Bierwirth(Instance& instance) {
    int taille_vecteur = instance.n_j * instance.n_m;  // Taille correcte : nombre de jobs * nombre de machines

    // Allouer dynamiquement de la mémoire pour le vecteur de Bierwirth
    int* VB = new int[taille_vecteur];
    if (!VB) {
        std::cout << "Problème lors de la génération de notre vecteur de Bierwirth" << std::endl;
        return nullptr;
    }

    // Remplir le vecteur avec les jobs : chaque job apparait 'instance.n_m' fois
    for (int i = 0; i < taille_vecteur; i++) {
        VB[i] = i / instance.n_m;  // Remplir le vecteur avec les jobs
    }

    // Convertir le tableau dynamique en vecteur pour le mélanger
    std::vector<int> vec(VB, VB + taille_vecteur);  // Convertir le tableau en vecteur
    shuffle(vec);  // Mélanger le vecteur

    // Remplir à nouveau le tableau avec les valeurs mélangées
    for (int i = 0; i < vec.size(); ++i) {
        VB[i] = vec[i];
    }

    return VB;  // Retourne le tableau mélangé
}*/

void Evaluer(const string &mon_fichier, Instance& instance) {
    // Lire le graphe depuis le fichier
    lire_graphe(mon_fichier, instance);

    int taille_vecteur = instance.n_j * instance.n_m; // Nombre total d'opérations

    // Générer le vecteur de Bierwirth
    int* VB = V_Bierwirth(instance);

    // Stocker les dates de début pour chaque opération
    std::vector<int> ES_ij(instance.n_j * instance.n_m, 0);  // Date de début des opérations

    // Variable pour le plus long chemin
    int plus_long_chemin = 0;

    // Parcourir les jobs dans l'ordre du vecteur de Bierwirth
    for (int i = 0; i < taille_vecteur; i++) {
        int job = VB[i];  // Job à traiter

        // Pour chaque opération du job, on calcule la date de début
        for (int op = 0; op < instance.n_m; op++) {
            int machine = instance.machines[job][op];
            int duree = instance.durees[job][op];

            // Trouver la date de début la plus tôt pour cette opération
            int date_debut = 0;
            if (op > 0) {
                // Si ce n'est pas la première opération du job, il faut attendre que l'opération précédente soit terminée
                date_debut = ES_ij[job * instance.n_m + op - 1] + instance.durees[job][op - 1];
            }

            // Mettre à jour la date de début pour cette opération
            ES_ij[job * instance.n_m + op] = date_debut;

            // Calculer la fin de cette opération
            plus_long_chemin = std::max(plus_long_chemin, date_debut + duree);
        }
    }

    // Afficher les résultats
    std::cout << "Dates de début des opérations : " << std::endl;
    for (int i = 0; i < taille_vecteur; i++) {
        std::cout << ES_ij[i] << " ";
    }
    std::cout << std::endl;

    // Afficher le plus long chemin
    std::cout << "Le plus long chemin est : " << plus_long_chemin << std::endl;

    delete[] VB;
}

// Fonction pour générer un vecteur de Bierwirth
int* V_Bierwirth(Instance& instance) {
    int* VB = (int*)malloc(sizeof(int) * instance.n_m * instance.n_m); // Corrigé ici

    // Vérifie si l'allocation a réussi
    if (!VB) {
        std::cout << "Probleme lors de la generation de notre vecteur de Bierwirth" << std::endl; // Corrigé ici
        return nullptr; // Corrigé ici
    } else {
        for (int i = 0; i < instance.n_m * instance.n_m; i++) { // Corrigé ici
            VB[i] = i % instance.n_m; // Remplir le vecteur
        }
    }

    // Convertir le tableau dynamique en vecteur pour le mélanger
    std::vector<int> vec(VB, VB + instance.n_m * instance.n_m); // Convertir le tableau en vecteur
    shuffle(vec); // Mélanger le vecteur

    // Remplir à nouveau le tableau avec les valeurs mélangées
    for (int i = 0; i < vec.size(); ++i) {
        VB[i] = vec[i];
    }

    return VB; // Retourne le tableau mélangé
}

int main() {
    Instance instance;  // Créer une instance de la structure

    // Appeler la fonction lire_graphe pour remplir les informations
    lire_graphe("La06.txt", instance);

    // Afficher la valeur de opt (la durée cumulée maximale)
    std::cout << "La plus longue durée sur une machine est : " << instance.opt << std::endl;

    // Générer le vecteur de Bierwirth
    int* vecteur = V_Bierwirth(instance);

    // Afficher le vecteur généré
    for (int i = 0; i < pow(instance.n_m, 2); ++i) {
        std::cout << vecteur[i] << " ";
    }
    std::cout << std::endl;

    // Tester la fonction Evaluer avec un fichier texte contenant les données des jobs et des machines
    
    Evaluer("La01.txt", instance);

    // Libérer la mémoire
    delete[] vecteur;  // Utiliser delete[] pour libérer la mémoire allouée
    return 0;
}
