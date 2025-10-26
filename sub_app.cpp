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
(p) graph plotter\n\
(q) quit program"
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
    while (true) {
        std::cout << "\n\n\nIn PLOTTER menu (h for help)" << std::endl;
        std::string input;
        std::getline(std::cin, input);

        if (input.size() != 1) continue;
        switch (input.at(0)) {
            case 'h':
                std::cout << "--- PLOTTER HELP MENU --- \n\
(h) help menu\n\
(q) quits plotter\n\
(c) configure plotter settings\n\
(i) generates custom fourier series\n\
(s) generates square wave" << std::endl;
                break;
            case 'q':
                return;
            case 's':
                run_square_wave();
                break;
            case 'i':
                run_input_fs();
                break;
            case 'c':
                change_plotter_config();
                break;
        }
    }
}

void run_square_wave() {
    int n_coefficients;
    float period;
    try {
        std::string input;

        std::cout << "Enter number of coefficients to square wave: ";
        std::cin >> input;
        n_coefficients = std::stoi(input);
        if (n_coefficients <= 0)
            throw "Coefficient count must be greater than 0!\n";

        std::cout << "Enter period of square wave: ";
        std::cin >> input;
        period = std::stof(input);
        if (period <= 0) throw "Period must be greater than 0!\n";
    } catch (std::exception e) {
        std::cout << "Invalid input, try again!" << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    } catch (const char* msg) {
        std::cout << msg << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    clc_cin();
    std::cout << std::endl;
    FourierSeries fs = gen_square_wave_fs(period, n_coefficients);
    plot_fourier(fs);
}

// takes variable inputs of a_k and b_k
void run_input_fs() {
    FourierSeries fs;

    try {
        std::string input;
        std::cout << "Enter period of signal: ";
        std::cin >> input;
        float period = std::stof(input);
        if (period <= 0) throw "Period must be greater than 0!";
        fs.set_period(period);
    } catch (std::exception e) {
        std::cout << "Invalid input, try again!" << std::endl;
        clc_cin();
        return;
    } catch (const char* msg) {
        std::cout << msg << std::endl;
        clc_cin();
        return;
    }

    std::cout << "Getting values for a_k/b_k coefficients (enter non-numeric "
                 "to end)\n";
    try {
        int k = 0;
        std::string input;
        while (true) {
            std::cout << "Enter value for a_k" << k << ": ";
            std::cin >> input;
            float a_k = std::stof(input);
            fs.a_ks.push_back(a_k);
            k++;
        }
    } catch (std::exception e) {
        // do nothing
    }

    try {
        int k = 1;
        std::string input;
        while (true) {
            std::cout << "Enter value for b_k" << k << ": ";
            std::cin >> input;
            float b_k = std::stof(input);
            fs.b_ks.push_back(b_k);
            k++;
        }
    } catch (std::exception e) {
        // do nothing
    }
    clc_cin();
    std::cout << std::endl;
    plot_fourier(fs);
}

void change_plotter_config() {
    std::cout << "Current config: \n"
              << "tick: " << PlotterConfig::get_instance().tick << std::endl
              << "count: " << PlotterConfig::get_instance().count << std::endl
              << "min: " << PlotterConfig::get_instance().min << std::endl
              << "max: " << PlotterConfig::get_instance().max << std::endl;

    try {
        std::string input;

        std::cout << "Enter new tick: ";
        std::cin >> input;
        float tick = std::stof(input);
        if (tick <= 0) throw "Invalid tick number";
        PlotterConfig::get_instance().tick = tick;

        std::cout << "Enter new count: ";
        std::cin >> input;
        int count = std::stoi(input);
        if (count <= 0) throw "Invalid count number";
        PlotterConfig::get_instance().count = count;

        std::cout << "Enter new min: ";
        std::cin >> input;
        float min = std::stoi(input);
        PlotterConfig::get_instance().min = min;

        std::cout << "Enter new max: ";
        std::cin >> input;
        float max = std::stoi(input);
        PlotterConfig::get_instance().max = max;
    } catch (std::exception e) {
        std::cout << "Invalid input, aborting changes!\n";
    } catch (const char* msg) {
        std::cout << msg << std::endl;
    }

    // clears cin
    clc_cin();
}