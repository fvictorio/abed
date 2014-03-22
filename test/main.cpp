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

    const double MAX_ERROR = 0.00;
    const unsigned int MAX_IT = 1000;

    StaticDataSet sds("or.ssv");

    vector<unsigned int> hl;
    hl.push_back(2);
    hl.push_back(2);
    MLP mlp(2, 2, hl, 0.05, 0.01);

    Tester tester(&mlp, &sds);

    //tester.cross_validation(10, MAX_ERROR, MAX_IT);
    tester.hold_out(0.1, MAX_ERROR, MAX_IT);
    cout << tester.get_percentage() << endl;

    return 0;
}

