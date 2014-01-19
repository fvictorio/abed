#ifndef ABED_TESTER_HPP
#define ABED_TESTER_HPP

#include <stdexcept>
#include "classifier.hpp"
#include "dataset.hpp"

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
            if (!ds->is_labeled()) {
                throw std::domain_error("Every datapoint must be labeled.");
            }
        }
        void resubstitution ();
        //void hold_out (double);
        //void cross_validation (int);
        //void leave_one_out ();
    private:
        Classifier* classifier;
        DataSet* data_set;
    };
}

#endif /* ABED_TESTER_HPP */
