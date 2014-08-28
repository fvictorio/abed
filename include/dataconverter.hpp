#ifndef ABED_DATACONVERTER_H
#define ABED_DATACONVERTER_H

#include <cassert>
#include "dataset.hpp"

namespace abed {

    //! \brief Abstract class that converts \ref DataSet "datasets" 
    //! and \ref DataPoint "datapoints".
    //
    //! The different derived classes of DataConverter provide
    //! alternative ways of transforming static data into
    //! dynamic data and vice versa.

    class DataConverter {
    public:
        virtual ~DataConverter () {}
        virtual StaticDataSet d2s (const DynamicDataPoint&) = 0;
        virtual StaticDataSet d2s (const DynamicDataSet&) = 0;
    };

    //! Transform data in a very simple way.

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
