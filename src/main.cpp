#include <iostream>
#include "../include/perceptron.hpp"
#include "../include/dataset.hpp"
using namespace std;
using namespace abed;

int main () {
    Perceptron p(2);
    StaticDataSet dataset("../test/xor.ssv", SSV);

    cout << p.train(dataset, 1, 0.1) << endl;

    //StaticDataSet sds("../test/or.ssv", SSV);
    StaticDataSet sds(cin, SSV);
    //for (unsigned int i = 0; i < sds.size(); i++) {
    //    cout << sds[i].get_label() << endl;
    //}

    p.classify(sds);

    for (unsigned int i = 0; i < sds.size(); i++) {
        cout << sds[i].get_label() << endl;
    }

    return 0;
}

