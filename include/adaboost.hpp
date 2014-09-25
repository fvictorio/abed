#ifndef ABED_ADABOOST_HPP
#define ABED_ADABOOST_HPP

#include <vector>
#include "ensemble.hpp"

namespace abed {

    using std::vector;

    class AdaBoost : public EnsembleClassifier {
    public:
        AdaBoost (int d, int c) : dimension(d), no_classes(c) {}
        virtual void initialize (unsigned int seed = UINT_MAX);
        virtual Classifier* clone () const {
            return new AdaBoost(*this);
        }

        virtual double train (const StaticDataSet&, 
                              double MAX_ERROR = DEFAULT_MAX_ERROR, 
                              unsigned int MAX_IT = DEFAULT_MAX_IT);
        virtual double train (const DynamicDataSet&,
                              double MAX_ERROR = DEFAULT_MAX_ERROR, 
                              unsigned int MAX_IT = DEFAULT_MAX_IT);

        virtual unsigned int predict_label (const StaticDataPoint&) const;
        virtual unsigned int predict_label (const DynamicDataPoint&) const;

    private:
        unsigned int dimension;
        unsigned int no_classes;

        vector<double> normalized_error;
    };
} // namespace abed

#endif /* ABED_ADABOOST_HPP */
