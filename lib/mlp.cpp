#include <cassert>
#include <vector>
#include <iostream> // XXX
#include "../include/mlp.hpp"
#include "../include/utilities.hpp"

namespace abed {
    
    using std::vector;
    
    MLP::MLP (unsigned int d, unsigned int l, const vector<unsigned int> &hl, double lr, double mom) 
             : dimension(d), no_labels(l), layers(hl), learning_rate(lr), momentum(mom) {
        
        for (unsigned int i = 0; i < layers.size(); i++) {
            layers[i]++; // bias
        }
        layers.push_back(l);
        no_layers = layers.size();

        // WEIGHTS
        // Resize
        weights.resize(no_layers);
        for (unsigned int i = 0; i < no_layers; i++) {
            weights[i].resize(layers[i]);
        }
        for (unsigned int i = 0; i < layers[0]; i++) {
            weights[0][i].resize(dimension+1); // bias -> +1
        }
        for (unsigned int i = 1; i < no_layers; i++) {
            for (unsigned int j = 0; j < layers[i]; j++) {
                weights[i][j].resize(layers[i-1]); // output layer doesn't have bias
            }
        }
        delta_weights = weights;

        // Initialize
        for (unsigned int i = 0; i < weights.size(); i++) {
            for (unsigned int j = 0; j < weights[i].size(); j++) {
                for (unsigned int k = 0; k < weights[i][j].size(); k++) {
                    if (i+1 < no_layers && j+1 == layers[i]) {
                        weights[i][j][k] = 0.0;
                    }
                    else {
                        weights[i][j][k] = randrange(-0.05, 0.05);
                    }
                }
            }
        }

        //XXX
        //for (unsigned int i = 0; i < weights.size(); i++) {
        //    std::cout << "Layer " << i << std::endl;
        //    for (unsigned int j = 0; j < weights[i].size(); j++) {
        //        std::cout << "\tUnit " << j << std::endl;
        //        for (unsigned int k = 0; k < weights[i][j].size(); k++) {
        //            std::cout << "\t\tWeight " << k << ": " << weights[i][j][k] << std::endl;
        //        }
        //    }
        //}

        // OUTPUTS
        // Resize
        outputs.resize(no_layers);
        for (unsigned int i = 0; i < no_layers; i++) {
            outputs[i].resize(layers[i]);
        }

        //XXX
        //for (unsigned int i = 0; i < outputs.size(); i++) {
        //    std::cout << "Layer " << i << std::endl;
        //    for (unsigned int j = 0; j < outputs[i].size(); j++) {
        //        std::cout << "\tUnit " << j << ": " << outputs[i][j] << std::endl;
        //    }
        //}
    }

