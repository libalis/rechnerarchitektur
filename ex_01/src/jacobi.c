#define _POSIX_C_SOURCE 199309L
#include "jacobi.h"

void jacobi(double* grid_source, double* grid_target, uint32_t x, uint32_t y) {
	// TODO implement
	// Update cells
	for (uint32_t dy = 1; dy < y - 1; dy++) {
		for (uint32_t dx = 1; dx < x - 1; dx++) {
			grid_target[dy * x + dx] = grid_source[(dy - 1) * x + dx] + grid_source[dy * x + (dx - 1)]
			grid_target[dy * x + dx] += grid_source[dy * x + (dx + 1)] + grid_source[(dy + 1) * x + dx];
			grid_target /= 4;
		}
	}
	// Switch the pointers for next iteration
	double* tmp = grid_source;
	grid_source = grid_target;
	grid_target = tmp;
}
