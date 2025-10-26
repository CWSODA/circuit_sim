#include "logic_array.hpp"

#include <fstream>
#include <iostream>

// #define DEBUG_LOADER

void LogicArray::get_input() {
    const std::vector<bool> required_inputs = and_gates.get_inputs();
    std::vector<bool> inputs;
    inputs.resize(required_inputs.size(), false);

    for (size_t i = 0; i < required_inputs.size(); i++) {
        // if input is required, prompt user for it
        if (required_inputs[i]) {
            char input;
            std::cout << "Please enter the value for "
                      << static_cast<char>(i + 'A')
                      << " (0 for false, 1 for true)" << std::endl;
            std::cin >> input;

            if (input == '1') {
                inputs[i] = true;
            } else if (input != '0') {
                std::cout << "Please enter a valid input!" << std::endl;
                // restarts the current input
                i--;
            }
        }
    }
    // clears cin
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    this->load_input(LogicInput(inputs));
}

void LogicArray::load_input(LogicInput inputs) {
    if (inputs.get_data().size() < and_gates.get_inputs().size() * 2) {
        std::cout << "Error! Invalid input size" << std::endl;
        return;
    }

    std::vector<bool> and_gate_outputs;

    // for each and gate
    for (auto const& and_gate : and_gates.get_data()) {
        bool output = true;

        for (size_t i = 0; i < and_gate.size(); i++) {
            // if and gate requires an input, but the corresponding input is
            // false, then the and gate output is false
            if (and_gate.at(i) && !inputs.get_data().at(i)) {
                output = false;
            }
        }

        and_gate_outputs.push_back(output);
    }

    // resets outputs first
    array_output.clear();
    // for each or gate
    for (auto const& or_gate : or_gates.get_data()) {
        bool output = false;

        for (size_t i = 0; i < or_gate.size(); i++) {
            if (or_gate.at(i) && and_gate_outputs.at(i)) {
                output = true;
                break;
            }
        }
        array_output.push_back(output);
    }
}

std::vector<bool> LogicArray::get_output() const { return array_output; }

LogicArray::LogicArray(const char* filename) {
    // opens file
    std::fstream file(filename);

    if (!file) {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }

    // each line is a new output
    // parse lines
    std::string line;
    size_t or_gate_count = 0;
    size_t and_gate_count = 0;
    while (std::getline(file, line)) {
        size_t index = 0;

        for (char c : line) {
#ifdef DEBUG_LOADER
            std::cout << "Working on: " << c << std::endl;
#endif
            // index for and gate from A->Z
            if (c >= 'A' && c <= 'Z') {
                // each letter is split into two
                // one for the letter, and one for its compliment
                index = (c - 'A') * 2;

                and_gates.set(and_gate_count, index);
            } else if (c == '\'') {
                if (index % 2 == 1) {
                    std::cout
                        << "Warning: Multiple ' on same letter is ignored!\n";
                } else {
                    // resets bit for the letter and
                    // sets bit for the compliment of the letter
                    and_gates.set(and_gate_count, index, false);
                    and_gates.set(and_gate_count, index + 1);
                }
            } else if (c == '+') {
                or_gates.set(or_gate_count, and_gate_count);
                and_gate_count++;
            }
        }

        // adds the last and gate to the or gate
        or_gates.set(or_gate_count, and_gate_count);
        // increments or gate
        or_gate_count++;
    }

    // ABC + BDC + H'
    // first and gate is ABC
    // second is BDC
    // add hashmap for indexing repeats?
}

void LogicArray::print_output() const {
    std::cout << "Printing outputs: \n";
    for (auto output : array_output) {
        std::cout << "Result: ";
        if (output)
            std::cout << "true";
        else
            std::cout << "false";
        std::cout << std::endl;
    }
}

LogicInput::LogicInput(std::vector<bool> input) {
    for (auto value : input) {
        if (value) {
            data.push_back(true);
            data.push_back(false);
        } else {
            data.push_back(false);
            data.push_back(true);
        }
    }
}

std::vector<bool> LogicInput::get_data() const {  //
    return data;
}