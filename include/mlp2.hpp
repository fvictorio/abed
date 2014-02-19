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

    class MLP : public StaticClassifier {
    public:
        MLP (unsigned int d, unsigned int c, const vector<unsigned int> &hl, double lr, double m);
        void classify (StaticDataSet& sds) const;
        double train (const StaticDataSet& sds);
    private:
        void compute_outputs (const StaticDataPoint&) const;
        unsigned int predict_label (const StaticDataPoint&) const;
        void print_weights () const;
        void print_error_terms () const;
        void print_outputs () const;
        
        unsigned int dimension, no_classes;
        double learning_rate, momentum;
        unsigned int no_layers;
        vector<unsigned int> layers;
        vector<vector<vector<double> > > weights;
        mutable vector<vector<double> > outputs;
        vector<vector<double> > error_terms;
    };

}

#endif /* ABED_MLP2_HPP */
