/**
 * neuron.h
 *
 * Represents a neuron in a neural net. 
 *
 */
#pragma once

typedef struct neuron {
	int id;
	double (*activation_fn) (double);
	double (*activation_derivative) (double);
	int layer;
	int num_weights;
	double *weights;
	double output;
} Neuron;

Neuron *init_neuron(double (*)(double), double (*)(double), int, int, int);
void print_neuron(Neuron *neuron);
void cleanup_neuron(Neuron *neuron);