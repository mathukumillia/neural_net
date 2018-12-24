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
 * Initializes a layer of inputs using the given array of inputs.
 */
Layer *init_input_layer(int num_inputs, double *inputs) {
	Layer *layer = (Layer *) calloc(1, sizeof(Layer));
	if (layer == NULL) {
		fprintf(stderr, "Could not allocate layer struct.\n");
		exit(1);
	}
	layer->num_neurons = num_inputs;
	layer->layer_num = 0;
	layer->type = INPUT;
	layer->neurons = (Neuron *) calloc(num_inputs, sizeof(Neuron));
	if (layer->neurons == NULL) {
		fprintf(stderr, "Could not allocate neurons in layer.\n");
		exit(1);
	}
	for (int i = 0; i < num_inputs; i++) {
		init_input_neuron(layer->neurons + i, i, inputs[i]);
	}
	return layer;
}	

/**
 * init_layer
 *
 * Initialize a layer with the given layer number with num_neurons of type type 
 * in it. Also takes in the number of inputs.
 */
Layer *init_layer(ActivationType type, int layer_num, int num_neurons, 
	int num_inputs) 
{
	// the layer num cannot be 0, as that is the input layer
	assert(layer_num != 0);
	Layer *layer = (Layer *) calloc(1, sizeof(Layer));
	if (layer == NULL) {
		fprintf(stderr, "Could not allocate layer struct.\n");
		exit(1);
	}
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
	return layer;
}

/**
 * print_layer
 *
 * Print this layer and all of the neurons in it.
 */
void print_layer(Layer *layer) {
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
 * Free the memory associated with the layer.
 */
void cleanup_layer(Layer *layer) {
	// cleanup each neuron
	for (int i = 0; i < layer->num_neurons; i++) {
		cleanup_neuron(layer->neurons + i);
	}
	// free the neurons array 
	free(layer->neurons);
	// free the layer
	free(layer);
}


