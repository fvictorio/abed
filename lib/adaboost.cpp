#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include "../include/adaboost.hpp"
#include "../include/dataset.hpp"
#include "../include/utilities.hpp"

namespace abed {
    using std::vector;

    void AdaBoost::initialize (unsigned int seed) {
        if (seed != UINT_MAX) {
            srand(seed);
        }
        
        for (unsigned int i = 0; i < classifiers.size(); i++) {
            classifiers[i]->initialize();
        }
    }

    // TODO Future me: please review this code carefully... I don't trust it
    double AdaBoost::train (const StaticDataSet& sds, double MAX_ERROR, unsigned int MAX_IT) {
        // TODO This should be in a upper class, maybe
        if (sds.get_dimension() != this->dimension) {
            throw std::domain_error("Dimension of Bagging and dataset are not the same");
        }
        if (sds.get_no_classes() != this->no_classes) {
            throw std::domain_error("Number of classes of Bagging and dataset are not the same");
        }
        // TODO Should I initialize all the classifiers?

        const unsigned int N = sds.size();
        const unsigned int B = classifiers.size();

        normalized_error = vector<double>(B);

        double mean_train_error = 0.0;

        vector<double> distribution(N, 1.0 / N);

        for (unsigned int b = 0; b < B; b++) {
            DataSet* bootstrapped = sds.bootstrap(distribution, N);

            mean_train_error = classifiers[b]->train(bootstrapped, MAX_ERROR, MAX_IT);

            vector<unsigned int> predicted_labels(N);
            double classifier_error = 0.0;
            for (unsigned int i = 0; i < N; i++) {
                const DataPoint* data_point = bootstrapped->get_data_point(i);
                predicted_labels[i] = classifiers[b]->predict_label(data_point);
                
                if (predicted_labels[i] != data_point->get_label()) {
                    classifier_error += distribution[i];
                } 
            }

            normalized_error[b] = classifier_error / (1.0 - classifier_error);

            for (unsigned int i = 0; i < N; i++) {
                const DataPoint* data_point = bootstrapped->get_data_point(i);
                if (predicted_labels[i] == data_point->get_label()) {
                    distribution[i] *= normalized_error[b];
                }
            }

            normalize_distribution(distribution);

            delete bootstrapped;
        }
        
        mean_train_error /= classifiers.size();
        return mean_train_error;
    }

    unsigned int AdaBoost::predict_label (const StaticDataPoint& sdp) const {
        vector<double> votes(no_classes, 0.0);

        for (unsigned int i = 0; i < classifiers.size(); i++) {
            unsigned int vote = classifiers[i]->predict_label(sdp);
            assert(vote >= 0 && vote < no_classes);
            votes[vote] += 1.0 / std::log(normalized_error[i]);
        }
        
        vector<double>::iterator voted = std::max_element(votes.begin(), votes.end());
        return voted - votes.begin();
    }
} // namespace abed
