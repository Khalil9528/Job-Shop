#include "JSSP.h"

void lire_graphe(const string& nom_fichier, Instance& instance) {
    ifstream fichier(nom_fichier);
    if (!fichier) {
        cerr << "Erreur lors de l'ouverture du fichier." << endl;
        exit(1);
    }

    fichier >> instance.n_j >> instance.n_m;

    vector<int> durees_machines(instance.n_m, 0);
    instance.machines.resize(instance.n_j, vector<int>(instance.n_m));
    instance.durees.resize(instance.n_j, vector<int>(instance.n_m));

    for (int i = 0; i < instance.n_j; ++i) {
        for (int j = 0; j < instance.n_m; ++j) {
            int machine, duree;
            fichier >> machine >> duree;
            durees_machines[machine] += duree;
            instance.machines[i][j] = machine;
            instance.durees[i][j] = duree;
        }
    }

    instance.opt = *max_element(durees_machines.begin(), durees_machines.end());
    fichier.close();
}

void shuffle(std::vector<int>& arr) {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = arr.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        std::swap(arr[i], arr[j]);
    }
}

int* V_Bierwirth(Instance& instance) {
    int* VB = (int*)malloc(sizeof(int) * instance.n_m * instance.n_m);
    if (!VB) {
        std::cout << "Probleme lors de la generation de notre vecteur de Bierwirth" << std::endl;
        return nullptr;
    } else {
        for (int i = 0; i < instance.n_m * instance.n_m; i++) {
            VB[i] = i % instance.n_m;
        }
    }

    std::vector<int> vec(VB, VB + instance.n_m * instance.n_m);
    shuffle(vec);

    for (int i = 0; i < vec.size(); ++i) {
        VB[i] = vec[i];
    }

    return VB;
}

void Evaluer(const string &mon_fichier, Instance& instance) {
    lire_graphe(mon_fichier, instance);
    std::cout << "Lecture du graphe terminée." << std::endl;

    int taille_vecteur = instance.n_m * instance.n_m;
    int* VB = V_Bierwirth(instance);
    std::cout << "Vecteur de Bierwirth généré : ";
    for (int i = 0; i < taille_vecteur; i++) {
        std::cout << VB[i] << " ";
    }
    std::cout << std::endl;

    std::vector<int> ES_ij(instance.n_j * instance.n_m, 0);
    int plus_long_chemin = 0;

    for (int i = 0; i < taille_vecteur; i++) {
        int job = VB[i];
        std::cout << "Traitement du job : " << job << std::endl;

        for (int op = 0; op < instance.n_m; op++) {
            int machine = instance.machines[job][op];
            int duree = instance.durees[job][op];

            int date_debut = 0;
            if (op > 0) {
                date_debut = ES_ij[job * instance.n_m + op - 1] + instance.durees[job][op - 1];
            }

            ES_ij[job * instance.n_m + op] = date_debut;
            plus_long_chemin = std::max(plus_long_chemin, date_debut + duree);

            std::cout << "Opération " << op << " du job " << job
                      << " : Machine " << machine << ", Date de début : " 
                      << date_debut << ", Durée : " << duree << std::endl;
        }
    }

    std::cout << "Dates de début des opérations : " << std::endl;
    for (int i = 0; i < taille_vecteur; i++) {
        std::cout << ES_ij[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Le plus long chemin est : " << plus_long_chemin << std::endl;

    delete[] VB;
}

int main() {
    Instance instance;
    lire_graphe("La03.txt", instance);

    std::cout << "La plus longue durée sur une machine est : " << instance.opt << std::endl;

    int* vecteur = V_Bierwirth(instance);
    for (int i = 0; i < pow(instance.n_m, 2); ++i) {
        std::cout << vecteur[i] << " ";
    }
    std::cout << std::endl;

    Evaluer("La03.txt", instance);

    delete[] vecteur;
    return 0;
}
