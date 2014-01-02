#include "../include/dataset.hpp"

namespace abed {

    StaticDataSet::StaticDataSet (const char* filename, DATA_FMT data_fmt) {
        std::ifstream file_handler(filename);
        // TODO error check
        this->read(file_handler, data_fmt);
        file_handler.close();
    }

    void StaticDataSet::read (std::istream& is, DATA_FMT data_fmt) {
        int d;
        // TODO: error checking (with c++ errors or returning
        // an int or enum)
        if (data_fmt == SSV || data_fmt == CSV) {
            is >> d;
            //TODO
        }
    }

}
