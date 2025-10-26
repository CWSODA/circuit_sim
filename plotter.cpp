#include "plotter.hpp"

#include <stdio.h>
#include <math.h>
#include <iostream>

#define WIDTH 100
#define PI 3.1415926535897932384f

void Point::plot(bool is_lined) {
    float min = PlotterConfig::get_instance().min;
    float max = PlotterConfig::get_instance().max;
    printf("x: %10.3f| ", x);
    printf("y: %10.3f |", y);

    if (is_lined) {
        printf("---");
    } else {
        printf("   ");
    }

    // rescale min->max to 0->WIDTH
    int offset = round((y - min) / (max - min) * (WIDTH - 1)) + 1;

    printf("%*c\n", offset, '*');
}

void plot_graph() {
    float x_increment = PlotterConfig::get_instance().tick;
    unsigned int x_length = PlotterConfig::get_instance().count;
    unsigned int x_count = 0;

    float y;

    // plots x_length number of values
    // increment x then print with fixed width of 10
    while (x_count < x_length) {
        float x = x_count * x_increment;
        y = sinf(2 * PI * x);

        // for every multiple of 10, insert tickmarks
        // else insert blank spaces equal to tickmark width so the offset is the
        // same
        bool is_lined = false;
        if (x_count % 10 == 0) {
            is_lined = true;
        }

        Point(x, y).plot(is_lined);

        x_count++;
    }
}

void plot_fourier(FourierSeries fs) {
    // formula = sum of a_k * cos(kwt) + b_k * sin(kwt)
    float x_increment = PlotterConfig::get_instance().tick;
    unsigned int x_length = PlotterConfig::get_instance().count;
    unsigned int x_count = 0;

    std::cout << "plotting fs\n";
    for (auto v : fs.b_ks) {
        std::cout << v << ", ";
    }
    std::cout << std::endl;

    while (x_count < x_length) {
        float x = x_count * x_increment;
        float y = 0;

        // calculates cosine terms
        for (size_t k = 0; k < fs.a_ks.size(); k++) {
            y += fs.a_ks[k] * cosf(k * fs.w0 * x);
        }

        // calculates sine terms
        for (size_t k = 1; k < fs.b_ks.size(); k++) {
            y += fs.b_ks[k] * sinf(k * fs.w0 * x);
        }

        // leaves some leeway in min/max for gibbs phenomenon
        Point(x, y).plot(false);

        x_count++;
    }
}