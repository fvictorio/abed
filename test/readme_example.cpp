#include <iostream>
#include "../include/mlp.hpp"
#include "../include/dataset.hpp"
using namespace abed;
using namespace std;


int main() {
    // Read the data
    StaticDataSet sds("iris.ssv");

    // Create the MLP
    vector<unsigned int> hidden_layers(2);
    hidden_layers[0] = 3;
    hidden_layers[1] = 3;

    unsigned int input_dimension = 4; // dimension of each data point
    unsigned int no_classes = 3; // number of possible classes
    MLP mlp(input_dimension, no_classes, hidden_layers);

    // Train the MLP
    mlp.train(sds);

    // Compute the percentage of success
    unsigned int no_correct = 0;
    for (unsigned int i = 0; i < sds.size(); i++) {
        unsigned int predicted_label = mlp.predict_label(sds[i]);
        if (predicted_label == sds[i].get_label()) {
            no_correct++;
        }
    }
    cout << static_cast<double>(no_correct) / sds.size() << endl;
}
