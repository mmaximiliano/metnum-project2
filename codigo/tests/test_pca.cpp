#include <gtest/gtest.h>
#include <vector>
#include <cmath>

#include "../src/pca.h"

TEST(pca, test_simple) {
    VectorizedEntriesMap vm;
    vm[2].bag_of_words = {64.0, 580.0, 29.0};
    vm[2].is_positive = true;

    vm[4].bag_of_words = {66.0, 570.0, 33.0};
    vm[4].is_positive = true;

    vm[5].bag_of_words = {68.0, 590.0, 37.0};
    vm[5].is_positive = true;

    vm[6].bag_of_words = {69.0, 660.0, 46.0};
    vm[6].is_positive = true;

    vm[7].bag_of_words = {73.0, 600.0, 55.0};
    vm[7].is_positive = true;

    // Matriz de covarianza:

/*    X        Y        Z
    X   11.50    50.00   34.75
    Y   50.00  1250.00  205.00
    Z   34.75   205.00  110.00 */

    std::vector<std::vector<double>> dimReduceMat;

    pca(vm, 3, 1, 5, dimReduceMat, "NULL");

    // Autovectores de la matriz de covarianza

    // Checkeamos si es igual al autovector negado o no negado
    if (std::abs(dimReduceMat[0][0] - 0.043) < 0.01) {

        EXPECT_NEAR(dimReduceMat[0][0], 0.043, 0.01);
        EXPECT_NEAR(dimReduceMat[0][1], 0.984, 0.01);
        EXPECT_NEAR(dimReduceMat[0][2], 0.172, 0.01);

    } else {
        EXPECT_NEAR(dimReduceMat[0][0], -0.043, 0.01);
        EXPECT_NEAR(dimReduceMat[0][1], -0.984, 0.01);
        EXPECT_NEAR(dimReduceMat[0][2], -0.172, 0.01);
    }

    if (std::abs(dimReduceMat[1][0] -  0.326) < 0.01) {
        EXPECT_NEAR(dimReduceMat[1][0], 0.326, 0.01);
        EXPECT_NEAR(dimReduceMat[1][1], -0.177, 0.01);
        EXPECT_NEAR(dimReduceMat[1][2], 0.928, 0.01);

    } else {
        EXPECT_NEAR(dimReduceMat[1][0], -0.326, 0.01);
        EXPECT_NEAR(dimReduceMat[1][1], 0.177, 0.01);
        EXPECT_NEAR(dimReduceMat[1][2], -0.928, 0.01);
    }

    if (std::abs(dimReduceMat[2][0] + 0.944) < 0.01) {
        EXPECT_NEAR(dimReduceMat[2][0], -0.944, 0.01);
        EXPECT_NEAR(dimReduceMat[2][1], -0.016, 0.01);
        EXPECT_NEAR(dimReduceMat[2][2], 0.329, 0.01);

    } else {
        EXPECT_NEAR(dimReduceMat[2][0], 0.944, 0.01);
        EXPECT_NEAR(dimReduceMat[2][1], 0.016, 0.01);
        EXPECT_NEAR(dimReduceMat[2][2], -0.329, 0.01);
    }
}