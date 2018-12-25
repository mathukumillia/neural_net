/**
 * run.c
 *
 * Creates and runs a neural net.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "activation.h"
#include "data_reader.h"
#include "neural_net.h"

int main(int argc, char **argv) {
    // ensure the program has been called with a filename
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }
    
    Data *data = read_data(argv[1]);
    // print_data(data);
    NeuralNetwork *network = init_neural_net(5);
    add_layer(network, RELU, 10);
    add_layer(network, RELU, 10);
    add_layer(network, RELU, 2);

    print_neural_net(network);
    train_neural_net(network, data);

    cleanup_neural_net(network);
    cleanup_data(data);
    return 0;
}