#include "gates.hpp"

#include <iostream>

// #define DEBUG_SET

void GateArray::set(size_t gate_num, size_t index, bool val) {
#ifdef DEBUG_SET
    std::cout << "Inserting index: " << index << ", at gate count: " << gate_num
              << std::endl;
#endif
    // resize gate number if more is needed
    if (gate_num + 1 > _data.size()) {
        _data.resize(gate_num + 1);
    }

    // resizes vector to fit a larger index
    if (index + 1 > _data.at(gate_num).size()) {
        // 0,1 for A
        // 2,3 for B
        // all letters end on an odd number with compliments
        // but size is index + 1 so make index even
        size_t new_size = index + 1;
        if (new_size % 2 == 1) new_size++;

        _data.at(gate_num).resize(new_size, false);
    }

    _data.at(gate_num).at(index) = val;

    // Deals with which inputs are done
    // the letter the new value belongs to
    // 0,1 for A -> 0
    // 2,3 for B -> 1
    // 4,5 for C -> 2
    // integer truncates the 0.5
    // so 5/2 = 2.5 rounds down to 2
    size_t input_count = index / 2;
    if (_inputs.size() < input_count + 1) {
        // resizes input vector
        _inputs.resize(input_count + 1, false);
    }
    _inputs.at(input_count) = true;

#ifdef DEBUG_SET
    if (val)
        std::cout << "Set";
    else
        std::cout << "Reset";

    std::cout << " at index: " << index << ", gate number: " << gate_num
              << std::endl;
#endif
}

GateArray::GateArray(std::vector<std::vector<bool>> gates) { _data = gates; }

void GateArray::print() {
    std::cout << "Printing gate array:\n";
    for (auto& vec : _data) {
        for (auto val : vec) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;
    }
}