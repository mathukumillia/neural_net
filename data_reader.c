/**
 * data_reader.c
 *
 * Reads in raw data from the given filename and packages it in a Data struct.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data_reader.h"

Data *read_data(char *filename) {
    Data *data = (Data *) calloc(1, sizeof(Data));
    FILE *data_file = fopen(filename, "r");
    if (data_file == NULL) {
        fprintf(stderr, "Could not open file %s\n", filename);
        exit(1);
    }
    // the first line is the number of points
    assert(fscanf(data_file, "%d", &data->num_pts)); 
    // the second line is the dimensionality of the data
    assert(fscanf(data_file, "%d %d", &data->xdim, &data->ydim));
    // allocate the input and output arrays 
    data->xvals = (double **) calloc(data->num_pts, sizeof(double *));
    if (data->xvals == NULL) {
        fprintf(stderr, "Could not allocate input array in read_data.\n");
        exit(1);
    }
    data->yvals = (double **) calloc(data->num_pts, sizeof(double *));
    if (data->yvals == NULL) {
        fprintf(stderr, "Could not allocate output array in read_data.\n");
        exit(1);
    }

    // read each point into the appropriate array
    for (int i = 0; i < data->num_pts; i++){
        // allocate the x and y vectors
        data->xvals[i] = (double *) calloc(data->xdim, sizeof(double));
        if (data->xvals[i] == NULL) {
            fprintf(stderr, "Could not allocate input %d in read_data.\n", i);
            exit(1);
        }
        data->yvals[i] = (double *) calloc(data->ydim, sizeof(double));
        if (data->yvals[i] == NULL) {
            fprintf(stderr, "Could not allocate output %d in read_data.\n", i);
            exit(1);
        }
        // read in the elements of x
        for (int j = 0; j < data->xdim; j++) {
            assert(fscanf(data_file, "%lf", &data->xvals[i][j]));
        }

        // read in the elements of y
        for (int j = 0; j < data->ydim; j++) {
            assert(fscanf(data_file, "%lf", &data->yvals[i][j]));
        }
    }
    fclose(data_file);
    return data;
}


/**
 * print_data
 *
 * Prints the raw data to stdout. Useful for debugging.
 */
void print_data(Data *data) 
{
    printf("----------------------------------\n");
    printf("DATA\n");
    printf("----------------------------------\n");
    for(int i = 0; i < data->num_pts; i++) {
        printf("[");
        for (int j = 0; j < data->xdim; j++) {
            printf("%f ", data->xvals[i][j]);
        }
        printf("]\t\t");
        printf("[");
        for (int j = 0; j < data->ydim; j++) {
            printf("%f ", data->yvals[i][j]);
        }
        printf("]\n");
    }
}

/**
 * cleanup_data
 *
 * Cleans up all of the memory associated with the raw data xvals.
 */
void cleanup_data(Data *data)
{
    for (int i = 0; i < data->num_pts; i++) {
        free(data->xvals[i]);
        free(data->yvals[i]);
    }
    free(data->xvals);
    free(data->yvals);
    free(data);
}