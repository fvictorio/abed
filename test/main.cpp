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
    double MAX_ERROR = 0.05;
    unsigned int MAX_IT = 1000;
    StaticDataSet sds("ecoli.ssv");
    unsigned int dimension = sds.get_dimension();
    unsigned int no_classes = sds.get_no_classes();

    SVM* svm = new SVM(dimension, no_classes);

    Tester tester(svm, &sds);
    tester.cross_validation(10, MAX_ERROR, MAX_IT);
    cout << tester.get_percentage() << endl;

    delete svm;

    return 0;
}

