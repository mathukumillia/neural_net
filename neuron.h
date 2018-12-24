/**
 * neuron.h
 *
 * Represents a neuron in a neural net. 
 *
 */
#pragma once

#include "activation.h"

typedef struct neuron {
    int id;
    Activation *activation;
    int layer;
    int num_weights;
    double *weights;
    double output;
} Neuron;

void init_neuron(Neuron *, ActivationType, int, int, int);
void init_input_neuron(Neuron *, int, double);
void compute_output(Neuron *, void *);
void print_neuron(Neuron *);
void cleanup_neuron(Neuron *);