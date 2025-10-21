#include "sub_app.hpp"

#include <iostream>

#include "logic_array.hpp"
#include "circuit.hpp"
#include "plotter.hpp"
#include "fourier.hpp"

std::string get_filename(std::string file_type) {
    std::string filename;
    std::cout << "Input " << file_type << " filename: ";
    std::getline(std::cin, filename);
    filename = "../data/" + filename;
    return filename;
}

void display_welcome_msg() {
    std::cout << "\n\nWELCOME TO CIRCUIT SIMULATOR\n\
Select a mode (h for help)"
              << std::endl;
}

void display_help_menu() {
    std::cout << "\
--- HELP MENU --- \n\
(h) help menu\n\
(l) logic array\n\
(c) circuit simulator\n\
(p) graph plotter"
              << std::endl;
}

void run_logic_array() {
    std::string filename = get_filename("logic array");
    LogicArray logic_array(filename.data());
    logic_array.get_input();
    logic_array.print_output();
}

void run_circuit_simulator() {
    std::string filename = get_filename("circuit");
    Circuit circuit(filename.data());
    circuit.analyse();
}

void run_plotter() {
    // plot_graph(0.05, 50);
    FourierSeries fs = gen_square_wave_fs(2, 100);
    plot_fourier(0.05, 100, fs);
}