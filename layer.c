/**
 * layer.c
 *
 * Performs functions that must be done at the layer level in a neural net.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "activation.h"
#include "layer.h"
#include "neuron.h"

/**
 * init_input_layer
 *
 * Initializes a layer of inputs to 0.
 */
void init_input_layer(Layer *layer, int num_inputs) {
    // the +1 accounts for the bias term
    layer->num_neurons = num_inputs + 1;
    layer->layer_num = 0;
    layer->type = INPUT;
    layer->neurons = (Neuron *) calloc(num_inputs + 1, sizeof(Neuron));
    if (layer->neurons == NULL) {
        fprintf(stderr, "Could not allocate neurons in layer.\n");
        exit(1);
    }
    // initialize the input neurons
    for (int i = 0; i < num_inputs; i++) {
        init_input_neuron(layer->neurons + i, i);
    }
    // initialize the bias neuron
    init_input_neuron(layer->neurons + num_inputs, num_inputs);
} 

/**
 * update_inputs 
 *  
 * Updates the inputs in the given layer (must be of input type).
 */ 
void update_inputs(Layer *layer, double *inputs) {
    assert(layer->type == INPUT);
    // we iterate from 0 to num_neurons - 1 to avoid updating the bias term
    for (int i = 0; i < layer->num_neurons - 1; i++) {
        set_output(layer->neurons + i, inputs[i]);
    }
}


/**
 * init_layer
 *
 * Initialize a layer with the given layer number with num_neurons of type type 
 * in it. Also takes in the number of inputs.
 */
void init_layer(Layer *layer, ActivationType type, int layer_num, int num_neurons, 
    int num_inputs) 
{
    // the layer num cannot be 0, as that is the input layer
    assert(layer_num != 0);
    layer->num_neurons = num_neurons;
    layer->layer_num = layer_num;
    layer->type = type;
    // initialize each neuron in the layer
    layer->neurons = (Neuron *) calloc(num_neurons, sizeof(Neuron));
    if (layer->neurons == NULL) {
        fprintf(stderr, "Could not allocate neurons in layer.\n");
        exit(1);
    }
    for (int i = 0; i < num_neurons; i++) {
        init_neuron(layer->neurons + i, type, num_inputs, layer_num, i);
    }
}

/**
 * print_layer
 *
 * Print this layer and all of the neurons in it.
 */
void print_layer(Layer *layer) {
    printf("---------------------------------------\n");
    printf("LAYER: %d\n", layer->layer_num);
    printf("---------------------------------------\n");
    for (int i = 0; i < layer->num_neurons; i++) {
        print_neuron(layer->neurons + i);
    }
    printf("---------------------------------------\n");
}

/**
 * compute_layer_outputs
 *
 * Computes each of the neurons' outputs given the previous layer's outputs as 
 * inputs
 */
void compute_layer_outputs(Layer *layer, Layer *prev_layer) {
    // the layer cannot be an input layer, as those have fixed output values
    assert(layer->type != INPUT);
    for (int i = 0; i < layer->num_neurons; i++) {
        compute_output(layer->neurons + i, prev_layer);
    }
}

/**
 * cleanup_layer
 *
 * Free the memory associated with the layer. Does NOT free layer itself.
 */
void cleanup_layer(Layer *layer) {
    // cleanup each neuron
    for (int i = 0; i < layer->num_neurons; i++) {
        cleanup_neuron(layer->neurons + i);
    }
    // free the neurons array 
    free(layer->neurons);
}


