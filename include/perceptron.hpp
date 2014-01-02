#ifndef ABED_PERCEPTRON_HPP
#define ABED_PERCEPTRON_HPP

#include <cmath>
#include "classifier.hpp"
#include "dataset.hpp"
#include "utilities.hpp"

namespace abed {

    class Perceptron : public StaticClassifier {
    public:
        Perceptron (unsigned int, double = 0.05);
        virtual double train (const StaticDataSet&);
        virtual void classify (StaticDataSet&);
    private:
        unsigned int dimension;
        double learning_rate;

        double bias;
        std::vector<double> weights;
    };

}

#endif /* ABED_PERCEPTRON_HPP */
