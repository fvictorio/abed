#include <cassert>
#include <vector>
#include <iostream>
#include <climits>
#include "../include/mlp.hpp"
#include "../include/utilities.hpp"

namespace abed {
    
    using std::vector;
    using std::cout;
    using std::endl;
    
    MLP::MLP (unsigned int d, unsigned int c, const vector<unsigned int> &hl, 
              double lr, double m, double wr, unsigned int seed)
              : dimension(d), no_classes(c), learning_rate(lr), momentum(m) {

        // Units per layer, not including bias units
        layers = hl; // hidden layers
        layers.push_back(no_classes); // output layer

        no_layers = layers.size();

        // Resize outputs
        outputs.resize(no_layers);
        for (unsigned int i = 0; i < no_layers; i++) {
            outputs[i].resize(layers[i]);
        }
        error_terms = outputs;

        // Resize weights[layer][unit][input_weight]
        weights.resize(no_layers);

        for (unsigned int i = 0; i < weights.size(); i++) {
            weights[i].resize(layers[i]);
        }

        for (unsigned int j = 0; j < weights[0].size(); j++) { // first layer
            weights[0][j].resize(dimension + 1); // bias -> +1
        }

        for (unsigned int i = 1; i < weights.size(); i++) { // other layers
            for (unsigned int j = 0; j < weights[i].size(); j++) {
                weights[i][j].resize(weights[i-1].size() + 1); // bias -> +1
            }
        }

        delta_weights = weights; // used for momentum

        // Initialize weights
        if (seed == UINT_MAX) {
            srand(time(NULL));
        }
        else {
            srand(seed);
        }
        for (unsigned int i = 0; i < weights.size(); i++) {
            for (unsigned int j = 0; j < weights[i].size(); j++) {
                for (unsigned int k = 0; k < weights[i][j].size(); k++) {
                    weights[i][j][k] = randrange(-wr, wr);
                }
            }
        }
    }

    void MLP::classify (StaticDataSet& sds) const {
        for (unsigned int n = 0; n < sds.get_size(); n++) {
            StaticDataPoint& x = sds[n];
            this->compute_outputs(x);

            unsigned int predicted_label = this->predict_label(x);
            x.set_label(predicted_label);
        }
    }
    
    double MLP::train (const StaticDataSet& sds, double MAX_ERROR, unsigned int MAX_IT) {
        double total_error;
        unsigned int iteration = 1;
        
        do {
            total_error = 0.0;
            for (unsigned int n = 0; n < sds.get_size(); n++) {
                const StaticDataPoint& x = sds[n];
                this->compute_outputs(x);

                // Backward
                unsigned int correct_label = x.get_label();
                unsigned int predicted_label = this->predict_label(x);

                if (correct_label != predicted_label) total_error += 1.0;

                for (unsigned int j = 0; j < error_terms[no_layers-1].size(); j++) {
                    error_terms[no_layers-1][j] = (j == correct_label ? 1.0 : 0.0) - outputs[no_layers-1][j];
                    error_terms[no_layers-1][j] *= outputs[no_layers-1][j] * (1.0 - outputs[no_layers-1][j]);
                }

                for (int i = no_layers-2; i >= 0; i--) {
                    for (unsigned int j = 0; j < error_terms[i].size(); j++) {
                        error_terms[i][j] = 0.0;
                        for (unsigned int k = 0; k < error_terms[i+1].size(); k++) {
                            error_terms[i][j] += error_terms[i+1][k] * weights[i+1][k][j];
                        }
                        error_terms[i][j] *= outputs[i][j] * (1.0 - outputs[i][j]);
                    }
                }

                // Forward
                for (unsigned int i = 0; i < no_layers; i++) {
                    for (unsigned int j = 0; j < error_terms[i].size(); j++) {
                        unsigned int k;
                        double delta;
                        for (k = 0; k+1 < weights[i][j].size(); k++) {
                            delta = learning_rate * error_terms[i][j] *
                                    (i == 0 ? x[k] : outputs[i-1][k]);
                            delta += momentum * delta_weights[i][j][k];
                            delta_weights[i][j][k] = delta;
                            weights[i][j][k] += delta;
                        }
                        delta = learning_rate * error_terms[i][j];
                        delta += momentum * delta_weights[i][j][k];
                        delta_weights[i][j][k] = delta;
                        weights[i][j][k] += delta;
                    }
                }
            }
            
            total_error /= sds.get_size();
            iteration++;
        } while (total_error > MAX_ERROR && iteration <= MAX_IT);
        cout << iteration << endl;

        return total_error;
    }

    void MLP::compute_outputs (const StaticDataPoint& x) const {
        // First layer
        for (unsigned int j = 0; j < outputs[0].size(); j++) {
            outputs[0][j] = 0.0;

            unsigned int k;
            for (k = 0; k+1 < weights[0][j].size(); k++) {
                outputs[0][j] += weights[0][j][k] * x[k];
            }
            outputs[0][j] += weights[0][j][k]; // bias

            outputs[0][j] = sigmoid(outputs[0][j]);
        }

        // Other layers
        for (unsigned int i = 1; i < outputs.size(); i++) {
            for (unsigned int j = 0; j < outputs[i].size(); j++) {
                outputs[i][j] = 0.0;

                unsigned int k;
                for (k = 0; k+1 < weights[i][j].size(); k++) {
                    outputs[i][j] += weights[i][j][k] * outputs[i-1][k];
                }
                outputs[i][j] += weights[i][j][k]; // bias

                outputs[i][j] = sigmoid(outputs[i][j]);
            }
        }
    }

    unsigned int MLP::predict_label (const StaticDataPoint& x) const {
        // Label is the index of the output unit with maximum activation
        double max_output = outputs[no_layers-1][0];
        unsigned int max_idx = 0;
        for (unsigned int j = 1; j < layers[no_layers-1]; j++) {
            if (outputs[no_layers-1][j] > max_output) {
                max_output = outputs[no_layers-1][j];
                max_idx = j;
            }
        }
        return max_idx;
    }

    void MLP::print_weights () const {
        for (unsigned int i = 0; i < weights.size(); i++) {
            cout << "Layer " << i << ":" << endl;
            for (unsigned int j = 0; j < weights[i].size(); j++) {
                cout << "Unit " << j << ": ";
                for (unsigned int k = 0; k < weights[i][j].size(); k++) {
                    cout << weights[i][j][k] << " ";
                }
                cout << endl;
            }
        }
        cout << "----------------------" << endl;
    }

    void MLP::print_error_terms () const {
        for (unsigned int i = 0; i < error_terms.size(); i++) {
            cout << "Layer " << i << ":" << endl;
            for (unsigned int j = 0; j < error_terms[i].size(); j++) {
                cout << error_terms[i][j] << " ";
            }
            cout << endl;
        }
        cout << "----------------------" << endl;
    }

    void MLP::print_outputs () const {
        for (unsigned int i = 0; i < outputs.size(); i++) {
            cout << "Layer " << i << ":" << endl;
            for (unsigned int j = 0; j < outputs[i].size(); j++) {
                cout << outputs[i][j] << " ";
            }
            cout << endl;
        }
        cout << "----------------------" << endl;
    }
}
