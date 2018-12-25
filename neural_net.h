/**
 * neural_net.h
 *
 * Defines an API that models a neural network. 
 */
#pragma once
#include "activation.h"
#include "layer.h"
#include "data_reader.h"

typedef struct neural_net {
    int num_layers;
    int layer_capacity;
    Layer *layers;
} NeuralNetwork;

NeuralNetwork *init_neural_net(int);
void cleanup_neural_net(NeuralNetwork *);
void print_neural_net(NeuralNetwork *);
void add_layer(NeuralNetwork *, ActivationType, int);
void update_neural_net_input(NeuralNetwork *, double *);
void compute_neural_net_output(NeuralNetwork *);
void train_neural_net(NeuralNetwork *, Data *);