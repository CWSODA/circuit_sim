#pragma once

#include <vector>

#include "vector.hpp"
#include "matrix.hpp"

/* Data Structures */

enum class ComponentType {
    VOLTAGE,
    RESISTOR,
    CURRENT,
};

struct Component {
    char name[10];
    // nodes
    unsigned int n1, n2;
    double value;
    ComponentType type;
};

class Circuit {
   public:
    Circuit(const char* filename);

    void analyse() const;
    void print() const;
    size_t n_components() const;

   private:
    // number of components, resistors, voltage source, current source
    unsigned int nR = 0, nV = 0, nI = 0;
    int nN = 0;
    std::vector<Component> comp;
};

/* Interfaces */
Vector solve_linear_system(Matrix A, Vector b);