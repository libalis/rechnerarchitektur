#ifndef JACOBI_H
#define JACOBI_H

#include <stdint.h>

/* This function iterates over a grid to perform a jacobi time step.
 */
void jacobi_subgrid(double* grid_source, double* grid_target, uint32_t x, uint32_t y, uint32_t y_min, uint32_t y_max);

#endif
