#ifndef ABED_UTILITIES_H
#define ABED_UTILITIES_H

#include <cstdlib>
#include <cmath>

namespace abed {
    inline double randrange () {
        return (double) rand() / RAND_MAX;
    }
    inline double randrange (double a, double b) {
        return a + (b-a) * rand() / RAND_MAX;
    }

    inline int round (double x) {
        return static_cast<int>(floor(x + 0.5));
    }

    inline double sigmoid (double x) {
        return 1.0 / (1.0 + exp(-x));
    }

    void normalize_distribution(std::vector<double>& d);
} // namespace abed

#endif /* ABED_UTILITIES_HPP */
