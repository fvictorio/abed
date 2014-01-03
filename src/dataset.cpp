#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include "../include/dataset.hpp"

namespace abed {

    // TODO error check
    StaticDataSet::StaticDataSet (const char* filename, DATA_FMT data_fmt) {
        std::ifstream file_handler(filename);
        this->read(file_handler, data_fmt);
        file_handler.close();
    }

    // TODO: error checking (with c++ errors or returning
    // an int or enum)
    void StaticDataSet::read (std::istream& is, DATA_FMT data_fmt) {
        using std::string;
        using std::stringstream;
        using std::getline;

        int d;
        if (data_fmt == SSV || data_fmt == CSV) {
            is >> d;

            // Ignore rest of line
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            string line;
            while (getline(is, line)) {
                stringstream ss;
                ss << line;

                StaticDataPoint sdp;
                sdp.features.resize(d);

                for (int i = 0; i < d; i++) {
                    ss >> sdp.features[i];
                }

                // Try to read label
                int label;
                ss >> label;
                if (ss) {
                    sdp.labeled = true;
                    sdp.label = label;
                }

                data_points.push_back(sdp);
            }
        }
    }

}
