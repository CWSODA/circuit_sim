#pragma once

#include <vector>
#include <span>
#include <bitset>

#include "gates.hpp"

class LogicInput {
   public:
    // constructor takes in booleans for A,B,C and splits them into each letter
    // and their complements
    // data stores A, A', B, B', ...
    LogicInput(std::vector<bool> input);

    // returns data
    std::vector<bool> get_data() const;

   private:
    std::vector<bool> data;
};

class LogicArray {
   public:
    GateArray and_gates;
    GateArray or_gates;

    void get_input();
    void load_input(LogicInput input);
    std::vector<bool> get_output() const;

    LogicArray(const char* filename);
    LogicArray() {}

   private:
    std::vector<bool> array_output;
};