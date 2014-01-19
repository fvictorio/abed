#include "../include/tester.hpp"

namespace abed {

    void Tester::resubstitution () {
        DataSet* data_set_temp = data_set->clone();

        classifier->train(data_set_temp);

        unsigned int n = data_set_temp->size();
        unsigned int correct = 0;
        for (unsigned int i = 0; i < n; i++) {
            int label_a, label_b;

            label_a = data_set->get_data_point(i)->get_label();
            label_b = data_set_temp->get_data_point(i)->get_label();

            if (label_a == label_b) correct++;
        }

        delete data_set_temp;

        //TODO do something with correct
    }

}