    double MLP::train (const StaticDataSet& sds) {
        vector<vector<double> > error_terms = outputs;

        for (unsigned int i = 0; i < delta_weights.size(); i++) {
            for (unsigned int j = 0; j < delta_weights[i].size(); j++) {
                for (unsigned int k = 0; k < delta_weights[i][j].size(); k++) {
                    delta_weights[i][j][k] = 0.0;
                }
            }
        }

        double total_error;

        unsigned int count = 0; // XXX
        unsigned int MAX_N = 1000; // XXX

        do {
            total_error = 0.0;
            for (unsigned int n = 0; n < sds.get_size(); n++) {
                const StaticDataPoint& x = sds[n];

                unsigned int predicted_label = predict(x);
                unsigned int correct_label = x.get_label();

                if (predicted_label != correct_label) total_error += 1.0;

                for (unsigned int j = 0; j < no_labels; j++) {
                    double tk = (j == correct_label ? 1.0 : 0.0);
                    double ok = outputs[no_layers-1][j];
                    error_terms[no_layers-1][j] = ok * (1.0 - ok) * (tk - ok);
                }

                for (int i = no_layers - 2; i >= 0; i--) {
                    for (unsigned int j = 0; j < layers[i]; j++) {
                        error_terms[i][j] = 0.0;
                        for (unsigned int k = 0; k < layers[i+1]; k++) {
                            error_terms[i][j] += weights[i+1][k][j] * error_terms[i+1][k];
                        }
                        error_terms[i][j] *= outputs[i][j] * (1.0 - outputs[i][j]);
                    }
                }

                for (unsigned int i = 0; i < weights.size(); i++) {
                    for (unsigned int j = 0; j < weights[i].size(); j++) {
                        for (unsigned int k = 0; k < weights[i][j].size(); k++) {
                            double delta = learning_rate * error_terms[i][j];
                            if (i == 0) {
                                if (k < dimension) delta *= x[k];
                            }
                            else {
                                delta *= outputs[i-1][k];
                            }
                            delta += momentum * delta_weights[i][j][k];
                            delta_weights[i][j][k] = delta;
                            weights[i][j][k] += delta; //TODO momentum
                        }
                    }
                }
            }

            //XXX outputs
            //for (unsigned int i = 0; i < outputs.size(); i++) {
            //    std::cout << "Layer " << i << std::endl;
            //    for (unsigned int j = 0; j < outputs[i].size(); j++) {
            //        std::cout << "\tUnit " << j << ": " << outputs[i][j] << std::endl;
            //    }
            //}
            //XXX error_term
            //for (unsigned int i = 0; i < error_terms.size(); i++) {
            //    std::cout << "Layer " << i << std::endl;
            //    for (unsigned int j = 0; j < error_terms[i].size(); j++) {
            //        std::cout << "\tUnit " << j << ": " << error_terms[i][j] << std::endl;
            //    }
            //}


            total_error /= sds.get_size();

            count++;
            //XXX error
            if (count % 1 == 0) std::cout << total_error << std::endl;
            //XXX weights
            //if (count % 1 == 0) {
            //    for (unsigned int i = 0; i < weights.size(); i++) {
            //        for (unsigned int j = 0; j < weights[i].size(); j++) {
            //            for (unsigned int k = 0; k < weights[i][j].size(); k++) {
            //                std::cout << i << " " << j << " " << k << ": " << weights[i][j][k] << std::endl;
            //            }
            //        }
            //    }
            //    std::cout << "-----------" << std::endl;
            //}

        } while (total_error > 0.05);
        //} while (total_error > 0.05 && count <= MAX_N);
        return total_error;
    }

    void MLP::classify (StaticDataSet& sds) const {
        for (unsigned int n = 0; n < sds.get_size(); n++) {
            StaticDataPoint& x = sds[n];

            unsigned int predicted_label = predict(x);
            x.set_label(predicted_label);
        }
    }

    unsigned int MLP::predict (const StaticDataPoint& x) const {
        compute_outputs(x);

        unsigned int predicted_label = 0;
        double max_output = outputs[no_layers-1][0];
        for (unsigned int i = 1; i < no_labels; i++) {
            if (outputs[no_layers-1][i] > max_output) {
                max_output = outputs[no_layers-1][i];
                predicted_label = i;
            }
        }

        return predicted_label;
    }

    void MLP::compute_outputs (const StaticDataPoint& x) const {

        for (unsigned int j = 0; j < layers[0]; j++) {
            // If bias unit
            if (j+1 == layers[0]) { // bias
                outputs[0][j] = 1.0;
            }
            else {
                outputs[0][j] = 0.0;
                for (unsigned int k = 0; k < dimension; k++) {
                    outputs[0][j] += weights[0][j][k] * x[k];
                }
                outputs[0][j] += weights[0][j][dimension]; // bias
                outputs[0][j] = sigmoid(outputs[0][j]);
            }
        }

        for (unsigned int i = 1; i < no_layers; i++) {
            for (unsigned int j = 0; j < layers[i]; j++) {
                // If hidden layer and bias unit
                if (i+1 < no_layers && j+1 == layers[i]) {
                    outputs[i][j] = 1.0;
                }
                else {
                    outputs[i][j] = 0.0;
                    for (unsigned int k = 0; k < layers[i-1]; k++) {
                        outputs[i][j] += weights[i][j][k] * outputs[i-1][k];
                    }
                    outputs[i][j] = sigmoid(outputs[i][j]);
                }
            }
        }
    }
}
