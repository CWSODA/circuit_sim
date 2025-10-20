#include <iostream>

#include "matrix.hpp"
#include "vector.hpp"
#include "circuit.hpp"
#include "plotter.hpp"
#include "logic_array.hpp"

int main(int argc, char* argv[]) {
    // Vector vec = load_vec_from_file("../data/vec1");
    // print_vec(vec);

    // Matrix mat = load_matrix_from_file("../data/mat1");
    // print_matrix(mat);

    // load circuit, then analyse
    // Circuit circuit("../data/ex2.cir");
    // circuit.analyse();

    // plot_graph(0.05, 50);
    // FourierSeries fs = gen_square_wave_fs(2, 5);
    // plot_fourier(0.05, 100, fs);

    while (true) {
        std::cout << "WELCOME TO CIRCUIT SIMULATOR\n\
        Select a mode (h for help)\n";

        std::string input;
        std::getline(std::cin, input);
    }
    LogicArray la("../data/la1");
    la.get_input();

    std::cout << "Printing outputs: \n";
    for (auto output : la.get_output()) {
        std::cout << "Result: ";
        if (output)
            std::cout << "true";
        else
            std::cout << "false";
        std::cout << std::endl;
    }

    return 0;
}