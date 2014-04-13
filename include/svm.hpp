#ifndef ABED_SVM_HPP
#define ABED_SVM_HPP

#include "classifier.hpp"
#include "libsvm.hpp"

namespace abed {

    class SVM : public StaticClassifier {
    public:
        // Constructor por defecto que asigna parametros estandar
        SVM (unsigned int d, unsigned int c);
        // Constructor con parametros mas definidos
        SVM (unsigned int d, unsigned int c, const svm_parameter&);

        virtual void initialize (unsigned int seed = UINT_MAX);
        virtual unsigned int predict_label (const StaticDataPoint&) const;
        virtual double train (const StaticDataSet&, 
                              double MAX_ERROR = DEFAULT_MAX_ERROR, 
                              unsigned int MAX_IT = DEFAULT_MAX_IT);
        virtual Classifier* clone () const {
            return new SVM(*this);
        }

        static void SDS_to_SVM_problem (const StaticDataSet&, svm_problem*&);
        static void SDP_to_SVM_node (const StaticDataPoint&, svm_node*&, unsigned int);
    private:
        unsigned int dimension;
        unsigned int no_classes;
    public: //XXX
        svm_parameter* param;
        svm_model* model;
        svm_problem* prob;
    };

}

#endif /* ABED_SVM_HPP */
