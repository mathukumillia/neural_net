/**
 * layer.h
 *
 * Represents a layer in the neural network.
 */
#pragma once

#include "activation.h"
#include "neuron.h"

typedef struct layer {
    Neuron *neurons;
    int num_neurons;
    int layer_num;
    ActivationType type;
} Layer;


Layer *init_layer(ActivationType, int, int, int);
Layer *init_input_layer(int, double *);
void compute_layer_outputs(Layer *, Layer *);
void print_layer(Layer *);
void cleanup_layer(Layer *);