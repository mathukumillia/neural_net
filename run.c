/**
 * run.c
 *
 * Creates and runs a neural net.
 */

#include <stdio.h>
#include <stdlib.h>
#include "layer.h"
#include "activation.h"
#include "neuron.h"


int main() {
	double inputs[5] = {1,2,3,4,5};
	Layer *layer1 = init_input_layer(5, inputs);
	Layer *layer2 = init_layer(RELU, 1, 10, layer1->num_neurons);

	compute_layer_outputs(layer2, layer1);
	
	print_layer(layer1);
	print_layer(layer2);

	cleanup_layer(layer1);
	cleanup_layer(layer2);
	return 0;
}