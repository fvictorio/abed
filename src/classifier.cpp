#include "../include/classifier.hpp"

namespace abed {

    double StaticClassifier::train (const DynamicDataSet& dds) {
        //TODO for point in ddp convert and train
        return 0.0;
    }

    void StaticClassifier::classify (DynamicDataSet& dds) {
        StaticDataSet sds = data_converter->d2s(dds);
        classify(sds);
    }

}
