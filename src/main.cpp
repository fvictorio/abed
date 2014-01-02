#include <iostream>
#include "../include/perceptron.hpp"
#include "../include/dataset.hpp"
using namespace std;
using namespace abed;

int main () {
    Perceptron p(2);
    StaticDataSet dataset("../test/or.ssv", SSV);

    p.train(dataset);

    StaticDataSet sds(cin, SSV);
    p.classify(sds);

    for (unsigned int i = 0; i < sds.size(); i++) {
        cout << sds[i].get_label() << endl;
    }

    return 0;
}

