cmake_minimum_required(VERSION 3.5)
project(solucion)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-O3 -pthread")

include_directories(tests/google-test)
add_subdirectory(tests/google-test)

set(SOURCE_FILES
        src/args.cpp
        src/knn.cpp
        src/lineal.cpp
        src/pca.cpp
        src_catedra/reader.h
        src_catedra/types.h
        src_catedra/vector_builder.h)

# Leemos todos los archivos de test en ./tests
file(GLOB TEST_SOURCES tests/*.cpp)

# Creamos el ejecutable para correr los tests

add_executable(tp2 src/main.cpp ${SOURCE_FILES})
add_executable(correrTests ${TEST_SOURCES} ${SOURCE_FILES})


# Necesitamos asociar los archivos del framework de testing
target_link_libraries(correrTests gtest gtest_main)

add_test(correrTests correrTests)

# Target para correr Valgrind
add_custom_target(correrValgrind
        valgrind --leak-check=full -v ./correrTests 2>&1
        DEPENDS correrTests)
