/**
 * activation.h
 *
 * Represents an activation function and its derivative.
 */

#pragma once

typedef struct activation {
	double (*fn) (double);
	double (*derivative) (double);
	char *name;
} Activation;

typedef enum {
	INPUT = 0,
	LOGISTIC = 1
} ActivationType;
 
Activation *init_activation(ActivationType);
void cleanup_activation(Activation *);