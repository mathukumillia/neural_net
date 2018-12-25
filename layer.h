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


void init_layer(Layer *, ActivationType, int, int, int);
void init_input_layer(Layer *, int);
void update_inputs(Layer *, double *);
void compute_layer_outputs(Layer *, Layer *);
void print_layer(Layer *);
void cleanup_layer(Layer *);