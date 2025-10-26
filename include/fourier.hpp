#pragma once

#include <vector>

#define PI 3.1415926535897932384f

struct FourierSeries {
    float w0;

    // coefficients. b_k0 is not important so is initialized so push_back() can
    // be used directly for b_k1
    std::vector<float> a_ks;
    std::vector<float> b_ks = std::vector<float>(1, 0.0f);

    void set_period(float period) {
        if (period <= 0) return;
        w0 = 2 * PI / period;
    }
};

FourierSeries gen_square_wave_fs(float period, unsigned int n_harmonics);
