#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include <climits>
#include "../include/dataset.hpp"
#include "../include/utilities.hpp"

//! @todo
//! - error check in StaticDataSet constructor
//! - error check in istream reading

namespace abed {

    StaticDataSet::StaticDataSet (const char* filename, DATA_FMT data_fmt) {
        std::ifstream file_handler(filename);
        this->read(file_handler, data_fmt);
        file_handler.close();
    }

    void StaticDataSet::read (std::istream& is, DATA_FMT data_fmt) {
        using std::string;
        using std::stringstream;
        using std::getline;

        unsigned int d, c;
        if (data_fmt == SSV || data_fmt == CSV) {
            is >> d;
            is >> c;
            this->dimension = d;
            this->no_classes = c;

            //TODO CSV

            // Ignore rest of line
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            string line;
            while (getline(is, line)) {
                stringstream ss;
                ss << line;

                StaticDataPoint sdp;
                sdp.features.resize(d);

                for (unsigned int i = 0; i < d; i++) {
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

    DataSet* StaticDataSet::indexed_clone (const std::vector<unsigned int>& indexes) const {
        StaticDataSet *indexed_dataset = new StaticDataSet;
        
        indexed_dataset->dimension = this->dimension;
        indexed_dataset->no_classes = this->no_classes;
        
        for (unsigned int i = 0; i < indexes.size(); i++) {
            indexed_dataset->data_points.push_back(this->data_points[indexes[i]]);
        }

        return indexed_dataset;
    }

    void StaticDataSet::slice (unsigned int a, unsigned int b, DataSet*& sliced_ds, DataSet*& remaining_ds) const {
        StaticDataSet* sliced_sds = new StaticDataSet;
        StaticDataSet* remaining_sds = new StaticDataSet;

        sliced_sds->dimension = this->dimension;
        sliced_sds->no_classes = this->no_classes;
        remaining_sds->dimension = this->dimension;
        remaining_sds->no_classes = this->no_classes;

        for (unsigned int i = 0; i < a; i++) {
            remaining_sds->data_points.push_back(this->data_points[i]);
        }
        for (unsigned int i = a; i < b; i++) {
            sliced_sds->data_points.push_back(this->data_points[i]);
        }
        for (unsigned int i = b; i < this->data_points.size(); i++) {
            remaining_sds->data_points.push_back(this->data_points[i]);
        }

        sliced_ds = sliced_sds;
        remaining_ds = remaining_sds;
    }

    DataSet* DynamicDataSet::indexed_clone (const std::vector<unsigned int>& indexes) const {
        DynamicDataSet *indexed_dataset = new DynamicDataSet;

        indexed_dataset->dimension = this->dimension;
        indexed_dataset->no_classes = this->no_classes;
        
        for (unsigned int i = 0; i < indexes.size(); i++) {
            indexed_dataset->data_points.push_back(this->data_points[indexes[i]]);
        }

        return indexed_dataset;
    }

    DataSet* StaticDataSet::bootstrap (unsigned int n) const {
        if (n == UINT_MAX) n = data_points.size();
        
        StaticDataSet* bootstrapped_ds = new StaticDataSet;
        bootstrapped_ds->dimension = this->dimension;
        bootstrapped_ds->no_classes = this->no_classes;

        unsigned int idx;
        for (unsigned int i = 0; i < n; i++) {
            //TODO randomness
            idx = static_cast<unsigned int>(randrange(0.0, data_points.size()));
            //TODO there is a slight chance of getting idx == data_points.size() that
            //I should avoid somehow (an epsilon?)
            bootstrapped_ds->data_points.push_back(this->data_points[idx]);
        }

        return bootstrapped_ds;
    }

    DataSet* DynamicDataSet::bootstrap (unsigned int n) const {
        if (n == UINT_MAX) n = data_points.size();
        
        DynamicDataSet* bootstrapped_ds = new DynamicDataSet;
        bootstrapped_ds->dimension = this->dimension;
        bootstrapped_ds->no_classes = this->no_classes;

        for (unsigned int i = 0; i < n; i++) {
            //TODO randomness
            unsigned int idx = static_cast<unsigned int>(randrange(0.0, data_points.size()));
            bootstrapped_ds->data_points.push_back(this->data_points[idx]);
        }

        return bootstrapped_ds;
    }

    void DynamicDataSet::slice (unsigned int a, unsigned int b, DataSet*& sliced_ds, DataSet*& remaining_ds) const {
        DynamicDataSet* sliced_dds = new DynamicDataSet; // TODO necesario?
        DynamicDataSet* remaining_dds = new DynamicDataSet;

        sliced_dds->dimension = this->dimension;
        sliced_dds->no_classes = this->no_classes;
        remaining_dds->dimension = this->dimension;
        remaining_dds->no_classes = this->no_classes;

        for (unsigned int i = 0; i < a; i++) {
            remaining_dds->data_points.push_back(this->data_points[i]);
        }
        for (unsigned int i = a; i < b; i++) {
            sliced_dds->data_points.push_back(this->data_points[i]);
        }
        for (unsigned int i = b; i < this->data_points.size(); i++) {
            remaining_dds->data_points.push_back(this->data_points[i]);
        }

        sliced_ds = sliced_dds;
        remaining_ds = remaining_dds;
    }

}
