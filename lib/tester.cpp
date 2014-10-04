#include <iostream>
#include "../include/dataset.hpp"
#include "../include/tester.hpp"

namespace abed {
    using std::cout;
    using std::endl;

    void Tester::resubstitution (double MAX_ERROR, unsigned int MAX_IT) {
        classifier->initialize();

        this->train_classifier(data_set, MAX_ERROR, MAX_IT);

        unsigned int n = data_set->size();
        unsigned int correct = classifier->test(data_set);
        
        this->percentage = static_cast<double>(correct) / n;
    }

    void Tester::hold_out (double p, double MAX_ERROR,
                             unsigned int MAX_IT) {
        classifier->initialize();
        // TODO Check 'p' value
        unsigned int test_size = static_cast<unsigned int>(p * data_set->size());

        std::vector<unsigned int> train_indexes, test_indexes;
        unsigned int i;
        // TODO hacer con slice
        for (i = 0; i < test_size; i++) {
            test_indexes.push_back(i);
        }
        for (; i < data_set->size(); i++) {
            train_indexes.push_back(i);
        }

        DataSet* train_data_set = data_set->indexed_clone(train_indexes);
        DataSet* test_data_set = data_set->indexed_clone(test_indexes);

        this->train_classifier(train_data_set, MAX_ERROR, MAX_IT);

        unsigned int n = test_data_set->size();
        unsigned int correct = classifier->test(test_data_set);

        delete train_data_set;
        delete test_data_set;

        this->percentage = static_cast<double>(correct) / n;
    }

    void Tester::cross_validation (unsigned int K, double MAX_ERROR,
                                          unsigned int MAX_IT) {
        unsigned int N = data_set->size();
        unsigned int a, b;
        DataSet *training_set, *test_set;
        unsigned int correct;
        double accum_percentage = 0.0;

        a = 0;
        for (unsigned int i = 0; i < N % K; i++) {
            b = a + N/K + 1;
            
            data_set->slice(a, b, test_set, training_set);
            classifier->initialize();
            this->train_classifier(training_set, MAX_ERROR, MAX_IT);
            correct = classifier->test(test_set);
            accum_percentage += static_cast<double>(correct) / test_set->size();

            a = b;
            delete training_set;
            delete test_set;
        }
        for (unsigned int i = 0; i < K - N % K; i++) {
            b = a + N/K;

            data_set->slice(a, b, test_set, training_set);
            classifier->initialize();
            this->train_classifier(training_set, MAX_ERROR, MAX_IT);
            correct = classifier->test(test_set);
            accum_percentage += static_cast<double>(correct) / test_set->size();

            a = b;
            delete training_set;
            delete test_set;
        }

        this->percentage = accum_percentage / K;
    }

    void Tester::leave_one_out (double MAX_ERROR,
                                unsigned int MAX_IT) {
        this->cross_validation(data_set->size(), MAX_ERROR, MAX_IT);
    }

    double Tester::train_classifier (DataSet* ds, double MAX_ERROR, unsigned int MAX_IT) const {
        if (MAX_ERROR < 0.0) { // both defaults
            return classifier->train(ds);
        }
        else if (MAX_IT == UINT_MAX) { // only error default
            return classifier->train(ds, MAX_ERROR);
        }
        else {
            return classifier->train(ds, MAX_ERROR, MAX_IT);
        }

    }
}
