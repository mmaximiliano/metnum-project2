#include <gtest/gtest.h>
#include <vector>

#include "../src/knn.h"


TEST(knn, todos_true) {
    VectorizedEntriesMap vm;
    vm[2].bag_of_words = {0, 0};
    vm[2].is_positive = true;

    vm[4].bag_of_words = {1, 0};
    vm[4].is_positive = true;

    vm[5].bag_of_words = {0, 1};
    vm[5].is_positive = true;

    bool resultado = knn(vm, {1, 1}, 3);
    EXPECT_TRUE(resultado);
}

TEST(knn, todos_false) {
    VectorizedEntriesMap vm;
    vm[2].bag_of_words = {0, 0};
    vm[2].is_positive = false;

    vm[4].bag_of_words = {1, 0};
    vm[4].is_positive = false;

    vm[5].bag_of_words = {0, 1};
    vm[5].is_positive = false;

    bool resultado = knn(vm, {1, 1}, 3);
    EXPECT_FALSE(resultado);
}

TEST(knn, mayoria_false) {

    VectorizedEntriesMap vm;

    vm[2].bag_of_words = {0, 0};
    vm[2].is_positive = true;

    vm[4].bag_of_words = {1, 0};
    vm[4].is_positive = false;

    vm[5].bag_of_words = {0, 1};
    vm[5].is_positive = false;

    bool resultado = knn(vm, {1, 1}, 3);
    EXPECT_FALSE(resultado);
}

TEST(knn, cercano_true) {

    VectorizedEntriesMap vm;

    vm[2].bag_of_words = {0, 0};
    vm[2].is_positive = true;

    vm[4].bag_of_words = {5, 0};
    vm[4].is_positive = false;

    vm[5].bag_of_words = {0, 5};
    vm[5].is_positive = false;

    bool resultado = knn(vm, {1, 1}, 1);
    EXPECT_TRUE(resultado);
}