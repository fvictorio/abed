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
        assert(false);
    }

    SVM& SVM::operator= (SVM svm) {
        assert(false);
    }

    SVM::~SVM () {
        svm_free_and_destroy_model(&model);
        svm_destroy_param(&param);
        free_svm_problem(prob);
    }

    void SVM::initialize (unsigned int seed) {
        //TODO
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
}
