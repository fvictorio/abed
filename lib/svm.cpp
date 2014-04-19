#include <cassert>
#include <iostream>
#include "../include/svm.hpp"
#include "../include/libsvm.hpp"
#include "../include/utilities.hpp"

namespace abed {
    SVM::SVM (unsigned int d, unsigned int c) : dimension(d), no_classes(c) {
        initialize_pointers();

        param = new svm_parameter();
        param->svm_type = 0;
        param->kernel_type = 2;
        param->degree = 3;
        param->gamma = 1.0 / dimension;
        param->coef0 = 0.0;

        // used for training only
        param->cache_size = 100;
        param->eps = 0.001;
        param->C = 1.0;
        param->nr_weight = 0;
        param->nu = 0.5;
        param->p = 0.1;
        param->shrinking = 1;
        param->probability = 0;
    }

    SVM::SVM (unsigned int d, unsigned int c, svm_parameter p) 
           : dimension(d), no_classes(c) {
        initialize_pointers();

        copy_svm_parameter(&p, param);
    }

    SVM::SVM (const SVM& svm) {
        initialize_pointers();

        dimension = svm.dimension;
        no_classes = svm.no_classes;

        copy_svm_parameter(svm.param, param);
        copy_svm_model(svm.model, model);
        copy_svm_problem(svm.prob, prob);
    }

    void SVM::initialize_pointers () {
        param = NULL;
        model = NULL;
        prob = NULL;
    }

    // copy-and-swap idiom
    SVM& SVM::operator= (SVM svm) {
        swap(*this, svm);

        return *this;
    }

    SVM::~SVM () {
        free_svm_parameter(param);
        delete param;
        param = NULL;

        //free_svm_model(model);
        svm_free_model_content(model);
        delete model;
        model = NULL;

        free_svm_problem(prob);
        delete prob;
        prob = NULL;
    }

    void swap(SVM& first, SVM& second) {
        using std::swap;
        swap(first.dimension, second.dimension);
        swap(first.no_classes, second.no_classes);
        swap(first.param, second.param);
        swap(first.model, second.model);
        swap(first.prob, second.prob);
    }

    void SVM::initialize (unsigned int seed) {
        //TODO
    }

    double SVM::train (const StaticDataSet& sds, double MAX_ERROR, unsigned int MAX_IT) {
        free_svm_problem(prob);
        delete prob;
        prob = NULL;

        //free_svm_model(model);
        if (model != NULL) {
            svm_free_model_content(model);
            delete model;
            model = NULL;
        }

        SVM::SDS_to_SVM_problem(sds, prob);

        const char* msg = svm_check_parameter(prob, param);
        if (msg) {
            std::cout << msg << std::endl;
        }
        else {
            model = svm_train(prob, param);
        }
        return 0.0; //TODO
    }

    unsigned int SVM::predict_label (const StaticDataPoint& sdp) const {
        svm_node* x = NULL;
        SVM::SDP_to_SVM_node(sdp, x, dimension);
        double predicted_label = svm_predict(model, x);
        delete[] x;
        return round(predicted_label);
    }

    void SVM::SDS_to_SVM_problem (const StaticDataSet& sds, svm_problem*& prob) {
        prob = new svm_problem();
        prob->l = sds.size();
        prob->y = new double[prob->l];
        prob->x = new svm_node*[prob->l];
        for (int i = 0; i < prob->l; i++) {
            SVM::SDP_to_SVM_node(sds[i], prob->x[i], sds.get_dimension());
            prob->y[i] = sds[i].get_label();
        }
    }

    void SVM::SDP_to_SVM_node (const StaticDataPoint& sdp, svm_node*& node, unsigned int d) {
        node = new svm_node[d+1];
        unsigned int i;
        for (i = 0; i < d; i++) {
            node[i].index = i+1;
            node[i].value = sdp[i];
        }
        node[i].index = -1;
    }

    void SVM::copy_svm_parameter (const svm_parameter* const from_param, svm_parameter*& to_param) {
        if (from_param == NULL) {
            to_param = NULL;
            return;
        }

        free_svm_parameter(to_param);
        to_param = new svm_parameter();
        *to_param = *from_param;

        int nr_weight = from_param->nr_weight;

        to_param->weight_label = new int[nr_weight];
        to_param->weight = new double[nr_weight];

        for (int i = 0; i < nr_weight; i++) {
            to_param->weight_label[i] = from_param->weight_label[i];
            to_param->weight[i] = from_param->weight[i];
        }
    }

