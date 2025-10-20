#pragma once

#include <vector>

using Vector = std::vector<double>;

Vector create_vector(size_t size);
std::vector<double> load_vec_from_file(const char* filename);
void print_vec(const std::vector<double>& vec);