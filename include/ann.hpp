#ifndef ABED_MLP_HPP
#define ABED_MLP_HPP

#include <cmath>
#include "classifier.hpp"
#include "dataset.hpp"
#include "utilities.hpp"

namespace abed {

    //! Multilayer Perceptron (MLP) implementation.
    //
    //! Feedforward artificial neural network used for
    //! classifying data 
    //! that isn't linearly separable, trained
    //! with the backpropagation algorithm.

    class MLP : public StaticClassifier {
    public:
    private:
    };

}

#endif /* ABED_MLP_HPP */
