/**
 * neural_net.c
 *
 * Implements an API that models a neural network.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "layer.h"
#include "activation.h"
#include "neural_net.h"

void expand_capacity(NeuralNetwork *);
double compute_error(NeuralNetwork *, double *, int);

/**
 * init_neural_net
 *
 * Initializes and returns a neural network with a capacity for 10 layers. Also 
 * initializes the input layer using the given number of inputs.
 */
NeuralNetwork *init_neural_net(int num_inputs) {
    NeuralNetwork *network = (NeuralNetwork *) calloc(1, sizeof(NeuralNetwork));
    if (network == NULL) {
        fprintf(stderr, "Could not allocate NeuralNetwork.\n");
        exit(1);
    }
    network->layer_capacity = 1;
    network->layers = (Layer *) calloc(network->layer_capacity, sizeof(Layer));
    if (network->layers == NULL) {
        fprintf(stderr, "Could not allocate layers for NeuralNetwork.\n");
        exit(1);
    }
    network->num_layers = 1;
    init_input_layer(network->layers, num_inputs);
    return network;
}

/** 
 * expand_capacity
 *
 * Doubles the layer capacity of the network.
 */
void expand_capacity(NeuralNetwork *network) {
    network->layer_capacity *= 2;
    network->layers = (Layer *)realloc(network->layers, 
        network->layer_capacity * sizeof(Layer));
    if (network->layers == NULL) {
        fprintf(stderr, "Error reallocating layers for NeuralNetwork.\n");
        exit(1);
    }
}

/**
 * update_neural_net_input
 *
 * Update the input values to the neural network.
 */
void update_neural_net_input(NeuralNetwork *network, double *inputs) {
    update_inputs(network->layers, inputs);
}

/**
 * compute_neural_net_output
 *
 * Computes the output of the neural network.
 */
void compute_neural_net_output(NeuralNetwork *network) {
    // we start at 1 because the input layer should already know its outputs
    for (int i = 1; i < network->num_layers; i++) {
        compute_layer_outputs(network->layers + i, network->layers + i - 1);
    }
}

/** 
 * train_neural_net
 *
 * Trains the neural net given data using stochastic gradient descent.
 */
void train_neural_net(NeuralNetwork *network, Data *data) {
    double error = 0;
    for (int i = 0; i < data->num_pts; i++) {
        update_neural_net_input(network, data->xvals[i]);
        print_neural_net(network);
        compute_neural_net_output(network);
        error = compute_error(network, data->yvals[i], data->ydim);
        printf("Error: %f\n", error);
    }
}

/**
 * compute_error
 *
 * Computes the error using Euclidean distance from the given output.
 */
double compute_error(NeuralNetwork *network, double *output, int ydim) {
    double error = 0;
    Layer *output_layer = &network->layers[network->num_layers - 1];
    int dim = output_layer->num_neurons;
    // the dimension of the last neural network layer must match the output 
    // dimension
    assert(dim == ydim);
    for (int i = 0; i < dim; i++) {
        error += pow(output_layer->neurons[i].output - output[i], 2);
    }
    return error;
}

/**
 * add_layer
 *
 * Adds a layer of the given type to the neural network that contains the given 
 * number of neurons.
 */
void add_layer(NeuralNetwork *network, ActivationType type, int num_neurons) {
    if (network->num_layers == network->layer_capacity) {
        expand_capacity(network);
    }
    init_layer(network->layers + network->num_layers, type, network->num_layers,
        num_neurons, network->layers[network->num_layers - 1].num_neurons);
    network->num_layers += 1;
}

/**
 * print_neural_net
 *
 * Prints out a neural network to the console.
 */
void print_neural_net(NeuralNetwork *network) {
    printf("--------------------------------------------\n");
    printf("NEURAL NETWORK\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < network->num_layers; i++) {
        print_layer(network->layers + i);
    }
    printf("--------------------------------------------\n");
}

/**
 * cleanup_neural_net
 *
 * Frees all the memory associated with this neural network.
 */
void cleanup_neural_net(NeuralNetwork *network) {
    for (int i = 0; i < network->num_layers; i++) {
        cleanup_layer(network->layers + i);
    }
    free(network->layers);
    free(network);
}