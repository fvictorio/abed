#include <iostream>
#include <cassert>
#include "../include/classifier.hpp"

//! @todo 
//! - train for DynamicDataSet

namespace abed {
    
    unsigned int Classifier::test (const DataSet* ds) const {
        unsigned int no_correct = 0;
        
        for (unsigned int i = 0; i < ds->size(); i++) {
            int label_a, label_b;

            label_a = ds->get_data_point(i)->get_label();
            label_b = this->predict_label(ds->get_data_point(i));

            no_correct += (label_a == label_b ? 1 : 0);
        }

        return no_correct;
    }

    double StaticClassifier::train (const DynamicDataSet& dds, 
                                    double MAX_ERROR,
                                    unsigned int MAX_IT) {
        return 0.0;
    }

    double Classifier::train (const DataSet* ds, 
                              double MAX_ERROR,
                              unsigned int MAX_IT) {
        double result = 0.0;

        if (ds->get_type() == DataSet::STATIC) {
            const StaticDataSet* sds = dynamic_cast<const StaticDataSet*>(ds);
            result = this->train(*sds, MAX_ERROR, MAX_IT);
        }
        else if (ds->get_type() == DataSet::DYNAMIC) {
            const DynamicDataSet* dds = dynamic_cast<const DynamicDataSet*>(ds);
            result = this->train(*dds, MAX_ERROR, MAX_IT);
        }
        else {
            assert(false);
        }

        return result;
    }

    void Classifier::classify (DataSet* ds) const {
        if (ds->get_type() == DataSet::STATIC) {
            StaticDataSet* sds = dynamic_cast<StaticDataSet*>(ds);
            this->classify(*sds);
        }
        else if (ds->get_type() == DataSet::DYNAMIC) {
            DynamicDataSet* dds = dynamic_cast<DynamicDataSet*>(ds);
            this->classify(*dds);
        }
        else {
            assert(false);
        }
    }

    void Classifier::classify (StaticDataSet& sds) const {
        for (unsigned int n = 0; n < sds.size(); n++) {
            StaticDataPoint& x = sds[n];

            unsigned int predicted_label = this->predict_label(x);
            x.set_label(predicted_label);
        }
    }

    void Classifier::classify (DynamicDataSet& sdp) const {
        for (unsigned int n = 0; n < sdp.size(); n++) {
            DynamicDataPoint& x = sdp[n];

            unsigned int predicted_label = this->predict_label(x);
            x.set_label(predicted_label);
        }
    }

    unsigned int Classifier::predict_label (const DataPoint* dp) const {
        if (dp->get_type() == DataPoint::STATIC) {
            const StaticDataPoint* sdp = dynamic_cast<const StaticDataPoint*>(dp);
            return this->predict_label(*sdp);
        }
        else if (dp->get_type() == DataPoint::DYNAMIC) {
            const DynamicDataPoint* ddp = dynamic_cast<const DynamicDataPoint*>(dp);
            return this->predict_label(*ddp);
        }
        else {
            assert(false);
        }
    }

    unsigned int StaticClassifier::predict_label (const DynamicDataPoint& ddp) const {
        StaticDataSet sds = data_converter->d2s(ddp);
        assert(false);
        //TODO
        return 0;
    }

}
