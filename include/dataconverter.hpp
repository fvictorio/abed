#ifndef ABED_DATACONVERTER_H
#define ABED_DATACONVERTER_H

#include <cassert>
#include "dataset.hpp"

namespace abed {

    // XXX podrian ser funciones
    class DataConverter {
    public:
        virtual StaticDataSet d2s (const DynamicDataPoint&) = 0;
        virtual StaticDataSet d2s (const DynamicDataSet&) = 0;
    };

    class TrivialDataConverter : public DataConverter {
    public:
        virtual StaticDataSet d2s (const DynamicDataPoint& ddp) {
            //TODO for f in ddp sds.push(f)
            assert(false);
            return StaticDataSet("");
        }
        virtual StaticDataSet d2s (const DynamicDataSet& dds) {
            //TODO for ddp in dds
            //         for f in ddp sds.push(f)
            assert(false);
            return StaticDataSet("");
        }
    };

}

#endif
