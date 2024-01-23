extern "C" {
    #include "get_time.h"
}

#include <stdio.h>
#include <stdlib.h>

#ifndef COPY_TIME
    #define COPY_TIME (0)
#endif

#ifndef MIN_RUNTIME
    #define MIN_RUNTIME (100)
#endif

__global__ void update_grid(double* grid_source, double* grid_target, uint32_t dx, uint32_t dy) {
    // Switch the pointers for next iteration
	double* tmp = grid_source;
	grid_source = grid_target;
	grid_target = tmp;

    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    x++;
    y++;

    grid_target[y * dx + x] = grid_source[(y - 1) * dx + x] + grid_source[y * dx + (x - 1)];
    grid_target[y * dx + x] += grid_source[y * dx + (x + 1)] + grid_source[(y + 1) * dx + x];
    grid_target[y * dx + x] *= 0.25;

    return;
}

int main(int argc, char *argv[]) {
    uint64_t dx = strtold(argv[1], NULL);
	uint64_t dy = strtold(argv[2], NULL);

    uint64_t start = 0, stop = 0, actual_runtime = 0, runs = 0, runtime = 0;

    // Allocate and initialize the arrays B and C in the CPU memory and then copy them into
    // the GPU memory
    double* grid_source = (double *)malloc(dx * dy * sizeof(double));
    double* grid_target = (double *)malloc(dx * dy * sizeof(double));

    for (int y = 0; y < dy; y++) {
		for (int x = 0; x < dx; x++) {
			if (y == 0 || x == 0) {
				grid_source[y * dx + x] = 1.0;
				grid_target[y * dx + x] = 1.0;
			} else {
				grid_source[y * dx + x] = 0.0;
				grid_target[y * dx + x] = 0.0;
			}
		}
	}

    double* device_grid_source;
    double* device_grid_target;

    cudaMalloc((void**)&device_grid_source, dx * dy * sizeof(double));
    cudaMalloc((void**)&device_grid_target, dx * dy * sizeof(double));

    start = get_time_us();
    cudaMemcpy(device_grid_source, grid_source, dx * dy * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(device_grid_target, grid_target, dx * dy * sizeof(double), cudaMemcpyHostToDevice);
    stop = get_time_us();
    #if COPY_TIME == 1
        actual_runtime += stop - start;
    #endif

    // Measure for MIN_RUNTIME with 100 ms, 1s and 10s
    for (runs = 1u; runtime < MIN_RUNTIME; runs = runs << 1u) {
        // Call your kernel function to run jacobi on the GPU
        start = get_time_us();
        update_grid<<<(dx - 2) * (dy - 2) / 1024, 1024>>>(device_grid_source, device_grid_target, dx, dy);
        cudaDeviceSynchronize();
        stop = get_time_us();
        runtime = stop - start;
    }

    actual_runtime += runtime;

    // Finally, copy array A from the device memory back to the host memory to verify the
    // correctness of your kernel implementation
    double* verify = (double *)malloc(dx * dy * sizeof(double));
    for (runs = 1u; runtime < MIN_RUNTIME; runs = runs << 1u) {
        start = get_time_us();
        for (int y = 1; y < dy - 1; y++) {
            for (int x = 1; x < dx - 1; x++) {
                // Switch the pointers for next iteration
                double* tmp = grid_source;
                grid_source = verify;
                verify = tmp;

                verify[y * dx + x] = grid_source[(y - 1) * dx + x] + grid_source[y * dx + (x - 1)];
                verify[y * dx + x] += grid_source[y * dx + (x + 1)] + grid_source[(y + 1) * dx + x];
                verify[y * dx + x] *= 0.25;
            }
        }
        stop = get_time_us();
        runtime = stop - start;
    }

    start = get_time_us();
    cudaMemcpy(grid_target, device_grid_target, dx * dy * sizeof(double), cudaMemcpyDeviceToHost);
    stop = get_time_us();
    #if COPY_TIME == 1
        actual_runtime += stop - start;
    #endif

    for (int y = 1; y < dy - 1; y++) {
		for (int x = 1; x < dx - 1; x++) {
            if (verify[y * dx + x] != grid_target[y * dx + x]) {
                printf("verify: failed\n");
                return 1;
            }
        }
    }

    cudaFree(device_grid_source);
    cudaFree(device_grid_target);
    free(grid_source);
    free(grid_target);
    free(verify);

    double bandwidth = 3.0 * dx * dy * sizeof(double) / actual_runtime;
    printf("%d,%lf\n", MIN_RUNTIME, bandwidth);

    return 0;
}
