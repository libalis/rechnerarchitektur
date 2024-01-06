#include "barrier.h"
#include "draw.h"
#include "get_time.h"
#include "jacobi.h"
#include <inttypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef THREADS
	#define THREADS (1)
#endif

// Struct containing all parameters for a thread
typedef struct work_package_s {
	double* grid_source;
	double* grid_target;
	uint64_t dx;
	uint64_t dy;
	uint64_t runs;
	uint64_t i;
} work_package_s;

static void usage_msg(void) {
	fprintf(stderr, "Usage: ./jacobi <dx> <dy>\n");
	return;
}

int y_range[THREADS + 1];

void linspace(int a, int b, int n) {
	int c, i;
	/* make sure number of points and array are valid */
	if (n < 2 || y_range == 0) {
		if (n == 1) {
			y_range[0] = a;
			y_range[1] = b;
		}
		return;
	}
	/* step size */
	c = (b - a)/(n - 1);
	if (c == 0) c = 1;
	/* fill vector */
	for (i = 0; i < n - 1; i++) y_range[i] = a + i * c;
	/* fix last entry to b */
	y_range[n - 1] = b;
}

// Function to be executed by each thread
void* worker_thread(void* void_args) {
	work_package_s* args = (work_package_s*) void_args;
	for (uint64_t i = 0; i < args->runs; i++) {
		jacobi_subgrid(args->grid_source, args->grid_target,args->dx, args->dy, y_range[args->i], y_range[args->i + 1]);
		sync_barrier(THREADS);
		// TODO swap
		double* tmp = args->grid_source;
		args->grid_source = args->grid_target;
		args->grid_target = tmp;
	}
	pthread_exit(NULL);
}

void* dummy_thread(void* void_args) {
	pthread_exit(NULL);
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

	// Create thread arguments
	work_package_s pkgs[THREADS - 1];
	linspace(0, dy, THREADS + 1);
	// for loop to initialize pkgs
	for (int i = 0; i < THREADS - 1; i++) pkgs[i] = (work_package_s){grid_source, grid_target, dx, dy, 0u, i};

	for(runs = 1u; actual_runtime < minimal_runtime; runs = runs << 1u) {
		start = get_time_us();
		pthread_t dummy_tid;
		if (runs >= 2) pthread_create(&dummy_tid, NULL, dummy_thread, NULL);
		pthread_t tid[THREADS - 1];
		for (int i = 0; i < THREADS - 1; i++) {
			pkgs[i].runs = runs;
			pthread_create(&tid[i], NULL, worker_thread, &pkgs[i]);
		}
		for(uint64_t i = 0u; i < runs; i++) {
			jacobi_subgrid(grid_source, grid_target, dx, dy, y_range[THREADS - 1], y_range[THREADS]);
			sync_barrier(THREADS);
			// Switch the pointers for next iteration
			double* tmp = grid_source;
			grid_source = grid_target;
			grid_target = tmp;
		}
		if (runs >= 2) pthread_join(dummy_tid, NULL);
		for (int i = 0; i < THREADS - 1; i++) {
			pthread_join(tid[i], NULL);
		}
		// Draw
		// if (access("result.ppm", F_OK) != 0) draw_grid(grid_source, dx, dy, "result.ppm");
		stop  = get_time_us();
		actual_runtime = stop - start;
	}

	//TODO: calculate and print
	mega_updates_per_second = ((runs>>1u)*((dy-2)*(dx-2)))/(double)actual_runtime;
	fprintf(stdout, "%d,%lf,%" PRIu64 "\n", THREADS, mega_updates_per_second, actual_runtime);

	_mm_free(grid_source);
	_mm_free(grid_target);
	return 0;
}
