#include <iostream>
#include <vector>
#include "../include/dataset.hpp"
#include "../include/mlp.hpp"
#include "../include/tester.hpp"
#include "../include/perceptron.hpp"
#include "../include/bagging.hpp"
#include "../include/svm.hpp"
using namespace std;
using namespace abed;


void test_mlp () {
    const double MLP_IRIS = 0.93;
    const double MLP_ECOLI = 0.78;
    const double MLP_YEAST = 0.49;

    const double MAX_ERROR = 0.05;
    const unsigned int MAX_IT = 100; //XXX
    const unsigned int NO_FOLDS = 3;

    Classifier* classifier;
    // IRIS
    {
        StaticDataSet sds("iris.ssv");
        unsigned int dimension = sds.get_dimension();
        unsigned int no_classes = sds.get_no_classes();

        vector<unsigned int> hl;
        hl.push_back(dimension);
        hl.push_back(dimension);
        classifier = new MLP(dimension, no_classes, hl);
        Tester tester(classifier, &sds);

        tester.cross_validation(NO_FOLDS, MAX_ERROR, MAX_IT);
        cout << "MLP - IRIS" << endl;
        cout << "Expected value: ~" << MLP_IRIS << endl;
        cout << "Obtained value: " << tester.get_percentage() << endl;
        cout << "---------------" << endl;

        delete classifier;
    }

    // ECOLI
    {
        StaticDataSet sds("ecoli.ssv");
        unsigned int dimension = sds.get_dimension();
        unsigned int no_classes = sds.get_no_classes();

        vector<unsigned int> hl;
        hl.push_back(dimension);
        hl.push_back(dimension);
        classifier = new MLP(dimension, no_classes, hl);
        Tester tester(classifier, &sds);

        tester.cross_validation(NO_FOLDS, MAX_ERROR, MAX_IT);
        cout << "MLP - ECOLI" << endl;
        cout << "Expected value: ~" << MLP_ECOLI << endl;
        cout << "Obtained value: " << tester.get_percentage() << endl;
        cout << "---------------" << endl;

        delete classifier;
    }

    // YEAST
    {
        StaticDataSet sds("yeast.ssv");
        unsigned int dimension = sds.get_dimension();
        unsigned int no_classes = sds.get_no_classes();

        vector<unsigned int> hl;
        hl.push_back(dimension);
        hl.push_back(dimension);
        classifier = new MLP(dimension, no_classes, hl);
        Tester tester(classifier, &sds);

        tester.cross_validation(NO_FOLDS, MAX_ERROR, MAX_IT);
        cout << "MLP - YEAST" << endl;
        cout << "Expected value: ~" << MLP_YEAST << endl;
        cout << "Obtained value: " << tester.get_percentage() << endl;
        cout << "---------------" << endl;

        delete classifier;
    }
}

void test_svm () {
    const double SVM_IRIS = 0.96;
    const double SVM_ECOLI = 0.74;
    const double SVM_YEAST = 0.35;

    const double MAX_ERROR = 0.05;
    const unsigned int MAX_IT = 1000;
    const unsigned int NO_FOLDS = 3;

    Classifier* classifier;

    // IRIS
    {
        StaticDataSet sds("iris.ssv");
        unsigned int dimension = sds.get_dimension();
        unsigned int no_classes = sds.get_no_classes();

        classifier = new SVM(dimension, no_classes);
        Tester tester(classifier, &sds);

        tester.cross_validation(NO_FOLDS, MAX_ERROR, MAX_IT);
        cout << "SVM - IRIS" << endl;
        cout << "Expected value: ~" << SVM_IRIS << endl;
        cout << "Obtained value: " << tester.get_percentage() << endl;
        cout << "---------------" << endl;

        delete classifier;
    }

    // ECOLI
    {
        StaticDataSet sds("ecoli.ssv");
        unsigned int dimension = sds.get_dimension();
        unsigned int no_classes = sds.get_no_classes();

        classifier = new SVM(dimension, no_classes);
        Tester tester(classifier, &sds);

        tester.cross_validation(NO_FOLDS, MAX_ERROR, MAX_IT);
        cout << "SVM - ECOLI" << endl;
        cout << "Expected value: ~" << SVM_ECOLI << endl;
        cout << "Obtained value: " << tester.get_percentage() << endl;
        cout << "---------------" << endl;

        delete classifier;
    }

    // YEAST
    {
        StaticDataSet sds("yeast.ssv");
        unsigned int dimension = sds.get_dimension();
        unsigned int no_classes = sds.get_no_classes();

        classifier = new SVM(dimension, no_classes);
        Tester tester(classifier, &sds);

        tester.cross_validation(NO_FOLDS, MAX_ERROR, MAX_IT);
        cout << "SVM - YEAST" << endl;
        cout << "Expected value: ~" << SVM_YEAST << endl;
        cout << "Obtained value: " << tester.get_percentage() << endl;
        cout << "---------------" << endl;

        delete classifier;
    }
}

