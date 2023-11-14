#define _POSIX_C_SOURCE 199309L
#include "jacobi.h"

#ifndef NUMBER
	#define NUMBER (0)
#endif

void jacobi(double* grid_source, double* grid_target, uint32_t x, uint32_t y) {
	// TODO implement
	// Update cells
	for (uint32_t dy = 1; dy < y - 1; dy++) {
		#if NUMBER == 0
			#pragma novector
			#pragma nounroll
			for (uint32_t dx = 1; dx < x - 1; dx++) {
				grid_target[dy * x + dx] = grid_source[(dy - 1) * x + dx] + grid_source[dy * x + (dx - 1)];
				grid_target[dy * x + dx] += grid_source[dy * x + (dx + 1)] + grid_source[(dy + 1) * x + dx];
				grid_target[dy * x + dx] *= 0.25;
			}
		}
		#elif NUMBER == 2
			uint32_t remainder = (x-1) % 2;
			#pragma novector
			#pragma nounroll
			for (int dx = 1; dx < x-remainder-1; dx+=2) {
				grid_target[dy * x + dx] = grid_source[(dy - 1) * x + dx] + grid_source[dy * x + (dx - 1)];
				grid_target[dy * x + dx] += grid_source[dy * x + (dx + 1)] + grid_source[(dy + 1) * x + dx];
				grid_target[dy * x + dx] *= 0.25;

				grid_target[dy * x + dx+1] = grid_source[(dy - 1) * x + (dx+1)] + grid_source[dy * x + (dx+1 - 1)];
				grid_target[dy * x + dx+1] += grid_source[dy * x + (dx+1 + 1)] + grid_source[(dy + 1) * x + (dx+1)];
				grid_target[dy * x + dx+1] *= 0.25;
			}
			if(remainder) {
				grid_target[dy * x + x-2] = grid_source[(dy - 1) * x + (x-2)] + grid_source[dy * x + (x-2)];
				grid_target[dy * x + x-2] += grid_source[dy * x + (x-2)] + grid_source[(dy + 1) * x + (x-2)];
				grid_target[dy * x + x-2] *= 0.25;
			}
		#elif NUMBER == 4
			uint32_t remainder = (x-1) % 4;
			#pragma novector
			#pragma nounroll
			for (int dx = 1; dx < x-remainder-1; dx+=4) {
				grid_target[dy * x + dx] = grid_source[(dy - 1) * x + dx] + grid_source[dy * x + (dx - 1)];
				grid_target[dy * x + dx] += grid_source[dy * x + (dx + 1)] + grid_source[(dy + 1) * x + dx];
				grid_target[dy * x + dx] *= 0.25;

				grid_target[dy * x + dx+1] = grid_source[(dy - 1) * x + (dx+1)] + grid_source[dy * x + (dx+1 - 1)];
				grid_target[dy * x + dx+1] += grid_source[dy * x + (dx+1 + 1)] + grid_source[(dy + 1) * x + (dx+1)];
				grid_target[dy * x + dx+1] *= 0.25;

				grid_target[dy * x + dx+2] = grid_source[(dy - 1) * x + (dx+2)] + grid_source[dy * x + (dx+2 - 1)];
				grid_target[dy * x + dx+2] += grid_source[dy * x + (dx+2 + 1)] + grid_source[(dy + 1) * x + (dx+2)];
				grid_target[dy * x + dx+2] *= 0.25;

				grid_target[dy * x + dx+3] = grid_source[(dy - 1) * x + (dx+3)] + grid_source[dy * x + (dx+3 - 1)];
				grid_target[dy * x + dx+3] += grid_source[dy * x + (dx+3 + 1)] + grid_source[(dy + 1) * x + (dx+3)];
				grid_target[dy * x + dx+3] *= 0.25
			}
			if(remainder == 1) {
				grid_target[dy * x + x-2] = grid_source[(dy - 1) * x + (x-2)] + grid_source[dy * x + (x-2)];
				grid_target[dy * x + x-2] += grid_source[dy * x + (x-2)] + grid_source[(dy + 1) * x + (x-2)];
				grid_target[dy * x + x-2] *= 0.25;
			}
			else if(remainder == 2) {
				grid_target[dy * x + x-2] = grid_source[(dy - 1) * x + (x-2)] + grid_source[dy * x + (x-2)];
				grid_target[dy * x + x-2] += grid_source[dy * x + (x-2)] + grid_source[(dy + 1) * x + (x-2)];
				grid_target[dy * x + x-2] *= 0.25;

				grid_target[dy * x + x-3] = grid_source[(dy - 1) * x + (x-3)] + grid_source[dy * x + (x-3)];
				grid_target[dy * x + x-3] += grid_source[dy * x + (x-3)] + grid_source[(dy + 1) * x + (x-3)];
				grid_target[dy * x + x-3] *= 0.25;
			}
			else if(remainder == 3) {
				grid_target[dy * x + x-2] = grid_source[(dy - 1) * x + (x-2)] + grid_source[dy * x + (x-2)];
				grid_target[dy * x + x-2] += grid_source[dy * x + (x-2)] + grid_source[(dy + 1) * x + (x-2)];
				grid_target[dy * x + x-2] *= 0.25;

				grid_target[dy * x + x-3] = grid_source[(dy - 1) * x + (x-3)] + grid_source[dy * x + (x-3)];
				grid_target[dy * x + x-3] += grid_source[dy * x + (x-3)] + grid_source[(dy + 1) * x + (x-3)];
				grid_target[dy * x + x-3] *= 0.25;

				grid_target[dy * x + x-4] = grid_source[(dy - 1) * x + (x-4)] + grid_source[dy * x + (x-4)];
				grid_target[dy * x + x-4] += grid_source[dy * x + (x-4)] + grid_source[(dy + 1) * x + (x-4)];
				grid_target[dy * x + x-4] *= 0.25;
			}
		#endif
}
