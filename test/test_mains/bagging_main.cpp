#include <iostream>
#include <vector>
#include "../include/dataset.hpp"
#include "../include/mlp.hpp"
#include "../include/tester.hpp"
#include "../include/perceptron.hpp"
#include "../include/bagging.hpp"
using namespace std;
using namespace abed;

int main () {
    srand(time(NULL));
    unsigned int dimension = 8;
    unsigned int no_classes = 10;
    double MAX_ERROR = 0.05;
    unsigned int MAX_IT = 1000;
    StaticDataSet sds("yeast.ssv");

    vector<unsigned int> hl;

    hl.push_back(dimension);
    hl.push_back(dimension);
    MLP mlp(dimension, no_classes, hl);

    Tester mlp_tester(&mlp, &sds);
    //mlp_tester.cross_validation(10, MAX_ERROR, MAX_IT);
    mlp_tester.hold_out(0.1, MAX_ERROR, MAX_IT);
    cout << "MLP: " << mlp_tester.get_percentage() << endl;

    Bagging bagging(dimension, no_classes);
    hl.clear();
    hl.push_back(dimension);
    bagging.add_classifier(new MLP(dimension, no_classes, hl));
    bagging.add_classifier(new MLP(dimension, no_classes, hl));
    bagging.add_classifier(new MLP(dimension, no_classes, hl));
    bagging.add_classifier(new MLP(dimension, no_classes, hl));
    bagging.add_classifier(new MLP(dimension, no_classes, hl));
    bagging.add_classifier(new MLP(dimension, no_classes, hl));
    bagging.add_classifier(new MLP(dimension, no_classes, hl));
    bagging.add_classifier(new MLP(dimension, no_classes, hl));

    Tester bagging_tester(&bagging, &sds);
    //bagging_tester.cross_validation(10, MAX_ERROR, MAX_IT);
    bagging_tester.hold_out(0.1, MAX_ERROR, MAX_IT);
    cout << "Bagging: " << bagging_tester.get_percentage() << endl;

    return 0;
}

