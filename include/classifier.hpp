#ifndef ABED_CLASSIFIER_HPP
#define ABED_CLASSIFIER_HPP

#include "dataset.hpp"
#include "dataconverter.hpp"

namespace abed {

    //! Abstract classifier class.
    //
    //! Classifier abstract the (also abstract)
    //! StaticClassifier and DynamicClassifier
    //! classes.

    class Classifier {
    public:
        virtual ~Classifier () {}

        //virtual double train (const StaticDataSet&) = 0;
        //virtual double train (const DynamicDataSet&) = 0;
        virtual double train (const DataSet*) = 0;
        //virtual void classify (StaticDataSet&) = 0;
        //virtual void classify (DynamicDataSet&) = 0;
        virtual void classify (DataSet*) const = 0;
    };

    //! Abstract static classifier class.
    //
    //! StaticClassifier is an abstraction of the
    //! classifiers used to classify static data.

    class StaticClassifier : public Classifier {
    public:
        //using Classifier::train; // Effective C++ Item 33
        //using Classifier::classify; // Effective C++ Item 33

        StaticClassifier () { data_converter = new TrivialDataConverter; }
        virtual ~StaticClassifier () { delete data_converter; }
        //virtual double train (const DynamicDataSet&);
        virtual double train (const DataSet*
        //virtual void classify (DynamicDataSet&);
        virtual void classify (DataSet*) const;
    protected:
        DataConverter *data_converter;
    };
}

#endif /* ABED_CLASSIFIER_HPP */
