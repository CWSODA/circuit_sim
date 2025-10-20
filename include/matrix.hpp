#pragma once

#include <vector>

/* Data structure */

using Matrix = std::vector<std::vector<double>>;

// struct Matrix {
//     std::vector<std::vector<double>> data;

//     Matrix() {};
//     Matrix(size_t n_rows, size_t n_cols);

//     size_t n_cols() const { return data.size(); }
//     size_t n_rows() const { return data[0].size(); }
// };

/* Interfaces */
Matrix create_matrix(size_t n_rows, size_t n_cols);
Matrix load_matrix_from_file(const char* filename);
void print_matrix(const Matrix& matrix);
