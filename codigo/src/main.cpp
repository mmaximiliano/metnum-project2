#include "../src_catedra/vector_builder.h"
#include "knn.h"
#include "pca.h"
#include "lineal.h"
#include "args.h"
#include <chrono>

using namespace std;

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

enum TimeType {
    DATA_SETUP = 0,
    PCA = 1,
    KNN_T = 2,
    ALL = 3
};

int main(int argc, char *argv[]) {
    if (argc % 2 == 0) {
        std::cerr << "Ojo! Fijate de pasar bien los params." << std::endl;
        return 1;
    }

    auto all_start = Time::now();

    std::map<TimeType, ms> times;
    times[DATA_SETUP] = ms{0};
    times[PCA] = ms{0};
    times[KNN_T] = ms{0};
    times[ALL] = ms{0};

    auto data_setup_start = Time::now();

    Config config = parseArgs(argc, argv);

    auto filter_out = [](const int token, const FrecuencyVocabularyMap &vocabulary, const Config config) {
        /**
         *  Lambda para usar como filtro de vocabulario
         *  Retorna `true` si `token` debe eliminarse
         *  Retorna `false` si `token` no debe eliminarse
         **/
        double token_frecuency = vocabulary.at(token);
        return token_frecuency < config.fmin || token_frecuency > config.fmax;
    };
    VectorizedEntriesMap train_entries;
    VectorizedEntriesMap test_entries;
    build_vectorized_datasets(config.dataset_path, train_entries, test_entries, filter_out, config);
    int N = train_entries.begin()->second.bag_of_words.size();

    auto data_setup_end = Time::now();
    times[DATA_SETUP] = std::chrono::duration_cast<ms>(data_setup_end - data_setup_start);

    std::cerr
            << "N: " << N << std::endl
            << "Dataset de entrenamiento: " << train_entries.size() << " entradas" << std::endl
            << "Dataset de testeo: " << test_entries.size() << " entradas" << std::endl;

    if (config.m == PCA_KNN) {
        auto pca_start = Time::now();
        std::cerr << "Calculando PCA sobre la data con Alpha: " << config.alpha << std::endl;
        std::vector<std::vector<double>> dimReduceMat;

        std::ifstream autovec_check(config.v_path);

        if (!autovec_check.good()) {
            pca(train_entries, config.alpha, config.thread_count, config.power_iterations, dimReduceMat, config.s_path);

            if (config.v_path != "NULL") {
                std::ofstream autovec;
                autovec.open(config.v_path, ios::out | ios::trunc);

                autovec << dimReduceMat.size() << " " << dimReduceMat[0].size() << std::endl;

                for (auto i = dimReduceMat.begin(); i != dimReduceMat.end(); i++) {
                    for (auto j = i->begin(); j != i->end(); j++) {
                        autovec << *j << " ";
                    }
                }

                autovec.close();
            }
        } else {
            std::cerr << "Usando matriz de autovectores guardada." << std::endl;
            std::ifstream autovec;
            autovec.open(config.v_path);

            int rows, cols;
            autovec >> rows;
            autovec >> cols;

            for (int i = 0; i < rows; i++) {
                dimReduceMat.push_back(std::vector<double>());
                for (int j = 0; j < cols; j++) {
                    double e;
                    autovec >> e;
                    dimReduceMat[i].push_back(e);
                }
            }

            autovec.close();
        }

        std::cerr << "Reduciendo Training Data \r";
        for (auto it = train_entries.begin(); it != train_entries.end(); it++) {
            // Ver que onda el index de salida
            it->second.bag_of_words = dimReduceMat * it->second.bag_of_words;
        }
        std::cerr << "                           \r";

        std::cerr << "Reduciendo Testing Data \r";
        for (auto it = test_entries.begin(); it != test_entries.end(); it++) {
            // Ver que onda el index de salida
            it->second.bag_of_words = dimReduceMat * it->second.bag_of_words;
        }
        std::cerr << "                           \r";

        std::cerr << "N ahora es: " << train_entries.begin()->second.bag_of_words.size() << std::endl;
        auto pca_end = Time::now();
        times[PCA] = std::chrono::duration_cast<ms>(pca_end - pca_start);
    }

    auto knn_start = Time::now();

    int tp = 0;
    int fp = 0;
    int tn = 0;
    int fn = 0;
    int amount = 0;
    std::ofstream fout;
    fout.open(config.classif, ios::out | ios::trunc);
    std::cerr << "K es: " << config.k << std::endl;
    fout << "id,label" << "\n";
    for (auto it = test_entries.begin(); it != test_entries.end(); it++) {
        std::cerr << "Prediciendo " << amount << " / " << test_entries.size() << '\r';
        bool label = it->second.is_positive;
        bool predi = knn(train_entries, it->second.bag_of_words, config.k);
        if (label && predi) tp++;
        else if (label && !predi) fn++;
        else if (!label && predi) fp++;
        else if (!label && !predi) tn++;
        amount++;
        std::cerr << "                                                            \r";
        fout << it->first << "," << (predi ? "pos" : "neg") << "\n";
    }

    fout.close();

    auto knn_end = Time::now();
    auto all_end = Time::now();
    times[KNN_T] = std::chrono::duration_cast<ms>(knn_end - knn_start);
    times[ALL] = std::chrono::duration_cast<ms>(all_end - all_start);

    fout.open(config.clock_path, ios::out | ios::trunc);
    fout << "data_setup," << times[DATA_SETUP].count() << "\n";
    fout << "pca," << times[PCA].count() << "\n";
    fout << "knn," << times[KNN_T].count() << "\n";
    fout << "all," << times[ALL].count() << "\n";
    fout.close();

    std::cerr
            << std::endl
            << "True positive: " << tp << std::endl
            << "False positive: " << fp << std::endl
            << "True negative: " << tn << std::endl
            << "False negative: " << fn << std::endl
            << "-----------------------" << std::endl
            << "Recall: " << (tp / (double) (tp + fp)) << std::endl
            << "Precision: " << (tp / (double) (tp + fn)) << std::endl
            << "Accuracy: " << ((tp + tn) / (double) amount) << std::endl;

    return 0;
}
