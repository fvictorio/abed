#ifndef ABED_PERCEPTRON_HPP
#define ABED_PERCEPTRON_HPP

#include <cmath>
#include <climits>
#include "classifier.hpp"
#include "dataset.hpp"
#include "utilities.hpp"

namespace abed {

    //! Simple perceptron implementation.
    //
    //! A simple algorithm used for classify data
    //! that is linearly separable.

    class Perceptron : public StaticClassifier {
    public:
        Perceptron (unsigned int dimension, double learning_rate = 0.05,
                    double wr = 0.1, unsigned int seed = UINT_MAX);
        virtual double train (const StaticDataSet&, 
                              double MAX_ERROR = DEFAULT_MAX_ERROR, 
                              unsigned int MAX_IT = DEFAULT_MAX_IT);
        virtual void classify (StaticDataSet&) const;
        virtual void initialize (unsigned int seed = UINT_MAX);
    private:
        unsigned int dimension;
        double learning_rate;
        double weights_range;

        double bias;
        std::vector<double> weights;
    };

}

#endif /* ABED_PERCEPTRON_HPP */
