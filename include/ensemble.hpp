#ifndef ABED_ENSEMBLE_HPP
#define ABED_ENSEMBLE_HPP

#include <iostream>
#include "classifier.hpp"

namespace abed {
    
    //! Abstract class for ensembles of classifiers

    class EnsembleClassifier : public Classifier {
    public:
        using Classifier::train; // Effective C++ Item 33
        using Classifier::classify; // Effective C++ Item 33
        using Classifier::predict_label; // Effective C++ Item 33

        EnsembleClassifier () {}
        EnsembleClassifier (const EnsembleClassifier& ec) {            
            for (unsigned int i = 0; i < ec.classifiers.size(); i++) {
                this->classifiers.push_back(ec.classifiers[i]->clone());
            }
        }
        EnsembleClassifier& operator= (const EnsembleClassifier& ec) {
            for (unsigned int i = 0; i < this->classifiers.size(); i++) {
                delete this->classifiers[i];
            }
            for (unsigned int i = 0; i < ec.classifiers.size(); i++) {
                classifiers.push_back(ec.classifiers[i]->clone());
            }
            return *this;
        }

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
