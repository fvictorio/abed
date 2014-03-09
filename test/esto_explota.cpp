#include <iostream>
#include <vector>
#include "../include/dataset.hpp"
#include "../include/mlp.hpp"
#include "../include/tester.hpp"
#include "../include/perceptron.hpp"
#include "../include/bagging.hpp"
using namespace std;
using namespace abed;

int main () {
    srand(time(NULL));
    StaticDataSet sds("yeast.ssv");

    vector<unsigned int> hl;

    //hl.push_back(8);
    //hl.push_back(8);
    //MLP mlp(8, 10, hl);

    //Tester mlp_tester(&mlp, &sds);
    //mlp_tester.resubstitution();
    //cout << "MLP: " << mlp_tester.get_percentage() << endl;

    Bagging bagging(3);
    hl.clear();
    hl.push_back(4);
    bagging.add_classifier(new MLP(8, 10, hl));
    bagging.add_classifier(new MLP(8, 10, hl));
    bagging.add_classifier(new MLP(8, 10, hl));
    bagging.add_classifier(new MLP(8, 10, hl));
    bagging.add_classifier(new MLP(8, 10, hl));
    bagging.add_classifier(new MLP(8, 10, hl));

    Tester bagging_tester(&bagging, &sds);
    bagging_tester.resubstitution();
    cout << "Bagging: " << bagging_tester.get_percentage() << endl;

    return 0;
}