void test_bagging_mlp () {
    const double BAG_MLP_IRIS = 0.94;
    const double BAG_MLP_ECOLI = 0.85;
    const double BAG_MLP_YEAST = 0.54;

    const double MAX_ERROR = 0.05;
    const unsigned int MAX_IT = 1000;
    const unsigned int NO_FOLDS = 3;

    // IRIS
    {
        StaticDataSet sds("iris.ssv");
        unsigned int dimension = sds.get_dimension();
        unsigned int no_classes = sds.get_no_classes();

        Bagging bagging(dimension, no_classes);
        vector<unsigned int> hl;
        hl.push_back(dimension);
        bagging.add_classifier(new MLP(dimension, no_classes, hl));
        bagging.add_classifier(new MLP(dimension, no_classes, hl));
        bagging.add_classifier(new MLP(dimension, no_classes, hl));
        bagging.add_classifier(new MLP(dimension, no_classes, hl));
        bagging.add_classifier(new MLP(dimension, no_classes, hl));
        Tester tester(&bagging, &sds);

        tester.cross_validation(NO_FOLDS, MAX_ERROR, MAX_IT);
        cout << "Bagging-MLP - IRIS" << endl;
        cout << "Expected value: ~" << BAG_MLP_IRIS << endl;
        cout << "Obtained value: " << tester.get_percentage() << endl;
        cout << "---------------" << endl;
    }

    // ECOLI
    {
        StaticDataSet sds("ecoli.ssv");
        unsigned int dimension = sds.get_dimension();
        unsigned int no_classes = sds.get_no_classes();

        Bagging bagging(dimension, no_classes);
        vector<unsigned int> hl;
        hl.push_back(dimension);
        bagging.add_classifier(new MLP(dimension, no_classes, hl));
        bagging.add_classifier(new MLP(dimension, no_classes, hl));
        bagging.add_classifier(new MLP(dimension, no_classes, hl));
        bagging.add_classifier(new MLP(dimension, no_classes, hl));
        bagging.add_classifier(new MLP(dimension, no_classes, hl));
        Tester tester(&bagging, &sds);

        tester.cross_validation(NO_FOLDS, MAX_ERROR, MAX_IT);
        cout << "Bagging-MLP - ECOLI" << endl;
        cout << "Expected value: ~" << BAG_MLP_ECOLI << endl;
        cout << "Obtained value: " << tester.get_percentage() << endl;
        cout << "---------------" << endl;
    }

    // YEAST
    {
        StaticDataSet sds("yeast.ssv");
        unsigned int dimension = sds.get_dimension();
        unsigned int no_classes = sds.get_no_classes();

        Bagging bagging(dimension, no_classes);
        vector<unsigned int> hl;
        hl.push_back(dimension);
        bagging.add_classifier(new MLP(dimension, no_classes, hl));
        bagging.add_classifier(new MLP(dimension, no_classes, hl));
        bagging.add_classifier(new MLP(dimension, no_classes, hl));
        bagging.add_classifier(new MLP(dimension, no_classes, hl));
        bagging.add_classifier(new MLP(dimension, no_classes, hl));
        Tester tester(&bagging, &sds);

        tester.cross_validation(NO_FOLDS, MAX_ERROR, MAX_IT);
        cout << "Bagging-MLP - YEAST" << endl;
        cout << "Expected value: ~" << BAG_MLP_YEAST << endl;
        cout << "Obtained value: " << tester.get_percentage() << endl;
        cout << "---------------" << endl;
    }
}

// All tests
int main () {
    srand(time(NULL));
    //test_mlp();
    //test_svm();
    test_bagging_mlp();

    return 0;
}

