#define _POSIX_C_SOURCE 199309L
#include <immintrin.h>
#include "jacobi.h"

#ifndef NUMBER
	#define NUMBER (0)
#endif

#define BX 6000

void jacobi(double* grid_source, double* grid_target, uint32_t x, uint32_t y) {
	// TODO implement
	// Update cells
	#if NUMBER == 0
	for (uint32_t dy = 1; dy < y-1; dy++) {
		uint32_t remainder = (x-2) % 4;
		#pragma novector
		#pragma nounroll
		for (uint32_t dx = 1; dx < x-remainder-1; dx+=4) {
			__m256d result = _mm256_setzero_pd();
			__m256d accu = _mm256_loadu_pd(&grid_source[(dy - 1) * x + dx]);
			result = _mm256_add_pd(result, accu);
			accu = _mm256_loadu_pd(&grid_source[dy * x + (dx - 1)]);
			result = _mm256_add_pd(result, accu);
			accu = _mm256_loadu_pd(&grid_source[dy * x + (dx + 1)]);
			result = _mm256_add_pd(result, accu);
			accu = _mm256_loadu_pd(&grid_source[(dy + 1) * x + dx]);
			result = _mm256_add_pd(result, accu);
			accu = _mm256_set1_pd(0.25);
			result = _mm256_mul_pd(result, accu);
			_mm256_storeu_pd(&grid_target[dy * x + dx], result);
		}
		if (remainder >= 1) {
			grid_target[dy * x + x-2] = grid_source[(dy - 1) * x + (x-2)] + grid_source[dy * x + (x-2)];
			grid_target[dy * x + x-2] += grid_source[dy * x + (x-2)] + grid_source[(dy + 1) * x + (x-2)];
			grid_target[dy * x + x-2] *= 0.25;
		}
		if (remainder >= 2) {
			grid_target[dy * x + x-3] = grid_source[(dy - 1) * x + (x-3)] + grid_source[dy * x + (x-3)];
			grid_target[dy * x + x-3] += grid_source[dy * x + (x-3)] + grid_source[(dy + 1) * x + (x-3)];
			grid_target[dy * x + x-3] *= 0.25;
		}
		if (remainder == 3) {
			grid_target[dy * x + x-4] = grid_source[(dy - 1) * x + (x-4)] + grid_source[dy * x + (x-4)];
			grid_target[dy * x + x-4] += grid_source[dy * x + (x-4)] + grid_source[(dy + 1) * x + (x-4)];
			grid_target[dy * x + x-4] *= 0.25;
		}
	}
	#elif NUMBER == 1
	uint32_t remainder = (x-2) % 4;
	uint32_t condition = x/BX+1;
	for (uint32_t ib = 0; ib < condition; ib++) {
		for (uint32_t dy = 1; dy < y-1; dy++) {
			#pragma novector
			#pragma nounroll
			for (uint32_t dx = ib*BX+1; dx < (ib+1)*BX+1 && dx < x-4; dx+=4) {
				__m256d result = _mm256_setzero_pd();
				__m256d accu = _mm256_loadu_pd(&grid_source[(dy - 1) * x + dx]);
				result = _mm256_add_pd(result, accu);
				accu = _mm256_loadu_pd(&grid_source[dy * x + (dx - 1)]);
				result = _mm256_add_pd(result, accu);
				accu = _mm256_loadu_pd(&grid_source[dy * x + (dx + 1)]);
				result = _mm256_add_pd(result, accu);
				accu = _mm256_loadu_pd(&grid_source[(dy + 1) * x + dx]);
				result = _mm256_add_pd(result, accu);
				accu = _mm256_set1_pd(0.25);
				result = _mm256_mul_pd(result, accu);
				_mm256_storeu_pd(&grid_target[dy * x + dx], result);
			}
		}
	}
	if (remainder >= 1) {
		for (uint32_t dy = 1; dy < y-1; dy++) {
			grid_target[dy * x + x-2] = grid_source[(dy - 1) * x + (x-2)] + grid_source[dy * x + (x-2)];
			grid_target[dy * x + x-2] += grid_source[dy * x + (x-2)] + grid_source[(dy + 1) * x + (x-2)];
			grid_target[dy * x + x-2] *= 0.25;
		}
	}
	if (remainder >= 2) {
		for (uint32_t dy = 1; dy < y-1; dy++) {
			grid_target[dy * x + x-3] = grid_source[(dy - 1) * x + (x-3)] + grid_source[dy * x + (x-3)];
			grid_target[dy * x + x-3] += grid_source[dy * x + (x-3)] + grid_source[(dy + 1) * x + (x-3)];
			grid_target[dy * x + x-3] *= 0.25;
		}
	}
	if (remainder == 3) {
		for (uint32_t dy = 1; dy < y-1; dy++) {
			grid_target[dy * x + x-4] = grid_source[(dy - 1) * x + (x-4)] + grid_source[dy * x + (x-4)];
			grid_target[dy * x + x-4] += grid_source[dy * x + (x-4)] + grid_source[(dy + 1) * x + (x-4)];
			grid_target[dy * x + x-4] *= 0.25;
		}
	}
	#endif
}
