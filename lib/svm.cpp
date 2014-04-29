#include <cassert>
#include <iostream>
#include "../include/svm.hpp"
#include "../include/libsvm.hpp"
#include "../include/utilities.hpp"

namespace abed {
    SVM::SVM (unsigned int d, unsigned int c) : dimension(d), no_classes(c) {
        param.svm_type = 0;
        param.kernel_type = 2;
        param.degree = 3;
        param.gamma = 1.0 / dimension;
        param.coef0 = 0.0;

        // used for training only
        param.cache_size = 100;
        param.eps = 0.001;
        param.C = 1.0;
        param.nr_weight = 0;
        param.weight_label = NULL;
        param.weight = NULL;
        param.nu = 0.5;
        param.p = 0.1;
        param.shrinking = 1;
        param.probability = 0;

        already_trained = false;
    }

    SVM::SVM (unsigned int d, unsigned int c, svm_parameter p) 
           : dimension(d), no_classes(c), param(p) {

        already_trained = false;
    }

    SVM::SVM (const SVM& svm) {
        this->dimension = svm.dimension;
        this->no_classes = svm.no_classes;
        this->param = svm.param;
        this->already_trained = svm.already_trained;

        copy_svm_parameter(svm.param, this->param);

        if (svm.already_trained) {
            copy_svm_problem(this->dimension, svm.prob, this->prob);
            copy_svm_model(svm.model, this->model);
        }

    }

    SVM& SVM::operator= (SVM svm) {
        swap(*this, svm);
        return *this;
    }

    void swap (SVM& first, SVM& second) {
        using std::swap;

        swap(first.dimension, second.dimension);
        swap(first.no_classes, second.no_classes);
        swap(first.param, second.param);
        swap(first.model, second.model);
        swap(first.prob, second.prob);
        swap(first.already_trained, second.already_trained);
    }

    SVM::~SVM () {
        svm_destroy_param(&param);
        if (already_trained) {
            svm_free_and_destroy_model(&model);
            free_svm_problem(prob);
        }
    }

    void SVM::initialize (unsigned int seed) {
        if (already_trained) {
            svm_free_and_destroy_model(&model);
            free_svm_problem(prob);
        }

        already_trained = false;
    }

    double SVM::train (const StaticDataSet& sds, double MAX_ERROR, unsigned int MAX_IT) {
        if (already_trained) {
            svm_free_and_destroy_model(&model);
            free_svm_problem(prob);
        }
        else {
            already_trained = true;
        }

        SVM::SDS_to_svm_problem(sds, prob);

        const char* msg = svm_check_parameter(&prob, &param);
        if (msg) {
            std::cout << msg << std::endl;
        }
        else {
            model = svm_train(&prob, &param);
        }

        return 0.0; //TODO
    }

    unsigned int SVM::predict_label (const StaticDataPoint& sdp) const {
        svm_node* x;
        SVM::SDP_to_svm_node(sdp, x, dimension);
        double predicted_label = svm_predict(model, x);
        delete[] x;
        return round(predicted_label);
    }

    void SVM::SDS_to_svm_problem (const StaticDataSet& sds, svm_problem& prob) {
        prob.l = sds.size();
        prob.y = new double[prob.l];
        prob.x = new svm_node*[prob.l];
        for (int i = 0; i < prob.l; i++) {
            SVM::SDP_to_svm_node(sds[i], prob.x[i], sds.get_dimension());
            prob.y[i] = sds[i].get_label();
        }
    }

    void SVM::SDP_to_svm_node (const StaticDataPoint& sdp, svm_node*& node, unsigned int d) {
        node = new svm_node[d+1];
        unsigned int i;
        for (i = 0; i < d; i++) {
            node[i].index = i+1;
            node[i].value = sdp[i];
        }
        node[i].index = -1;
    }

    void SVM::free_svm_problem (svm_problem& prob) {
        for (int i = 0; i < prob.l; i++) {
            delete[] prob.x[i];
        }
        delete[] prob.x;
        delete[] prob.y;
    }

    void SVM::copy_svm_parameter (const svm_parameter& from_param, svm_parameter& to_param) {
        to_param = from_param;
        if (from_param.nr_weight > 0) {
            to_param.weight_label = new int[from_param.nr_weight];
            to_param.weight = new double[from_param.nr_weight];
            for (int i = 0; i < from_param.nr_weight; i++) {
                to_param.weight_label[i] = from_param.weight_label[i];
                to_param.weight[i] = from_param.weight[i];
            }
        }
    }

    void SVM::copy_svm_problem (unsigned int d, const svm_problem& from_prob, svm_problem& to_prob) {
        to_prob.l = from_prob.l;
        to_prob.y = new double[from_prob.l];
        to_prob.x = new svm_node*[from_prob.l];
        for (int i = 0; i < from_prob.l; i++) {
            to_prob.y[i] = from_prob.y[i];
            to_prob.x[i] = new svm_node[d+1];
            for (unsigned int j = 0; j < d+1; j++) {
                to_prob.x[i][j] = from_prob.x[i][j];
            }
        }
    }

    void SVM::copy_svm_model (svm_model* const from_model, svm_model*& to_model) {
            const char* filename = ".saved_model.tmp";
            svm_save_model(filename, from_model);
            to_model = svm_load_model(filename);
    }

}
