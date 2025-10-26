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
    void plot(bool is_lined = false);
};

class PlotterConfig {
   public:
    static PlotterConfig& get_instance() {
        static PlotterConfig instance;
        return instance;
    }

    float tick = 0.05;
    unsigned int count = 100;
    float min = -1.0f;
    float max = 1.0f;

   private:
    PlotterConfig() {}

    PlotterConfig(PlotterConfig& other) = delete;
    void operator=(const PlotterConfig&) = delete;
};

void plot_graph();

void plot_fourier(FourierSeries fs);