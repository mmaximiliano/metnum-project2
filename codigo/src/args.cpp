#include "args.h"
#include <iostream>

Config parseArgs(int argc, char *argv[]) {
    // -m <method>
    // -d <dataset_path>
    // -v <v_path = "NULL">
    // -s <s_path = "NULL">
    // -o <classif> output
    // -c <clock_output_path>
    // -a <alpha = 100>
    // -p <iteraciones potencia = 100> 
    // -k <k = 5>
    // -t <thread_count = 1>
    // -f <frecuencia_minima = 0.01>
    // -F <frecuencia_maxima = 0.99>

    Config config;
    for (int i = 1; i < argc; i += 2) {
        std::string s = argv[i];

        switch (s[1]) {
            case 'm':
                config.m = (Method) std::stoi(argv[i + 1]);
                break;
            case 'd':
                config.dataset_path = argv[i + 1];
                break;
            case 'v':
                config.v_path = argv[i + 1];
                break;
            case 's':
                config.s_path = argv[i + 1];
                break;
            case 'o':
                config.classif = argv[i + 1];
                break;
            case 'c':
                config.clock_path = argv[i + 1];
                break;
            case 'a':
                config.alpha = std::stoi(argv[i + 1]);
                break;
            case 'p':
                config.power_iterations = std::stoi(argv[i + 1]);
                break;
            case 'k':
                config.k = std::stoi(argv[i + 1]);
                break;
            case 't':
                config.thread_count = std::stoi(argv[i + 1]);
                break;
            case 'f':
                config.fmin = std::stod(argv[i + 1]);
                break;
            case 'F':
                config.fmax = std::stod(argv[i + 1]);
        }
    }

    return config;
}
