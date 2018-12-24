/**
 * activation.c
 *
 * Implementation of various activation functions.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "activation.h"

double logistic_fn(double);
double logistic_derivative(double);

/**
 * init_activation
 *
 * Create an activation struct of the given type.
 */
Activation *init_activation(ActivationType type) {
	Activation *activation = (Activation *) malloc(sizeof(Activation));
	if (activation == NULL) {
		fprintf(stderr, "Could not allocate activation function.\n");
		exit(1);
	}
	switch(type) {
		case INPUT:
			activation->name = (char *) calloc(6, sizeof(char));
			if (activation->name == NULL) {
				fprintf(stderr, "Could not allocate activation name.\n");
				exit(1);
			}
			strncpy(activation->name, "INPUT", 5);
			break;
		case LOGISTIC: 
			activation->fn = &logistic_fn;
			activation->derivative = &logistic_derivative;
			activation->name = (char *) calloc(9, sizeof(char));
			if (activation->name == NULL) {
				fprintf(stderr, "Could not allocate activation name.\n");
				exit(1);
			}
			strncpy(activation->name, "LOGISTIC", 8);
			break;
		default: 
			fprintf(stderr, "Activation type is unsupported.\n");
			exit(1);
	}
	return activation;
}

/** 
 * logistic_fn
 *
 * The logistic activation function.
 */
double logistic_fn(double input) {
	return 1/(1 + exp(-1 * input));
}

/**
 * logistic_derivative
 *
 * The derivative of a logistic activation function.
 */
double logistic_derivative(double input) {
	return logistic_fn(input) * (1 - logistic_fn(input));
}

/**
 * cleanup_activation
 *
 * Frees the memory associated with an activation function.
 */
void cleanup_activation(Activation *activation) {
	free(activation->name);
	free(activation);
}