/**
 * run.c
 *
 * Creates and runs a neural net.
 */

#include <stdio.h>
#include <stdlib.h>
#include "activation.h"
#include "neuron.h"


int main() {
	// create a neuron and print it to the console
	Neuron *neuron = init_neuron(&logistic_fn, &logistic_derivative, 3, 0, 0);
	print_neuron(neuron);
	cleanup_neuron(neuron);
	return 0;
}