#ifndef ABED_TESTER_HPP
#define ABED_TESTER_HPP

#include <stdexcept>
#include <climits>
#include "classifier.hpp"
#include "dataset.hpp"

//! \todo
//! - Constructor that takes Classifier& and DataSet& and calls
//    the other constructor

namespace abed {

    //! Tester class.
    //
    //! Tester implements functions that,
    //! given a classifier and a
    //! dataset, returns statistics about
    //! how good the predictions of the
    //! classifier are.
    //!
    //! The classifier and the dataset pointers 
    //! can be passed at construction or
    //! setted later.

    class Tester {
    public:
        Tester (Classifier* c, DataSet* ds) : classifier(c), data_set(ds) {
            percentage = -1.0;
            if (!ds->is_labeled()) {
                throw std::domain_error("Every datapoint must be labeled.");
            }
        }
        void resubstitution (double MAX_ERROR = -1.0,
                             unsigned int MAX_IT = UINT_MAX);
        void hold_out (double p, double MAX_ERROR = -1.0,
                                 unsigned int MAX_IT = UINT_MAX);
        void cross_validation (unsigned int K, double MAX_ERROR = -1.0,
                                               unsigned int MAX_IT = UINT_MAX);
        void leave_one_out (double MAX_ERROR = -1.0,
                            unsigned int MAX_IT = UINT_MAX);
        double get_percentage () const { return percentage; }
    private:
        double train_classifier (DataSet* ds, double MAX_ERROR, unsigned int MAX_IT) const;

        Classifier* classifier;
        DataSet* data_set;
        double percentage;
    };
}

#endif /* ABED_TESTER_HPP */
