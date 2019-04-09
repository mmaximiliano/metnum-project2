#ifndef VECTOR_BUILDER__H
#define VECTOR_BUILDER__H

#include <functional>
#include <iostream>

#include "types.h"
#include "reader.h"
#include "../src/args.h"

void build_vectorized_datasets(
        const std::string &entries_path,
        VectorizedEntriesMap &train_vectorized_entries,
        VectorizedEntriesMap &test_vectorized_entries,
        const std::function<bool(int token, const FrecuencyVocabularyMap &vocabulary, const Config config)> &filter_out,
        const Config config) {
    /**
     * Construye las entradas vectorizadas, filtrándolas según `filter_out`.
     * Si alguna review quedara vacía luego de filtrar esta es eliminada
     **/
    TokenizedEntriesMap train_entries;
    TokenizedEntriesMap test_entries;
    read_entries(entries_path, train_entries, test_entries);

    const FrecuencyVocabularyMap vocabulary = read_vocabulary();

    auto filter_entries_with_vocabulary = [&vocabulary, &filter_out, config](TokenizedEntriesMap &entries) {
        /**
         *  Filtra las entradas de `entries` según `filter_out`
         **/
        std::cerr << "Filtrando entradas..." << '\r';
        for (auto entry = entries.begin(); entry != entries.end();) {
            std::vector<int> &tokens = entry->second.tokens;
            for (auto token = tokens.begin(); token != tokens.end();)
                if (filter_out(*token, vocabulary, config)) { token = tokens.erase(token); } else { ++token; }
            if (tokens.size() == 0) { entry = entries.erase(entry); } else { ++entry; }
        }
        std::cerr << "                     " << '\r';
    };
    filter_entries_with_vocabulary(train_entries);
    filter_entries_with_vocabulary(test_entries);

    auto count_words = [](std::map<int, int> &dst, const TokenizedEntriesMap &src) {
        /**
         *  Construye el mapa de token a ids
         **/
        std::cerr << "Contando palabras..." << '\r';
        int amount_of_words = dst.size();
        for (auto entry = src.begin(); entry != src.end(); entry++) {
            for (const auto token : entry->second.tokens) {
                if (dst.count(token) == 0) {
                    dst[token] = amount_of_words;
                    amount_of_words++;
                }
            }
        }
        std::cerr << "                    " << '\r';
    };
    std::map<int, int> tokens_to_indexes;
    count_words(tokens_to_indexes, train_entries);
    count_words(tokens_to_indexes, test_entries);
    const int N = tokens_to_indexes.size();

    auto translate_tokenized_entries = [&tokens_to_indexes, &N](const TokenizedEntriesMap &entries) {
        std::cerr << "Traduciendo tokens a vectores..." << '\r';
        VectorizedEntriesMap vectorized_entries;
        for (auto entry = entries.begin(); entry != entries.end(); entry++) {
            const int review_id = entry->first;
            const std::vector<int> &tokens = entry->second.tokens;
            VectorizedEntry vectorized_entry;
            vectorized_entries[review_id].is_positive = entry->second.is_positive;
            vectorized_entries[review_id].bag_of_words = std::vector<double>(N, 0);

            const double step = 1 / (double) tokens.size();
            for (const int token : tokens) {
                vectorized_entries[review_id].bag_of_words[tokens_to_indexes[token]] += step;
            }
        }

        std::cerr << "                                " << '\r';
        return vectorized_entries;
    };
    train_vectorized_entries = translate_tokenized_entries(train_entries);
    test_vectorized_entries = translate_tokenized_entries(test_entries);
}


#endif  // VECTOR_BUILDER__H
