#ifndef ABED_SVM_HPP
#define ABED_SVM_HPP

#include "classifier.hpp"
#include "libsvm.hpp"

namespace abed {

    //! \brief Support Vector Machine implementation

    class SVM : public StaticClassifier {
    public:
        // Constructor por defecto que asigna parametros estandar
        SVM (unsigned int d, unsigned int c);
        // Constructor con parametros mas definidos
        SVM (unsigned int d, unsigned int c, svm_parameter);
        SVM (const SVM& svm);
        SVM& operator= (SVM svm);
        ~SVM ();
        friend void swap (SVM&, SVM&);

        virtual void initialize (unsigned int seed = UINT_MAX);
        virtual unsigned int predict_label (const StaticDataPoint&) const;
        virtual double train (const StaticDataSet&, 
                              double MAX_ERROR = DEFAULT_MAX_ERROR, 
                              unsigned int MAX_IT = DEFAULT_MAX_IT);
        virtual Classifier* clone () const {
            return new SVM(*this);
        }

        static void SDS_to_svm_problem (const StaticDataSet&, svm_problem&);
        static void SDP_to_svm_node (const StaticDataPoint&, svm_node*&, unsigned int);
    private:
        static void copy_svm_parameter (const svm_parameter& from_param, svm_parameter& to_param);
        static void copy_svm_problem (unsigned int d, const svm_problem& from_prob, svm_problem& to_prob);
        static void copy_svm_model (svm_model* const from_model, svm_model*& to_model);
        static void free_svm_problem (svm_problem&);

        unsigned int dimension;
        unsigned int no_classes;
        svm_parameter param;
        svm_model* model;
        svm_problem prob;
        bool already_trained;
    };

}

#endif /* ABED_SVM_HPP */
