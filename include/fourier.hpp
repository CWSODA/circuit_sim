#include <vector>

struct FourierSeries {
    float w0;
    std::vector<float> a_ks, b_ks;
};

FourierSeries gen_square_wave_fs(float period, unsigned int n_harmonics);