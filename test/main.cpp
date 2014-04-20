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
    StaticDataSet sds("iris.ssv");
    unsigned int d = sds.get_dimension();
    unsigned int c = sds.get_no_classes();

    SVM svm(d, c);
    SVM svm2(svm);
    SVM svm3(svm2);
    svm3.train(sds);

    return 0;
}

/*
int main () {
    //srand(time(NULL));
    srand(42); // 0.395

    const double MAX_ERROR = 0.05;
    const unsigned int MAX_IT = 100;
    const unsigned int NO_FOLDS = 10;
    StaticDataSet sds("iris.ssv");
    const unsigned int dimension = sds.get_dimension();
    const unsigned int no_classes = sds.get_no_classes();

    svm_parameter param;
    param.svm_type = C_SVC;
    param.kernel_type = LINEAR;
    param.degree = 3;
    param.gamma = 1.0 / dimension;
    param.coef0 = 0.0;
    param.cache_size = 100;
    param.eps = 0.001;
    param.C = 1.0;
    param.nr_weight = 0;
    param.nu = 0.5;
    param.p = 0.1;
    param.shrinking = 1;
    param.probability = 0;
    SVM svm(dimension, no_classes, param);
    //SVM svm2 = svm;

    Tester tester(&svm, &sds);
    tester.hold_out(0.2, MAX_ERROR, MAX_IT);

    cout << tester.get_percentage() << endl;

    return 0;
}
*/
