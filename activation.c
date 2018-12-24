/**
 * activation.c
 *
 * Various activation functions and their derivatives.
 */

#include <math.h>
#include "activation.h"

double logistic_fn(double input) {
	return 1/(1 + exp(-1 * input));
}

double logistic_derivative(double input) {
	return logistic_fn(input) * (1 - logistic_fn(input));
}