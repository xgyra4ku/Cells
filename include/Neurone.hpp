#pragma once
#ifndef NEURONE_HPP
#define NEURONE_HPP
#include "glogal.hpp"

using namespace std;

class NeuralNetwork {
public:
    double sigmoid(double x) {
        return 1.0 / (1.0 + exp(-x));
    }

    double sigmoid_derivative(double x) {
        return x * (1.0 - x);
    }

    void init(int inputSize, int hiddenSize, int outputSize) {
        this->inputSize = inputSize;
        this->hiddenSize = hiddenSize;
        this->outputSize = outputSize;

        // Initialize weights with random values
        weights1 = vector<vector<double>>(inputSize, vector<double>(hiddenSize));
        weights2 = vector<vector<double>>(hiddenSize, vector<double>(outputSize));
        
        for (int i = 0; i < inputSize; i++)
            for (int j = 0; j < hiddenSize; j++)
                weights1[i][j] = ((double) rand() / (RAND_MAX));

        for (int i = 0; i < hiddenSize; i++)
            for (int j = 0; j < outputSize; j++)
                weights2[i][j] = ((double) rand() / (RAND_MAX));
    }

    vector<double> feedforward(const vector<vector<double>>& weights1, const vector<vector<double>>& weights2, vector<double> inputs) {
        this->inputs = inputs;

        // Calculate hidden layer activation
        hidden.resize(hiddenSize);
        for (int i = 0; i < hiddenSize; i++) {
            hidden[i] = 0.0;
            for (int j = 0; j < inputSize; j++) {
                hidden[i] += inputs[j] * weights1[j][i];
            }
            hidden[i] = sigmoid(hidden[i]);
        }

        // Calculate output layer activation
        outputs.resize(outputSize);
        for (int i = 0; i < outputSize; i++) {
            outputs[i] = 0.0;
            for (int j = 0; j < hiddenSize; j++) {
                outputs[i] += hidden[j] * weights2[j][i];
            }
            outputs[i] = sigmoid(outputs[i]);
        }

        return outputs;
    }

    void backpropagate(vector<double> target) {
        // Calculate output layer error
        vector<double> outputErrors(outputSize);
        for (int i = 0; i < outputSize; i++) {
            outputErrors[i] = target[i] - outputs[i];
        }

        // Calculate hidden layer error
        vector<double> hiddenErrors(hiddenSize);
        for (int i = 0; i < hiddenSize; i++) {
            hiddenErrors[i] = 0.0;
            for (int j = 0; j < outputSize; j++) {
                hiddenErrors[i] += outputErrors[j] * weights2[i][j];
            }
            hiddenErrors[i] *= sigmoid_derivative(hidden[i]);
        }

        // Update weights for weights2
        for (int i = 0; i < hiddenSize; i++) {
            for (int j = 0; j < outputSize; j++) {
                weights2[i][j] += hidden[i] * outputErrors[j];
            }
        }

        // Update weights for weights1
        for (int i = 0; i < inputSize; i++) {
            for (int j = 0; j < hiddenSize; j++) {
                weights1[i][j] += inputs[i] * hiddenErrors[j];
            }
        }
    }

private:
    int inputSize;
    int hiddenSize;
    int outputSize;

    vector<double> inputs;
    vector<double> hidden;
    vector<double> outputs;

    vector<vector<double>> weights1;
    vector<vector<double>> weights2;
};

#endif // NEURONE_HPP
