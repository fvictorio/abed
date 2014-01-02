#ifndef ABED_CLASSIFIER_HPP
#define ABED_CLASSIFIER_HPP

#include "dataset.hpp"
#include "dataconverter.hpp"

namespace abed {

    class Classifier {
    public:
        virtual ~Classifier () {}

        virtual double train (const StaticDataSet&) = 0;
        virtual double train (const DynamicDataSet&) = 0;
        virtual void classify (StaticDataSet&) = 0;
        virtual void classify (DynamicDataSet&) = 0;
    };

    class StaticClassifier : public Classifier {
    public:
        using Classifier::train; // Effective C++ Item 33
        using Classifier::classify; // Effective C++ Item 33

        StaticClassifier () { data_converter = new TrivialDataConverter; }
        virtual ~StaticClassifier () { delete data_converter; }
        virtual double train (const DynamicDataSet&);
        virtual void classify (DynamicDataSet&);
    protected:
        DataConverter *data_converter;
    };
}

#endif /* ABED_CLASSIFIER_HPP */
