#include <iostream>
#include <vector>
#include <string>
#include "../include/adaboost.hpp"
#include "../include/bagging.hpp"
#include "../include/dataset.hpp"
#include "../include/mlp.hpp"
#include "../include/perceptron.hpp"
#include "../include/svm.hpp"
#include "../include/tester.hpp"
using namespace std;
using namespace abed;

int main (int argc, char** argv) {
    srand(time(NULL));

    string classifier_type = "MLP";
    string dataset = "iris.ssv";
    string testing_method = "HOLD_OUT";

    if (argc >= 2) {
        classifier_type = argv[1];
    }
    if (argc >= 3) {
        dataset = argv[2];
    }
    if (argc >= 4) {
        testing_method = argv[3];
    }

    StaticDataSet sds(dataset.c_str());
    Classifier *classifier;

    unsigned int d = sds.get_dimension();
    unsigned int c = sds.get_no_classes();

    if (classifier_type == "MLP") {
        vector<unsigned int> hl;
        hl.push_back(d);
        hl.push_back(d);

        classifier = new MLP(d, c, hl);
    }
    else if (classifier_type == "SVM") {
        classifier = new SVM(d, c);
    }
    else if (classifier_type == "ADABOOST") {
        vector<unsigned int> hl;
        hl.push_back(1 + d / 2);

        EnsembleClassifier *adaboost = new AdaBoost(d, c);
        for (unsigned int i = 0; i < 20; i++) {
            adaboost->add_classifier(new MLP(d, c, hl));
        }

        classifier = static_cast<Classifier*>(adaboost);
    }
    else if (classifier_type == "BAGGING") {
        vector<unsigned int> hl;
        hl.push_back(1 + d/2);

        EnsembleClassifier *bagging = new Bagging(d, c);
        for (unsigned int i = 0; i < 20; i++) {
            bagging->add_classifier(new MLP(d, c, hl));
        }

        classifier = static_cast<Classifier*>(bagging);
    }
    else {
        printf("Unknown classifier\n");
        return 1;
    }

    Tester tester(classifier, &sds);

    double max_error = 0.25;
    
    if (testing_method == "HOLD_OUT") {
        tester.hold_out(0.1, max_error);
    }
    else if (testing_method == "CROSS_VALIDATION") {
        tester.cross_validation(10, max_error);
    }

    printf("%f\n", tester.get_percentage());

    return 0;
}
