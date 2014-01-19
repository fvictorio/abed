#include <cassert>
#include <cmath>
#include "../include/perceptron.hpp"

namespace abed {

    Perceptron::Perceptron (unsigned int d, double lr) {
        dimension = d;

        bias = 0.0;
        weights.resize(dimension, 0.0);

        learning_rate = lr;
    }

    double Perceptron::train (const StaticDataSet& sds, int max_it, double min_error) {
        double total_error = 0.0;
        for (int i = 1; i <= max_it; i++) {
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
            if (total_error <= min_error) return total_error;
        }

        return total_error;
    }

    void Perceptron::classify (StaticDataSet& sdp) const {
        for (unsigned int i = 0; i < sdp.size(); i++) {
            StaticDataPoint& x = sdp[i];
            double y = 0.0;

            y += bias;
            for (unsigned int i = 0; i < dimension; i++) {
                y += weights[i] * x[i];
            }

            x.set_label(round(y));
        }
    }

}
