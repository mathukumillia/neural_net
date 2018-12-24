/**
 * run.c
 *
 * Creates and runs a neural net.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "layer.h"
#include "activation.h"
#include "data_reader.h"
#include "neuron.h"

int main(int argc, char **argv) {
    // ensure the program has been called with a filename
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }
    
    Data *data = read_data(argv[1]);
    // print_data(data);
    Layer *layer1 = init_input_layer(5, data->xvals[0]);
    Layer *layer2 = init_layer(RELU, 1, 10, layer1->num_neurons);
    Layer *layer3 = init_layer(RELU, 2, 10, layer2->num_neurons);

    compute_layer_outputs(layer2, layer1);
    compute_layer_outputs(layer3, layer2);
    
    // print_layer(layer1);
    // print_layer(layer2);
    // print_layer(layer3);

    cleanup_layer(layer1);
    cleanup_layer(layer2);
    cleanup_layer(layer3);
    cleanup_data(data);
    return 0;
}