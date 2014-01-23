#include <iostream>
#include "../include/dataset.hpp"
#include "../include/perceptron.hpp"
#include "../include/tester.hpp"
using namespace std;
using namespace abed;

int main () {
    Perceptron p(2);
    StaticDataSet dataset("/home/blamaeda/proyecto/abed/test/data/or.ssv", SSV);

    cout << dataset.get_size() << endl;

    Tester tester(&p, &dataset);
    tester.resubstitution();

    cout << tester.get_percentage() << endl;

    return 0;
}

