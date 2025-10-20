#pragma once

#include <vector>

// dynamically manages gate number and size
class GateArray {
   public:
    // constructors
    GateArray() {}
    GateArray(std::vector<std::vector<bool>> gates);

    // get and set functions
    void set(size_t gate_num, size_t index, bool val = true);
    std::vector<std::vector<bool>> get_data() const { return _data; }
    std::vector<bool> get_inputs() const { return _inputs; }

    void print();

   private:
    std::vector<std::vector<bool>> _data;

    // stores which inputs are required
    std::vector<bool> _inputs;
};