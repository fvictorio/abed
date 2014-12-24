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

    StaticDataSet sds("one_dimension.csv");

    unsigned int d = sds.get_dimension();
    unsigned int c = sds.get_no_classes();

    vector<unsigned int> hl;
    hl.push_back(3);
    hl.push_back(3);

    MLP mlp(d, c, hl);

    Tester tester(&mlp, &sds);

    double max_error = 0.05;
    
    tester.cross_validation(10, max_error);

    printf("%f\n", tester.get_percentage());

    return 0;
}
