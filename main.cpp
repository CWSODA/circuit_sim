#include <iostream>

#include "matrix.hpp"
#include "vector.hpp"
#include "circuit.hpp"
#include "plotter.hpp"
#include "logic_array.hpp"

int main(int argc, char* argv[]) {
    // plot_graph(0.05, 50);
    // FourierSeries fs = gen_square_wave_fs(2, 5);
    // plot_fourier(0.05, 100, fs);

    while (true) {
        std::cout << "\n\nWELCOME TO CIRCUIT SIMULATOR\n\
Select a mode (h for help)"
                  << std::endl;

        std::string input;
        std::getline(std::cin, input);

        if (input.size() == 1) {
            char c = input.at(0);

            switch (c) {
                case 'h':  // help menu
                    std::cout << "\
--- HELP MENU --- \n\
(h) help menu\n\
(l) logic array\n\
(c) circuit simulator\n\
(p) graph plotter\
                    " << std::endl;
                    break;
                case 'l':  // logic array
                {
                    std::cout << "Input filename: ";
                    std::getline(std::cin, input);
                    LogicArray logic_array(input.data());
                    logic_array.get_input();
                    logic_array.print_output();
                } break;
                case 'c':  // circuit simulator
                {
                    std::cout << "Input filename: ";
                    std::getline(std::cin, input);
                    Circuit circuit(input.data());
                    circuit.analyse();
                } break;
                case 'p':  // plot graph
                    break;
            }
        }
    }

    return 0;
}