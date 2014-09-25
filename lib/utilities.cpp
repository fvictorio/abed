#include <vector>
#include "../include/utilities.hpp"

namespace abed {
    void normalize_distribution(std::vector<double>& d) {
        const unsigned int N = d.size();
        double sum = 0.0;

        for (unsigned int i = 0; i < N; i++) {
            sum += d[i];
        }

        for (unsigned int i = 0; i < N; i++) {
            d[i] /= sum;
        }
    }
} // namespace abed
