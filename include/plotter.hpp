#pragma once

#include <vector>

#include "fourier.hpp"

class Point {
   public:
    float x, y;

    Point(float x, float y) {
        this->x = x;
        this->y = y;
    }

    // plots a point
    void plot(bool is_lined = false, float min = -1.0f, float max = 1.0f);
};

void plot_graph(float x_increment, unsigned int x_length);

void plot_fourier(float x_increment, unsigned int x_length, FourierSeries fs);