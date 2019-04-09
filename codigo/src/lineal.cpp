#include "lineal.h"
#include <cmath>

double norma1(const std::vector<double> &v) {
    double norma = 0.0;
    for (unsigned int i = 0; i < v.size(); i++) {
        norma += std::abs(v[i]);
    }
    return norma;
}

double norma2(const std::vector<double> &v) {
    double norma = 0.0;
    for (unsigned int i = 0; i < v.size(); i++) {
        norma += v[i] * v[i];
    }
    return sqrt(norma);
}

std::vector<double> normalizar(const std::vector<double> &v) {
    double normaDeV = norma2(v);

    std::vector<double> res;
    for (unsigned int i = 0; i < v.size(); i++) {
        res.push_back(v[i] / normaDeV);
    }

    return res;
}

double operator*(const std::vector<double> &v1, const std::vector<double> &v2) {
    double sum = 0.0;
    for (unsigned int i = 0; i < v1.size(); i++) {
        sum += v1[i] * v2[i];
    }

    return sum;
}

std::vector<double> operator*(const std::vector<std::vector<double> > &M, const std::vector<double> &v) {
    std::vector<double> res;
    for (unsigned int i = 0; i < M.size(); i++) {
        double sum = 0.0;
        for (unsigned int j = 0; j < M[i].size(); j++) {
            sum += M[i][j] * v[j];
        }

        res.push_back(sum);
    }

    return res;
}
