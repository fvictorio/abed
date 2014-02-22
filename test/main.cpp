#include <iostream>
#include <vector>
#include "../include/dataset.hpp"
#include "../include/mlp.hpp"
#include "../include/tester.hpp"
#include "../include/perceptron.hpp"
using namespace std;
using namespace abed;

int main () {
    // Perceptron
    Perceptron classifier(2, 0.05, 0.25, 1);

    // Dataset
    StaticDataSet sds("xor.ssv");
    
    Tester tester(&classifier, &sds);
    tester.resubstitution(0.05, 200);
    cout << tester.get_percentage() << endl;


    return 0;
}

