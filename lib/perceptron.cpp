#include <cassert>
#include <cmath>
#include <iostream>
#include <climits>
#include "../include/perceptron.hpp"
#include "../include/utilities.hpp"

namespace abed {

    Perceptron::Perceptron (unsigned int d, double lr, double wr, unsigned int seed) {
        dimension = d;

        if (seed == UINT_MAX) {
            srand(time(NULL));
        }
        else {
            srand(seed);
        }
        bias = randrange(-wr, wr);
        weights.resize(dimension, 0.0);
        for (unsigned int i = 0; i < weights.size(); i++) {
            weights[i] = randrange(-wr, wr);
        }

        learning_rate = lr;
    }

    double Perceptron::train (const StaticDataSet& sds, double MAX_ERROR, unsigned int MAX_IT) {
        double total_error = 0.0;

        for (unsigned int i = 1; i <= MAX_IT; i++) {
            total_error = 0.0;
            for (unsigned int j = 0; j < sds.get_size(); j++) {
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
            total_error /= sds.get_size();
            if (total_error <= MAX_ERROR) 
                return total_error;
        }

        std::cout << "Bias: " << bias << std::endl;
        for (unsigned int i = 0; i < weights.size(); i++) {
            std::cout << "Weight " << i << ": " << weights[i] << std::endl;
        }

        return total_error;
    }

    void Perceptron::classify (StaticDataSet& sds) const {
        for (unsigned int i = 0; i < sds.get_size(); i++) {
            StaticDataPoint& x = sds[i];
            double y = 0.0;

            y += bias;
            for (unsigned int i = 0; i < dimension; i++) {
                y += weights[i] * x[i];
            }

            x.set_label(round(y));
        }
    }

}
