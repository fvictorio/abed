#include <cassert>
#include <iostream>
#include "../include/svm.hpp"

namespace abed {
    SVM::SVM (unsigned int d, unsigned int c) : dimension(d), no_classes(c) {
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

    SVM::SVM (unsigned int d, unsigned int c, const svm_parameter& p) 
           : dimension(d), no_classes(c) {
        param = new svm_parameter(p);
    }

    void SVM::initialize (unsigned int seed) {
        //TODO
    }

    double SVM::train (const StaticDataSet& sds, double MAX_ERROR, unsigned int MAX_IT) {
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
        return static_cast<unsigned int>(predicted_label);
    }

    void SVM::SDS_to_SVM_problem (const StaticDataSet& sds, svm_problem*& prob) {
        prob = new svm_problem();
        prob->l = sds.size();
        prob->y = new double[prob->l];
        prob->x = new svm_node*[prob->l];
        for (int i = 0; i < prob->l; i++) {
            SVM::SDP_to_SVM_node(sds[i], prob->x[i], sds.get_dimension());
            prob->y[i] = sds[i].get_label();
            //prob->x[i] = new svm_node[sds.get_dimension() + 1];
            //unsigned int j;
            //for (j = 0; j < sds.get_dimension(); j++) {
            //    prob->x[i][j].index = j+1;
            //    prob->x[i][j].value = sds[i][j];
            //}
            //prob->x[i][j].index = -1;
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
}
