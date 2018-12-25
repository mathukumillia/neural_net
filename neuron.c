/**
 * neuron.c
 *
 * Implementation for a neuron in a neural net.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "neuron.h"
#include "layer.h"
#include "activation.h"

/**
 * init_input_neuron
 *
 * Initializes the given neuron to be an input neuron w/ a default value of 0.
 */
void init_input_neuron(Neuron *neuron, int id) {
    neuron->activation = init_activation(INPUT);
    neuron->num_weights = 0;
    neuron->layer = 0;
    neuron->id = id;
    neuron->output = 0;
}

/**
 * set_output
 *
 * Sets the output value of an input neuron (i.e. updates an input value)
 */
void set_output(Neuron *neuron, double input) {
    neuron->output = input;
}

/**
 * init_neuron
 *
 * Initializes the given neuron in the given layer with the given id, activation 
 * function, derivative, number of weights (equivalent to number of inputs), and 
 * output.
 */
void init_neuron(Neuron *neuron, ActivationType type, int num_weights, 
    int layer, int id) 
{
    neuron->activation = init_activation(type);
    neuron->num_weights = num_weights;
    // allocate the weights
    neuron->weights = (double *) calloc(num_weights, sizeof(double));
    if (neuron->weights == NULL) {
        fprintf(stderr, "Could not allocate weights in neuron.\n");
        exit(1);
    }
    // initialize the weights to some value between 0 and 1
    for (int i = 0; i < num_weights; i++) {
        neuron->weights[i] = (double) rand()/(double) RAND_MAX;
    }
    neuron->id = id;
    neuron->layer = layer;
    neuron->output = 0;
}

/**
 * print_neuron
 * 
 * Prints a neuron to the console. Useful for debugging.
 */
void print_neuron(Neuron *neuron) {
    printf("\n");
    printf("Layer %d Neuron %d:\n", neuron->layer, neuron->id);
    // print out the activation function type
    printf("Activation Function: %s\n", neuron->activation->name);
    // print out the weights
    printf("Weights: ");
    for (int i = 0; i < neuron->num_weights; i++) {
        printf("%f ", neuron->weights[i]);
    }   
    printf("\n");   
    // print out the output of the neuron
    printf("Output: %f\n", neuron->output);
}


/**
 * cleanup_neuron
 *
 * Frees the memory associated with a neuron. Does NOT free the neuron itself.
 */
void cleanup_neuron(Neuron *neuron) {
    cleanup_activation(neuron->activation);
    free(neuron->weights);
}

/**
 * compute_output
 *
 * Computes the output of the neuron given the previous layer. The previous 
 * layer is passed in as a void pointer to prevent a circular dependency between
 * layer and neuron.
 */
void compute_output(Neuron *neuron, void *prev) {
    // the number of elements in the previous layer should equal the number of 
    // weights in this neuron
    Layer *prev_layer = (Layer *) prev;
    assert(prev_layer->num_neurons == neuron->num_weights);
    double weighted_sum = 0;
    for (int i = 0; i < neuron->num_weights; i++) {
        weighted_sum += neuron->weights[i] * prev_layer->neurons[i].output;
    }
    neuron->output = neuron->activation->fn(weighted_sum);
}