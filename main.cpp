#include <iostream>

#include "sub_app.hpp"

int main(int argc, char* argv[]) {
    while (true) {
        display_welcome_msg();

        std::string input;
        std::getline(std::cin, input);

        if (input.size() != 1) continue;

        char c = input.at(0);
        switch (c) {
            case 'h':  // help menu
                display_help_menu();
                break;
            case 'l':  // logic array
                run_logic_array();
                break;
            case 'c':  // circuit simulator
                run_circuit_simulator();
                break;
            case 'p':  // plot graph
                run_plotter();
                break;
            case 'q':
                return 0;
        }
    }

    return 0;
}