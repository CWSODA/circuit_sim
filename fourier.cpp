#include "fourier.hpp"

#include <iostream>

#define PI 3.1415926535897932384f

FourierSeries gen_square_wave_fs(float period, unsigned int n_harmonics) {
    FourierSeries fs;

    if (n_harmonics == 0) {
        std::cout << "Invalid harmonics count, defaulting to 3" << std::endl;
        n_harmonics = 3;
    }

    // simplified formula from https://www.geogebra.org/m/wUanseCs
    // scaled by 4 / (PI * k)
    // only odd harmonics on sine (b_k)
    // last harmonic is at 2 * n_harmonics - 1
    // 3 harmonics
    // b_ks for k = 1,3,5
    // 2 * 3 - 1 = highest k of 5
    // n = 0 -> 3 - 1
    // highest n of 2
    // highest k of 2 * 2 + 1 = 5
    fs.b_ks.resize(2 * n_harmonics, 0.0f);
    for (size_t n = 0; n < n_harmonics; n++) {
        size_t k = 2 * n + 1;
        fs.b_ks.at(k) = 4.0f / PI / k;
    }

    // calculates fundamental frequency
    fs.w0 = 2 * PI / period;

    return fs;
}
