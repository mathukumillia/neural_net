/**
 * data_reader.h
 *
 * Contains useful structs and functions to read raw data from a file.
 */
#pragma once

typedef struct data {
    double **xvals;
    double **yvals;
    int num_pts;
    int xdim;
    int ydim;
} Data;

Data *read_data(char *);
void print_data(Data *);
void cleanup_data(Data *);