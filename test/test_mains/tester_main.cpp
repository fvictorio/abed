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
    vector<unsigned int> hidden_layers;
    hidden_layers.push_back(8);
    hidden_layers.push_back(8);
    MLP classifier(8, 10, hidden_layers, 0.05, 0.01);
    double MAX_ERROR = 0.05;
    unsigned int MAX_IT = 500;
    StaticDataSet sds("yeast.ssv");
    

    // Resubstitution
    Tester re(&classifier, &sds);
    re.resubstitution(MAX_ERROR, MAX_IT);
    cout << "Resubstitution: " << re.get_percentage() << endl;

    // Hold out
    Tester ho(&classifier, &sds);
    ho.hold_out(0.1, MAX_ERROR, MAX_IT);
    cout << "Hold-out: " << ho.get_percentage() << endl;

    // Cross validation
    int k;

    k = 3;
    Tester cv1(&classifier, &sds);
    cv1.cross_validation(k, MAX_ERROR, MAX_IT);
    cout << "Cross-validation (" << k << " folds): " << cv1.get_percentage() << endl;

    k = 10;
    Tester cv2(&classifier, &sds);
    cv2.cross_validation(k, MAX_ERROR, MAX_IT);
    cout << "Cross-validation (" << k << " folds): " << cv2.get_percentage() << endl;

    k = 30;
    Tester cv3(&classifier, &sds);
    cv3.cross_validation(k, MAX_ERROR, MAX_IT);
    cout << "Cross-validation (" << k << " folds): " << cv3.get_percentage() << endl;

    k = 60;
    Tester cv4(&classifier, &sds);
    cv4.cross_validation(k, MAX_ERROR, MAX_IT);
    cout << "Cross-validation (" << k << " folds): " << cv4.get_percentage() << endl;

    // Leave one out
    Tester lou(&classifier, &sds);
    lou.leave_one_out(MAX_ERROR, MAX_IT);
    cout << "Leave one out: " << lou.get_percentage() << endl;

    return 0;
}

