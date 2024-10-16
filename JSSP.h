#pragma once
#include <iostream>
#include<fstream>
#include <vector>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour time()
#include <cmath>   // Pour pow
#include <algorithm> // Pour std::swap

using namespace std;

struct Instance {
    int n_j;  // Nombre de jobs
    int n_m;  // Nombre de machines
    int opt;  // Le plus long chemin
    std::vector<std::vector<int>> machines;  // Machines pour chaque job et chaque opération
    std::vector<std::vector<int>> durees;    // Durées pour chaque job et chaque opération
};

void lire_graphe(const string& nom_fichier, Instance& instance);

void shuffle(std::vector<int>& arr);

int* V_Bierwirth(Instance& instance);

void Evaluer(const string &mon_fichier, Instance& instance);


