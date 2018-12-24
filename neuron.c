/**
 * neuron.c
 *
 * Implementation for a neuron in a neural net.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "neuron.h"

/**
 * init_neuron
 *
 * Returns a neuron in the given layer with the given id, activation function, 
 * derivative, and number of weights (equivalent to number of inputs).
 */
Neuron *init_neuron(double (*activation)(double), 
	double (*activation_derivative)(double), int num_weights, int layer, int id) 
{
	Neuron *neuron = (Neuron *) malloc(sizeof(Neuron));
	if (neuron == NULL) {
		fprintf(stderr, "Could not allocate neuron.\n");
		exit(1);
	}
	neuron->activation_fn = activation;
	neuron->activation_derivative = activation_derivative;
	// TODO: what should the weights and output be initialized to?
	neuron->num_weights = num_weights;
	neuron->weights = (double *) calloc(num_weights, sizeof(double));
	if (neuron->weights == NULL) {
		fprintf(stderr, "Could not allocate weights in neuron.\n");
		exit(1);
	}
	neuron->id = id;
	neuron->layer = layer;
	neuron->output = 0;
	return neuron;
}

/**
 * print_neuron
 * 
 * Prints a neuron to the console. Useful for debugging.
 */
void print_neuron(Neuron *neuron) {
	printf("----------------------------------------------\n");
	printf("Layer %d Neuron %d:\n", neuron->layer, neuron->id);
	printf("----------------------------------------------\n");
	// print out the weights
	printf("Weights: ");
	for (int i = 0; i < neuron->num_weights; i++) {
		printf("%f ", neuron->weights[i]);
	}	
	printf("\n");	
	// print out the output of the neuron
	printf("Output: %f\n", neuron->output);
	printf("----------------------------------------------\n");
}


/**
 * cleanup_neuron
 *
 * Frees the memory associated with a neuron.
 */
void cleanup_neuron(Neuron *neuron) {
	free(neuron->weights);
	free(neuron);
}