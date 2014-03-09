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
    StaticDataSet sds("iris.ssv");
    Bagging bagging(3);

    return 0;
}

