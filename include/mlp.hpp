#ifndef ABED_MLP_HPP
#define ABED_MLP_HPP

#include <vector>
#include <climits>
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
        MLP (unsigned int d, unsigned int c, const vector<unsigned int> &hl, 
             double lr = 0.05, double m = 0.01, double wr = 0.25, unsigned int seed = UINT_MAX);
        virtual double train (const StaticDataSet&, 
                              double MAX_ERROR = DEFAULT_MAX_ERROR, 
                              unsigned int MAX_IT = DEFAULT_MAX_IT);
        virtual void initialize (unsigned int seed = UINT_MAX);
        virtual Classifier* clone () const {
            return new MLP(*this);
        }
        virtual unsigned int predict_label (const StaticDataPoint&) const;
    private:
        // Private member functions
        void compute_outputs (const StaticDataPoint&) const;

        // Used for debugging
        void print_weights () const;
        void print_error_terms () const;
        void print_outputs () const;
        
        // Attributes
        unsigned int dimension, no_classes;
        double learning_rate, momentum;
        double weights_range;
        unsigned int no_layers;
        vector<unsigned int> layers;
        vector<vector<vector<double> > > weights, delta_weights;
        mutable vector<vector<double> > outputs;
        vector<vector<double> > error_terms;
    };

}

#endif /* ABED_MLP_HPP */
