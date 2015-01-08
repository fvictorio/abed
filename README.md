abed
====

Introduction
------------

abed is a statistical classification library, written in C++, for performing
supervised learning. It has an object-oriented design, no external
dependencies and it's free software under the BSD 3-Clause License.

abed has three kinds of classifiers: 

* **Static classifiers**, for working with static (non-sequential) data.
* **Dynamic classifiers**, for working with sequential data.
* **Meta-classifiers**, that allow composing weak classifiers to make a strong
classifier.

Examples
--------

The following example shows how to read a SSV file containing the famous [iris
dataset](http://en.wikipedia.org/wiki/Iris_flower_data_set) and train a
multilayer perceptron (MLP). The MLP has two layers, each one with three
neurons.

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

This example, of course, overestimates the performance of the MLP, by testing
and training it with the same data. abed provides a `Tester` class for doing
hold-out or cross-validation testing.
