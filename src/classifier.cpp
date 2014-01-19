#include <cassert>
#include "../include/classifier.hpp"

namespace abed {

    double StaticClassifier::train (const DynamicDataSet& dds) {
        //TODO for point in ddp convert and train
        return 0.0;
    }

    void StaticClassifier::classify (DynamicDataSet& dds) const {
        StaticDataSet sds = data_converter->d2s(dds);
        classify(sds);
    }

    double StaticClassifier::train (const DataSet* ds) {
        double result = 0.0;

        if (ds->get_type() == DataSet::STATIC) {
            const StaticDataSet* sds = dynamic_cast<const StaticDataSet*>(ds);
            result = this->train(*sds);
        }
        else if (ds->get_type() == DataSet::DYNAMIC) {
            const DynamicDataSet* dds = dynamic_cast<const DynamicDataSet*>(ds);
            result = this->train(*dds);
        }
        else {
            assert(false);
        }

        return result;
    }

    void StaticClassifier::classify (DataSet* ds) const {
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

}
