#ifndef ABED_ENSEMBLE_HPP
#define ABED_ENSEMBLE_HPP

#include "classifier.hpp"

namespace abed {

    class EnsembleClassifier : public Classifier {
    public:
        using Classifier::train; // Effective C++ Item 33
        using Classifier::classify; // Effective C++ Item 33
        using Classifier::predict_label; // Effective C++ Item 33

        virtual ~EnsembleClassifier () {
            for (unsigned int i = 0; i < classifiers.size(); i++) {
                delete classifiers[i];
            }
        }
        virtual void add_classifier (Classifier* classifier) {
            classifiers.push_back(classifier);
        }
        virtual void remove_classifier (unsigned int i) {
            delete classifiers[i];
            classifiers.erase(classifiers.begin() + i);
        }
    protected:
        std::vector<Classifier*> classifiers;
    };

}

#endif /* ABED_ENSEMBLE_HPP */
