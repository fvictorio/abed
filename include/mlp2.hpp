#ifndef ABED_MLP2_HPP
#define ABED_MLP2_HPP

#include <vector>
#include "classifier.hpp"

namespace abed {

    //! Multilayer Perceptron (MLP) implementation.
    //
    //! Feedforward artificial neural network used for
    //! classifying data 
    //! that isn't linearly separable, trained
    //! with the backpropagation algorithm.

    using std::vector;

    class MLP2 : public StaticClassifier {
    public:
        MLP2 (unsigned int d, unsigned int c, const vector<unsigned int>& hl, double lr, double mom);
        virtual double train (const StaticDataSet& sds);
        virtual void classify (StaticDataSet& sds) const;
    private:
        void compute_outputs (const StaticDataPoint&) const;
        unsigned int predict (const StaticDataPoint&) const;
    private:
        unsigned int dimension;
        unsigned int no_labels;
        vector<unsigned int> layers;
        unsigned int no_layers;
        double learning_rate, momentum;

        vector<vector<vector<double> > > weights;
        vector<vector<vector<double> > > delta_weights;
        mutable vector<vector<double> > outputs;
    };

}

#endif /* ABED_MLP2_HPP */
