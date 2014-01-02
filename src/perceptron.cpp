#include <cassert>
#include "../include/perceptron.hpp"

namespace abed {

    Perceptron::Perceptron (unsigned int d, double lr) {
        dimension = d;

        bias = 0.0;
        weights.resize(dimension, 0.0);

        learning_rate = lr;
    }

    double Perceptron::train (const StaticDataSet& sds) {
        //TODO recorrer y entrenar
        //double y = 0.0;

        //y += bias;
        //for (unsigned int i = 0; i < dimension; i++) {
        //    y += weights[i] * x[i];
        //}

        //double error = x.diff(y);
        //bias += learning_rate * error;
        //for (unsigned int i = 0; i < dimension; i++) {
        //    weights[i] += learning_rate * error * x[i];
        //}

        //return error;
        assert(false);
        return 0.0;
    }

    void Perceptron::classify (StaticDataSet& sdp) {
        //TODO recorrer y poner label
        //double y = 0.0;

        //y += bias;
        //for (unsigned int i = 0; i < dimension; i++) {
        //    y += weights[i] * x[i];
        //}
        assert(false);
    }

}
