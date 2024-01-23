extern "C" {
    #include "get_time.h"
}

#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE (1*1024*1024*1024)
#define ARRAY_ELEMENTS (ARRAY_SIZE/8)

#ifndef COPY_TIME
    #define COPY_TIME (0)
#endif

__global__ void triad(double* A, double* B, double* C, double c) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    A[x] = B[x] * c + C[x];
    return;
}

int main(int argc, char *argv[]) {
    uint64_t start = 0, stop = 0, actual_runtime = 0;

    // Allocate and initialize the arrays B and C in the CPU memory and then copy them into
    // the GPU memory
    double* B = (double *)malloc(ARRAY_SIZE);
    double* C = (double *)malloc(ARRAY_SIZE);

    for (int i = 0; i < ARRAY_ELEMENTS; i++) {
        B[i] = i + 0.5;
        C[i] = i + 0.75;
    }

    double* device_B;
    double* device_C;

    cudaMalloc((void**)&device_B, ARRAY_SIZE);
    cudaMalloc((void**)&device_C, ARRAY_SIZE);

    start = get_time_us();
    cudaMemcpy(device_B, B, ARRAY_SIZE, cudaMemcpyHostToDevice);
    cudaMemcpy(device_C, C, ARRAY_SIZE, cudaMemcpyHostToDevice);
    stop = get_time_us();
    #if COPY_TIME == 1
        actual_runtime += stop - start;
    #endif

    double* A = (double *)malloc(ARRAY_SIZE);
    double* device_A;
    cudaMalloc((void**)&device_A, ARRAY_SIZE);

    // Call your kernel function to run the STREAM Triad on the GPU
    start = get_time_us();
    triad<<<ARRAY_ELEMENTS/1024,1024>>>(device_A, device_B, device_C, 0.5);
    cudaDeviceSynchronize();
    stop = get_time_us();
    actual_runtime += stop - start;

    // Finally, copy array A from the device memory back to the host memory to verify the
    // correctness of your kernel implementation
    double* verify = (double *)malloc(ARRAY_SIZE);
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

    cudaFree(device_A);
    cudaFree(device_B);
    cudaFree(device_C);
    free(A);
    free(B);
    free(C);
    free(verify);

    double bandwidth = 3.0 * ARRAY_SIZE / actual_runtime;
    printf("bandwidth: %lf\n", bandwidth);

    return 0;
}
