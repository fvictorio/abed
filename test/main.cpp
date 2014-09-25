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
    string dataset = "iris.ssv";
    string classifier_type = "MLP";

    if (argc >= 2) {
        classifier_type = argv[1];
    }
    if (argc >= 3) {
        dataset = argv[2];
    }

    StaticDataSet sds(dataset.c_str());
    Classifier *classifier;

    if (classifier_type == "MLP") {
        unsigned int d = sds.get_dimension();
        unsigned int c = sds.get_no_classes();

        vector<unsigned int> hl;
        hl.push_back(d);
        hl.push_back(d);
        classifier = new MLP(d, c, hl);
    }
    else if (classifier_type == "ADABOOST") {
        unsigned int d = sds.get_dimension();
        unsigned int c = sds.get_no_classes();

        vector<unsigned int> hl;
        hl.push_back(d);
        EnsembleClassifier *adaboost = new AdaBoost(d, c);
        adaboost->add_classifier(new MLP(d, c, hl));
        adaboost->add_classifier(new MLP(d, c, hl));
        adaboost->add_classifier(new MLP(d, c, hl));
        adaboost->add_classifier(new MLP(d, c, hl));
        adaboost->add_classifier(new MLP(d, c, hl));
        classifier = static_cast<Classifier*>(adaboost);
    }
    else {
        printf("Unknown classifier\n");
        return 1;
    }

    Tester tester(classifier, &sds);
    
    tester.hold_out(0.1);

    printf("%f\n", tester.get_percentage());

    return 0;
}
