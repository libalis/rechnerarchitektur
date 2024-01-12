#include "get_time.h"
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE (1*1024*1024*1024)
#define ARRAY_ELEMENTS (ARRAY_SIZE/8)

#ifndef COPY_TIME
    #define COPY_TIME (0)
#endif

__global__ void triad(double* A, double* B, double* C, double c, int n, uint64_t actual_runtime) {
    uint64_t start = get_time_us();

    for (int i = 0; i < n; ++i) {
        A[i] = B[i] * c + C[i];
    }

    // Measure solely the kernel execution time and calculate the bandwidth
    uint64_t stop = get_time_us();
    actual_runtime += stop - start;
    double bandwidth = 3.0 * ARRAY_SIZE / actual_runtime;
    printf("bandwidth: %lf\n", bandwidth);
}

int main(int argc, char *argv[]) {
    uint64_t actual_runtime = 0;

    // Allocate and initialize the arrays B and C in the CPU memory and then copy them into
    // the GPU memory
    double* B = _mm_malloc(ARRAY_SIZE, 64);
    double* C = _mm_malloc(ARRAY_SIZE, 64);

    for (int i = 0; i < ARRAY_ELEMENTS; i++) {
        B[i] = i + 0.5;
        C[i] = i + 0.75;
    }

    double* device_B;
    double* device_C;

    cudaMalloc((void**)&device_B, ARRAY_SIZE);
    cudaMalloc((void**)&device_C, ARRAY_SIZE);

    uint64_t start = get_time_us();
    cudaMemcpy(device_B, B, ARRAY_SIZE, cudaMemcpyHostToDevice);
    cudaMemcpy(device_C, C, ARRAY_SIZE, cudaMemcpyHostToDevice);
    uint64_t stop = get_time_us();
    #if COPY_TIME == 1
        actual_runtime += stop - start;
    #endif

    double* A = _mm_malloc(ARRAY_SIZE, 64);
    double* device_A;
    cudaMalloc((void**)&device_A, ARRAY_SIZE);

    // Call your kernel function to run the STREAM Triad on the GPU
    triad<<<1,1>>>(device_A, device_B, device_C, 0.5, ARRAY_ELEMENTS, actual_runtime);

    cudaDeviceSynchronize();

    // Finally, copy array A from the device memory back to the host memory to verify the
    // correctness of your kernel implementation
    double* verify = _mm_malloc(ARRAY_SIZE, 64);
    for (int i = 0; i < ARRAY_ELEMENTS; ++i) {
        verify[i] = B[i] * 0.5 + C[i];
    }

    start = get_time_us();
    cudaMemcpy(A, device_A, ARRAY_SIZE, cudaMemcpyDeviceToHost);
    stop = get_time_us();
    #if COPY_TIME == 1
        actual_runtime += stop - start;
    #endif

    for (int i = 0; i < ARRAY_ELEMENTS; ++i) {
        if (verify[i] != A[i]) {
            printf("verify: failed\n");
            return 1;
        }
    }

    _mm_free(A);
    _mm_free(B);
    _mm_free(C);
    cudaFree(device_A);
    cudaFree(device_B);
    cudaFree(device_C);

    return 0;
}