    void SVM::copy_svm_model (const svm_model* const from_model, svm_model*& to_model) {
        if (from_model == NULL) {
            to_model = NULL;
            return;
        }

        //free_svm_model(to_model);
        if (to_model != NULL) {
            svm_free_model_content(to_model);
        }
        to_model = new svm_model();

        // Start with a shallow copy
        *to_model = *from_model;

        // Deep copying begins here

        // Copy svm_paremeter. The pointers are necessary for calling
        // abed::SVM::copy_svm_parameter
        const svm_parameter* const from_model_param = &(from_model->param);
        svm_parameter* to_model_param = &(to_model->param);
        copy_svm_parameter(from_model_param, to_model_param);

        // Deep copy model->SV and model->sv_coef
        int no_classes = from_model->nr_class;
        int no_svs = from_model->l;
        
        to_model->SV = new svm_node*[no_classes];
        for (int i = 0; i < no_classes; i++) {
            to_model->SV[i] = new svm_node[no_classes-1];
            for (int j = 0; j < no_classes-1; j++) {
                to_model->SV[i][j] = from_model->SV[i][j];
            }
        }

        to_model->sv_coef = new double*[no_classes-1];
        for (int i = 0; i < no_classes-1; i++) {
            to_model->sv_coef[i] = new double[no_svs];
            for (int j = 0; j < no_svs; j++) {
                to_model->sv_coef[i][j] = from_model->sv_coef[i][j]; // XXX
            }
        }
        
        int no_binary_problems = (no_classes*(no_classes-1))/2;

        // Deep copy model->rho
        to_model->rho   = new double[no_binary_problems];
        for (int i = 0; i < no_binary_problems; i++) {
            to_model->rho[i]   = from_model->rho[i];
        }

        // Deep copy model->probA and model->probB
        if (to_model->param.probability == 1) {
            to_model->probA = new double[no_binary_problems];
            to_model->probB = new double[no_binary_problems];

            for (int i = 0; i < no_binary_problems; i++) {
                to_model->probA[i] = from_model->probA[i]; // XXX
                to_model->probB[i] = from_model->probB[i];
            }
        }
        else {
            to_model->probA = NULL;
            to_model->probB = NULL;
        }

        // Deep copy model->label and model->nSV
        to_model->label = new int[no_classes];
        to_model->nSV   = new int[no_classes];

        for (int i = 0; i < no_classes; i++) {
            to_model->label[i] = from_model->label[i];
            to_model->nSV[i]   = from_model->nSV[i];
        }
    }
    void SVM::copy_svm_problem (const svm_problem* const from_prob, svm_problem*& to_prob) {
        if (from_prob == NULL) {
            to_prob = NULL;
            return;
        }

        free_svm_problem(to_prob);
        to_prob = new svm_problem();

        to_prob->l = from_prob->l;

        to_prob->y = new double[from_prob->l];
        for (int i = 0; i < from_prob->l; i++) {
            to_prob->y[i] = from_prob->y[i];
        }

        to_prob->x = new svm_node*[from_prob->l];
        for (int i = 0; i < from_prob->l; i++) {
            int size = -1;
            while (from_prob->x[i][++size].index != -1) {}
            to_prob->x[i] = new svm_node[size];
            for (int j = 0; j < size; j++) {
                to_prob->x[i][j] = from_prob->x[i][j];
            }
        }
    }

    void SVM::free_svm_parameter (svm_parameter* const param) {
        if (param == NULL) {
            return;
        }

        delete[] param->weight_label;
        delete[] param->weight;
    }

    void SVM::free_svm_model (svm_model* const model) {
        if (model == NULL) {
            return;
        }

        free_svm_parameter(&(model->param));

        if (model->SV != NULL) {
            for (int i = 0; i < model->nr_class-1; i++) {
                delete[] model->SV[i];
            }
            delete[] model->SV;
            model->SV = NULL;
        }

        if (model->rho != NULL) {
            delete[] model->rho;   
            model->rho = NULL;
        }

        if (model->param.probability == 1) {
            if (model->probA != NULL) {
                delete[] model->probA;
                model->probA = NULL;
            }
            if (model->probB != NULL) {
                delete[] model->probB;
                model->probB = NULL;
            }
        }

        if (model->label != NULL) {
            delete[] model->label;
            model->label = NULL;
        }
        if (model->nSV != NULL) {
            delete[] model->nSV;
            model->nSV = NULL;
        }
    }

    void SVM::free_svm_problem (svm_problem* const prob) {
        if (prob == NULL) {
            return;
        }

        delete[] prob->y;
        for (int i = 0; i < prob->l; i++) {
            delete[] prob->x[i];
        }
        delete[] prob->x;
    }
}
