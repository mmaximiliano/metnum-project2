#ifndef __ARGS_H__
#define __ARGS_H__

#include <string>

enum Method {
    KNN = 0,
    PCA_KNN = 1
};

struct Config {
    Method m;
    std::string dataset_path;
    std::string classif;
    std::string v_path;
    std::string s_path;
    std::string clock_path;
    int alpha;
    int power_iterations;
    int k;
    int thread_count;
    double fmin;
    double fmax;

    Config() {
        this->m = KNN;
        this->dataset_path = "../datos/imdb_tokenized.csv";
        this->classif = "out/classif.out";
        this->v_path = "NULL";
        this->s_path = "NULL";
        this->clock_path = "out/clock.out";
        this->alpha = 100;
        this->power_iterations = 100;
        this->k = 5;
        this->thread_count = 1;
        this->fmin = 0.01;
        this->fmax = 0.99;
    }
};

Config parseArgs(int argc, char *argv[]);

#endif
