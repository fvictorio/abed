#include <iostream>
#include <vector>
#include "../include/dataset.hpp"
#include "../include/mlp.hpp"
#include "../include/tester.hpp"
#include "../include/perceptron.hpp"
#include "../include/bagging.hpp"
#include "../include/svm.hpp"
using namespace std;
using namespace abed;

int main () {
    srand(time(NULL));

    const double MAX_ERROR = 0.05;
    const unsigned int MAX_IT = 1000;
    const unsigned int NO_FOLDS = 10;
    StaticDataSet sds("yeast.ssv");
    const unsigned int dimension = sds.get_dimension();
    const unsigned int no_classes = sds.get_no_classes();

    //SVM classifier(dimension, no_classes);

    Tester tester(&classifier, &sds);
    tester.cross_validation(NO_FOLDS, MAX_ERROR, MAX_IT);

    cout << tester.get_percentage() << endl;

    return 0;
}

