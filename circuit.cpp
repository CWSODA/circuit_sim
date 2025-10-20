#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "circuit.hpp"

Circuit::Circuit(const char* filename) {
    Component component;
    FILE* fPtr;

    /* Try to open the file */
    fPtr = fopen(filename, "r");
    if (!fPtr) {
        fprintf(stderr, "Could not open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    Component new_comp;
    int line_count = 0;
    while (fscanf(fPtr, "%s %u %u %lf", new_comp.name, &new_comp.n1,
                  &new_comp.n2, &new_comp.value) == 4) {
        line_count++;
        switch (new_comp.name[0]) {
            case 'R':
                nR++;
                new_comp.type = ComponentType::RESISTOR;
                break;
            case 'V':
                nV++;
                new_comp.type = ComponentType::VOLTAGE;
                break;
            case 'I':
                nI++;
                new_comp.type = ComponentType::CURRENT;
                break;
            default:
                fprintf(stderr, "Unknown component on line %u in file %s.\n",
                        line_count, filename);
                exit(EXIT_FAILURE);
        }

        // updates maximum node
        if (new_comp.n1 > nN) nN = new_comp.n1;
        if (new_comp.n2 > nN) nN = new_comp.n2;

        comp.push_back(new_comp);
    }
    nN++; /* Node labelling is zero based so add one to get total number of
               nodes. */
    fclose(fPtr);
}

void Circuit::analyse() const {
    unsigned int n1, n2, i, cV;
    double value, g;
    Matrix A = create_matrix(nN + nV, nN + nV);
    Vector Z = create_vector(nN + nV);

    /* Build nodal analysis equations */
    for (i = 0, cV = 0; i < this->n_components(); i++) {
        n1 = comp[i].n1;
        n2 = comp[i].n2;
        value = comp[i].value;
        switch (comp[i].type) {
            case ComponentType::RESISTOR:
                g = 1.0 / value;
                A[n1][n2] -= g;
                A[n2][n1] -= g;
                A[n1][n1] += g;
                A[n2][n2] += g;
                break;
            case ComponentType::VOLTAGE:
                A[n1][cV + nN] = A[cV + nN][n1] = 1.0;
                A[n2][cV + nN] = A[cV + nN][n2] = -1.0;
                Z[cV + nN] = -value;
                cV++;
                break;
            case ComponentType::CURRENT:
                Z[n1] -= value;
                Z[n2] += value;
                break;
            default:
                std::cout << "HOW\n";
        }
    }
    /* Node 0 is ground and is treated differently */
    A[0][0] = 1.0;
    Z[0] = 0.0;
    for (i = 1; i < nN + nV; i++) A[0][i] = A[i][0] = 0.0;

    /* Analyse and display results */
    Vector X = solve_linear_system(A, Z);
    // NOTE: code below does not use A,Z so solve_linear_system does not edit
    // A,Z
    printf("----------------------------\n");
    printf(" Voltage sources: %u\n", nV);
    printf(" Current sources: %u\n", nI);
    printf("       Resistors: %u\n", nR);
    printf("           Nodes: %u\n", nN);
    printf("----------------------------\n");
    for (i = 0; i < nN; i++) {
        printf(" Node %3u = %10.6lf V\n", i, X[i]);
    }
    printf("----------------------------\n");
    if (nV) {
        for (i = 0, cV = 0; i < this->n_components(); i++)
            if (comp[i].type == ComponentType::VOLTAGE)
                printf(" I(%s)    = %10.6lf A\n", comp[i].name, X[nN + cV++]);
        printf("----------------------------\n");
    }
}

void Circuit::print() const {
    for (auto& component : comp) {
        std::string type;
        switch (component.type) {
            case ComponentType::RESISTOR:
                type = "resistor";
                break;
            case ComponentType::CURRENT:
                type = "current";
                break;
            case ComponentType::VOLTAGE:
                type = "voltage";
                break;
        }
        std::cout << component.name << " (" << type << ")" << ": "
                  << component.value << "(" << component.n1 << ", "
                  << component.n2 << ")" << std::endl;
    }
}

size_t Circuit::n_components() const { return comp.size(); }

Vector solve_linear_system(Matrix A, Vector b) {
    /* Note: This function overwrites the contents of A and b. */
    int i, j, k;
    double mult, sum;
    size_t n_rows = A.size();
    size_t n_cols = A[0].size();

    Vector x = create_vector(n_cols);

    /* reduce to upper triangular form */
    for (i = 0; i < n_rows - 1; i++) {
        for (j = i + 1; j < n_rows; j++) {
            mult = -A[j][i] / A[i][i];
            for (k = i; k < n_cols; k++) {
                A[j][k] += mult * A[i][k];
            }
            b[j] += mult * b[i];
        }
    }
    /* back substitute to find Vector x */
    for (i = n_rows - 1; i >= 0; i--) {
        for (j = i + 1, sum = 0.0; j < n_cols; j++) {
            sum += A[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / A[i][i];
    }
    return x;
}
