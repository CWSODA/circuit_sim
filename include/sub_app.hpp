#pragma once

#include <iostream>

void display_welcome_msg();
void display_help_menu();
void run_logic_array();
void run_circuit_simulator();

void run_plotter();
void run_square_wave();
void run_input_fs();
void change_plotter_config();

inline void clc_cin() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
