#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <set>
#include "timing.hpp"

constexpr size_t N = 100000000; // 10^8
const double s = 1.00000000001;
constexpr double min_runtime = 0.5;

void run_benchmark(size_t stride, const std::string& mode, std::ofstream& out) {
    std::vector<double> a(N, 1.0);

    // Warm-up
    for (size_t i = 0; i < N; i += stride) {
        a[i] *= s;
    }

    // Benchmark loop
    size_t repeats = 0;
    double start = getTimeStamp();
    double elapsed = 0.0;

    do {
        for (size_t i = 0; i < N; i += stride) {
            a[i] *= s;
        }
        ++repeats;
        elapsed = getTimeStamp() - start;
    } while (elapsed < min_runtime);

    size_t updates = ((N + stride - 1) / stride) * repeats;
    double updates_per_sec = updates / elapsed;

    std::cout << "[" << mode << "] M = " << stride
              << ", MUpdates/s = " << updates_per_sec / 1e6
              << ", Time = " << elapsed << "s\n";

    out << stride << "," << updates_per_sec / 1e6 << "," << elapsed << "," << repeats << "\n";
}

int main() {
    // Power-of-2 strides: M = 2^0 to 2^20
    std::ofstream out_pow2("results_pow2.csv");
    for (int i = 0; i <= 20; ++i) {
        size_t stride = static_cast<size_t>(1) << i;
        run_benchmark(stride, "POW2", out_pow2);
    }
    out_pow2.close();

    // M = 8 * 1.2^n for n = 0 to 40, unique & sorted
    std::set<size_t> strides;
    for (int n = 0; n <= 40; ++n) {
        size_t stride = static_cast<size_t>(std::round(8.0 * std::pow(1.2, n)));
        if (stride <= 1000000) strides.insert(stride);
    }

    std::ofstream out_pow1p2("results_pow1p2.csv");
    for (auto stride : strides) {
        run_benchmark(stride, "POW1P2", out_pow1p2);
    }
    out_pow1p2.close();

    return 0;
}
