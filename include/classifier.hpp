#ifndef ABED_CLASSIFIER_HPP
#define ABED_CLASSIFIER_HPP

#include <climits>
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

        virtual void initialize (unsigned int seed = UINT_MAX) = 0;

        virtual Classifier* clone () const = 0;

        virtual double train (const DataSet*,
                              double MAX_ERROR = DEFAULT_MAX_ERROR, 
                              unsigned int MAX_IT = DEFAULT_MAX_IT);
        virtual double train (const StaticDataSet&, 
                              double MAX_ERROR = DEFAULT_MAX_ERROR, 
                              unsigned int MAX_IT = DEFAULT_MAX_IT) = 0;
        virtual double train (const DynamicDataSet&,
                              double MAX_ERROR = DEFAULT_MAX_ERROR, 
                              unsigned int MAX_IT = DEFAULT_MAX_IT) = 0;

        virtual void classify (DataSet*) const;
        virtual void classify (StaticDataSet&) const;
        virtual void classify (DynamicDataSet&) const;

        virtual unsigned int test (const DataSet*) const;
        virtual unsigned int predict_label (const DataPoint*) const;
        virtual unsigned int predict_label (const StaticDataPoint&) const = 0;
        virtual unsigned int predict_label (const DynamicDataPoint&) const = 0;
    protected:
        static const double DEFAULT_MAX_ERROR = 0.05;
        static const unsigned int DEFAULT_MAX_IT = 1000;
    };

    //! Abstract static classifier class.
    //
    //! StaticClassifier is an abstraction of the
    //! classifiers used to classify static data.

    class StaticClassifier : public Classifier {
    public:
        using Classifier::train;
        using Classifier::classify;
        using Classifier::predict_label;

        StaticClassifier () { data_converter = new TrivialDataConverter; }
        virtual ~StaticClassifier () { delete data_converter; }

        virtual double train (const DynamicDataSet&,
                              double MAX_ERROR = DEFAULT_MAX_ERROR, 
                              unsigned int MAX_IT = DEFAULT_MAX_IT);

        virtual unsigned int predict_label (const DynamicDataPoint&) const;
    protected:
        DataConverter *data_converter;
    };
} // namespace abed

#endif /* ABED_CLASSIFIER_HPP */
