#include <cassert>
#include <cmath>
#include <iostream>
#include <climits>
#include "../include/perceptron.hpp"
#include "../include/utilities.hpp"

namespace abed {

    Perceptron::Perceptron (unsigned int d, double lr, double wr, unsigned int seed)
                           : dimension(d), learning_rate(lr), weights_range(wr) {
        this->initialize(seed);
    }

    void Perceptron::initialize (unsigned int seed) {
        if (seed != UINT_MAX) {
            srand(seed);
        }
        bias = randrange(-weights_range, weights_range);
        weights.resize(dimension, 0.0);
        for (unsigned int i = 0; i < weights.size(); i++) {
            weights[i] = randrange(-weights_range, weights_range);
        }
    }

    double Perceptron::train (const StaticDataSet& sds, double MAX_ERROR, unsigned int MAX_IT) {
        double total_error = 0.0;

        for (unsigned int i = 1; i <= MAX_IT; i++) {
            total_error = 0.0;
            for (unsigned int j = 0; j < sds.size(); j++) {
                const StaticDataPoint& x = sds[j];
                double y = 0.0;

                y += bias;
                for (unsigned int i = 0; i < dimension; i++) {
                    y += weights[i] * x[i];
                }

                double error = x.diff(y);
                bias += learning_rate * error;
                for (unsigned int i = 0; i < dimension; i++) {
                    weights[i] += learning_rate * error * x[i];
                }

                total_error += std::fabs(error);
            }
            total_error /= sds.size();
            if (total_error <= MAX_ERROR) 
                return total_error;
        }

        return total_error;
    }

    unsigned int Perceptron::predict_label (const StaticDataPoint& x) const {
        double y = 0.0;

        y += bias;
        for (unsigned int i = 0; i < dimension; i++) {
            y += weights[i] * x[i];
        }

        return round(y);
    }
}
