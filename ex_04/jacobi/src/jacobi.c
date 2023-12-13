#define _POSIX_C_SOURCE 199309L
#include <immintrin.h>
#include "jacobi.h"

#ifndef NUMBER
	#define NUMBER (0)
#endif

void jacobi(double* grid_source, double* grid_target, uint32_t x, uint32_t y) {
	// TODO implement
	// Update cells
	#if NUMBER == 0
		for (uint32_t dy = 1; dy < y - 1; dy++) {
			#pragma novector
			#pragma nounroll
			for (uint32_t dx = 1; dx < x - 1; dx++) {
				grid_target[dy * x + dx] = grid_source[(dy - 1) * x + dx] + grid_source[dy * x + (dx - 1)];
				grid_target[dy * x + dx] += grid_source[dy * x + (dx + 1)] + grid_source[(dy + 1) * x + dx];
				grid_target[dy * x + dx] *= 0.25;
			}
		}
	#elif NUMBER == 2
		for (uint32_t dx = 1; dx < x - 1; dx++) {
			#pragma novector
			#pragma nounroll
			for (uint32_t dy = 1; dy < y - 1; dy++) {
				grid_target[dy * x + dx] = grid_source[(dy - 1) * x + dx] + grid_source[dy * x + (dx - 1)];
				grid_target[dy * x + dx] += grid_source[dy * x + (dx + 1)] + grid_source[(dy + 1) * x + dx];
				grid_target[dy * x + dx] *= 0.25;
			}
		}
	#endif
}