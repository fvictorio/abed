#include <iostream>
#include "../include/dataset.hpp"
#include "../include/perceptron.hpp"
using namespace std;
using namespace abed;

int main () {
    Perceptron p(2);
    StaticDataSet dataset("../test/xor.ssv", SSV);

    return 0;
}

