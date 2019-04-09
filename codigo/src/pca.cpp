#include "pca.h"
#include "lineal.h"
#include <cmath>
#include <iostream>
#include <thread>
#include <fstream>

using namespace std;

void calcularMedias(const std::vector<std::vector<double>> &entries, std::vector<double> &medias) {
    std::cerr << "                                                    " << "\r";
    std::cerr << "Calculando Medias" << "\r";

    // Cantidad de entradas
    unsigned int n = entries.size();
    // Tamaño de las entradas
    unsigned int m = entries[0].size();
    for (unsigned int j = 0; j < m; j++) {
        double sumatoria = 0.0;
        for (unsigned int i = 0; i < n; i++) {
            sumatoria += entries[i][j];
        }

        medias.push_back(sumatoria / n);
    }
}

void obtenerMatrizCovarianzaThreads(const std::vector<std::vector<double>> *entries,
                                    std::vector<std::vector<double>> *covarianza,
                                    std::vector<double> *medias, unsigned int from, unsigned int to, unsigned int id) {
    // Cantidad de entradas
    unsigned int n = entries->size();
    // Tamaño de las entradas
    unsigned int m = (*entries)[0].size();

    for (unsigned int i = from; i < to; i++) {
        for (unsigned int j = i; j < m; j++) {
            (*covarianza)[i][j] = 0.0;
            for (unsigned int k = 0; k < n; k++) {
                (*covarianza)[i][j] +=
                        (((*entries)[k][i] - (*medias)[i]) * ((*entries)[k][j] - (*medias)[j])) / (n - 1);
                (*covarianza)[j][i] = (*covarianza)[i][j];
            }
        }
    }
}

void
obtenerMatrizCovarianza(const std::vector<std::vector<double>> &entries, std::vector<std::vector<double>> &covarianza,
                        unsigned int t) {
    std::cerr << "Obteniendo Matriz de Covarianza" << "\r";

    unsigned int THREAD_COUNT = t;

    std::vector<double> medias;
    calcularMedias(entries, medias);

    unsigned int m = entries[0].size();
    unsigned int step = m / THREAD_COUNT;

    std::vector<std::thread> threads;

    std::cerr << "                                                    " << "\r";
    std::cerr << "Iniciando " << THREAD_COUNT << " threads" << "\r";

    for (unsigned int i = 0; i < m; i += step) {
        threads.push_back(
                std::thread(obtenerMatrizCovarianzaThreads, &entries, &covarianza, &medias, i, i + step, i / step));
    }

    unsigned int border = m % THREAD_COUNT;
    threads.push_back(std::thread(obtenerMatrizCovarianzaThreads, &entries, &covarianza, &medias, m - border, m,
                                  THREAD_COUNT - 1));

    std::cerr << "                                                    " << "\r";
    std::cerr << "Corriendo " << THREAD_COUNT << " threads" << "\r";

    for (auto it = threads.begin(); it != threads.end(); it++) {
        it->join();
    }

    std::cerr << "                                                    " << "\r";
    std::cerr << "Terminando Threads" << "\r";

}

void obtenerVectorRandom(std::vector<double> &v) {
    srand(1);
    for (unsigned int i = 0; i < v.size(); i++) {
        // Numeros random
        v[i] = (rand() % 100) / 100.0;
    }
}

double metodoPotencia(const std::vector<std::vector<double>> &A, std::vector<double> &v, int numeroIteraciones) {
    obtenerVectorRandom(v);

    for (int iteracion = 0; iteracion < numeroIteraciones; iteracion++) {
        v = normalizar(A * v);
    }
    return (v * (A * v)) / (v * v);
}

void reducirAutovalores(std::vector<std::vector<double>> &B, std::vector<double> &v, double autovalor) {
    for (unsigned int i = 0; i < B.size(); i++) {
        for (unsigned int j = 0; j < B.size(); j++) {
            B[i][j] -= autovalor * v[i] * v[j];
        }
    }
}

void pca(const VectorizedEntriesMap &entries, unsigned int alpha, unsigned int t, unsigned int p,
         std::vector<std::vector<double>> &salidas, std::string s) {
    std::cerr << "PCA" << "\r";

    // Pasamos a una matriz para operar más comodos
    std::vector<std::vector<double>> B; // Matriz para operar
    std::vector<bool> isPositive; // Me guardo si las reviews eran positivas
    std::vector<int> ids; // Me guardo los ids de las reviews
    for (auto entry = entries.begin(); entry != entries.end(); entry++) {
        B.push_back(entry->second.bag_of_words);
        isPositive.push_back(entry->second.is_positive);
        ids.push_back(entry->first);
    }

    int dimReviews = B[0].size();

    // Crear matriz de covarianza
    std::vector<std::vector<double>> covarianza(dimReviews, std::vector<double>(dimReviews));

    // s es el path a una matriz de covarianza
    std::ifstream smat_check(s);

    if (!smat_check.good()) {
        obtenerMatrizCovarianza(B, covarianza, t);

        if (s != "NULL") {
            std::ofstream smat;
            smat.open(s, ios::out | ios::trunc);
            smat << covarianza.size() << " " << covarianza[0].size() << std::endl;
            for (auto i = covarianza.begin(); i != covarianza.end(); i++) {
                for (auto j = i->begin(); j != i->end(); j++) {
                    smat << *j << " ";
                }
            }
            smat.close();
        }
    } else {
        std::cerr << "Usando matriz de covarianza guardada." << std::endl;
        covarianza = std::vector<std::vector<double>>();
        std::ifstream smat;
        smat.open(s);
        int rows, cols;
        smat >> rows;
        smat >> cols;
        for (int i = 0; i < rows; i++) {
            covarianza.push_back(std::vector<double>());
            for (int j = 0; j < cols; j++) {
                double e;
                smat >> e;
                covarianza[i].push_back(e);
            }
        }
        smat.close();
    }

    // Vector para calcular autovector
    std::vector<double> v(dimReviews);
    // Autovectores calculados
    std::vector<std::vector<double>> autovectores;
    for (unsigned int i = 0; i < alpha; i++) {
        std::cerr << "                           " << "\r";
        std::cerr << "Buscando autovector " << i << "\r";
        double autovalor = metodoPotencia(covarianza, v, p);
        autovectores.push_back(v);
        reducirAutovalores(covarianza, v,
                           autovalor);
    }
    salidas = autovectores;
}
