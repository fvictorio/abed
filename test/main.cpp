#include <iostream>
#include <vector>
#include "../include/dataset.hpp"
#include "../include/mlp.hpp"
#include "../include/tester.hpp"
using namespace std;
using namespace abed;

int main () {
    vector<unsigned int> hidden_layers;
    hidden_layers.push_back(1);
    MLP mlp(4, 3, hidden_layers, 0.05, 0.01, 0.25);

    StaticDataSet sds_train("test/data/iris.ssv");
    StaticDataSet sds_orig = sds_train;
    cout << mlp.train(sds_train, 0.05, 500) << endl;
    mlp.classify(sds_train);

    for (unsigned int n = 0; n < sds_train.get_size(); n++) {
        cout << sds_orig[n].get_label() << " " << sds_train[n].get_label() << endl;
    }

    return 0;
}

