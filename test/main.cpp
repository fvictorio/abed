#include <iostream>
#include "../include/dataset.hpp"
#include "../include/perceptron.hpp"
#include "../include/tester.hpp"
using namespace std;
using namespace abed;

int main () {
    Perceptron p(2);
    StaticDataSet dataset("../test/xor.ssv", SSV);

    Tester tester(&p, &dataset);

    return 0;
}

