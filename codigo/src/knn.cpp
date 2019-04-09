#include "knn.h"
#include "lineal.h"
#include <cmath>
#include <algorithm>
#include <utility>
#include <queue>
#include <iostream>

using MinHeap = std::priority_queue<std::pair<double, bool>, std::vector<std::pair<double, bool> >, std::greater<std::pair<double, bool> > >;

double dist(const std::vector<double> &wordsA, const std::vector<double> &wordsB) {
    double res = 0;

    for (unsigned int i = 0; i < wordsA.size(); i++) {
        res += std::abs(wordsA[i] - wordsB[i]);
    }

    return res;
}

bool knn(const VectorizedEntriesMap &entries, const std::vector<double> &words, int k) {
    std::vector<std::pair<double, bool> > distancias;

    for (auto entry:entries) {
        distancias.push_back({dist(words, entry.second.bag_of_words), entry.second.is_positive});
    }

    MinHeap heapDistancias(distancias.begin(), distancias.end());

    int cant_pos = 0;
    for (int i = 0; i < k; i++) {
        std::pair<double, bool> vecino = heapDistancias.top();
        heapDistancias.pop();

        if (vecino.second) {
            cant_pos++;
        }
    }

    return cant_pos >= (k - cant_pos);
}
