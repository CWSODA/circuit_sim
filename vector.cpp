#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>

#include "vector.hpp"

Vector create_vector(size_t size) {
    Vector output;
    output.resize(size, 0.0);
    return output;
}

Vector load_vec_from_file(const char* filename) {
    Vector output;

    std::fstream input_stream;
    input_stream.open(filename);
    if (!input_stream) {
        std::cout << "Error reading vector file: " << filename << std::endl;
    }

    float val;
    while (input_stream >> val) {
        output.push_back(val);
    }

    return output;
}

void print_vec(const Vector& vec) {
    for (size_t i = 0; i < vec.size(); i++) printf("[%zu] = %lf\n", i, vec[i]);
}
