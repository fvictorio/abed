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
        SVM (unsigned int d, unsigned int c, svm_parameter);

        SVM (const SVM&);
        SVM& operator= (SVM svm);
        ~SVM ();
        friend void swap(SVM& first, SVM& second);

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
        void initialize_pointers ();
        void static copy_svm_parameter (const svm_parameter* const from_param, svm_parameter*& to_param);
        void static copy_svm_model (const svm_model* const from_model, svm_model*& to_model);
        void static copy_svm_problem (const svm_problem* const from_prob, svm_problem*& to_prob);
        void static free_svm_parameter (svm_parameter* const param);
        void static free_svm_model (svm_model* const model);
        void static free_svm_problem (svm_problem* const prob);

        unsigned int dimension;
        unsigned int no_classes;
        svm_parameter* param;
        svm_model* model;
        svm_problem* prob;
    };

}

#endif /* ABED_SVM_HPP */
