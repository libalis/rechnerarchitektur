#include "draw.h"
#include "get_time.h"
#include "jacobi.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void usage_msg(void) {
	fprintf(stderr, "Usage: ./jacobi <dx> <dy>\n");
	return;
}

int main(int argc, char *argv[]) {
	uint64_t minimal_runtime  = 0u;
	uint64_t actual_runtime   = 0u;
	uint64_t dx = 0u;  // width
	uint64_t dy = 0u;  // height
	uint64_t runs             = 0u;
	uint64_t start            = 0u;
	uint64_t stop             = 0u;
	double   mega_updates_per_second  = 0u;

	if(argc != 3 || argv == NULL) {
		usage_msg();
		return -1;
	}

	//TODO: parse parameter: width and height
	dx = strtold(argv[1], NULL);
	dy = strtold(argv[2], NULL);

	//TODO: allocate memory and initialize it
	double *grid_source = _mm_malloc(dx * dy * sizeof(double), 64);
	double *grid_target = _mm_malloc(dx * dy * sizeof(double), 64);

	for (int y = 0; y < dy; y++) {
		for (int x = 0; x < dx; x++) {
			if (y == 0 || x == 0) {
				grid_source[dx * y + x] = 1.0;
				grid_target[dx * y + x] = 1.0;
			} else {
				grid_source[dx * y + x] = 0.0;
				grid_target[dx * y + x] = 0.0;
			}
		}
	}

	//TODO: measurement with a runtime of at least 1 s
	minimal_runtime = 1 * 1000000;

	for(runs = 1u; actual_runtime < minimal_runtime; runs = runs << 1u) {
		start = get_time_us();
		for(uint64_t i = 0u; i < runs; i++) {
			// TODO
			jacobi(grid_source, grid_target, dx, dy);
			// Switch the pointers for next iteration
			double* tmp = grid_source;
			grid_source = grid_target;
			grid_target = tmp;
			// Draw
			if (access("result.ppm", F_OK) != 0) draw_grid(grid_source, dx, dy, "result.ppm");
		}
		stop  = get_time_us();
		actual_runtime = stop - start;
	}

	//TODO: calculate and print
	mega_updates_per_second = ((runs>>1u)*((dy-2)*(dx-2)))/(double)actual_runtime;
	fprintf(stdout, "%" PRIu64 ",%lf,%" PRIu64 "\n", dx, mega_updates_per_second, actual_runtime);

	_mm_free(grid_source);
	_mm_free(grid_target);
	return 0;
}
