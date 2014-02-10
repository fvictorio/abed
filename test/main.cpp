#include <iostream>
#include <vector>
#include "../include/dataset.hpp"
#include "../include/mlp.hpp"
#include "../include/tester.hpp"
using namespace std;
using namespace abed;

int main () {
    vector<unsigned int> hidden_layers;
    hidden_layers.push_back(2);
    hidden_layers.push_back(2);
    MLP mlp(2, 2, hidden_layers, 0.05, 0.01);

    StaticDataSet sds_train("xor_train.ssv");
    StaticDataSet sds_orig("xor.ssv");
    StaticDataSet sds("xor.ssv");
    cout << mlp.train(sds_train) << endl;
    mlp.classify(sds);

    for (unsigned int n = 0; n < sds.get_size(); n++) {
        cout << sds[n].get_label() << " " << sds_orig[n].get_label() << endl;
    }

    return 0;
}

