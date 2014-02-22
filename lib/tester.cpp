#include "../include/tester.hpp"

//! @todo
//! - Finish resubstitution method (add pertinent class variables)

namespace abed {

    void Tester::resubstitution (double MAX_ERROR, unsigned int MAX_IT) {
        DataSet* data_set_temp = data_set->clone();

        if (MAX_ERROR < 0.0) { // both defaults
            classifier->train(data_set_temp);
        }
        else if (MAX_IT == UINT_MAX) { // only error default
            classifier->train(data_set_temp, MAX_ERROR);
        }
        else {
            classifier->train(data_set_temp, MAX_ERROR, MAX_IT);
        }
        classifier->classify(data_set_temp);

        unsigned int n = data_set_temp->get_size();
        unsigned int correct = 0;
        for (unsigned int i = 0; i < n; i++) {
            int label_a, label_b;

            label_a = data_set->get_data_point(i)->get_label();
            label_b = data_set_temp->get_data_point(i)->get_label();

            if (label_a == label_b) correct++;
        }

        delete data_set_temp;
        
        this->percentage = static_cast<double>(correct) / n;
    }
}
