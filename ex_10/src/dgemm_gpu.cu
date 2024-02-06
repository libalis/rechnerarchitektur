extern "C" {
    #include "get_time.h"
}

#include <cublas_v2.h>
#include <curand.h>
#include <stdio.h>
#include <stdlib.h>

#include "get_time.h"

// Fill the array A(nr_rows_A, nr_cols_A) with random numbers on GPU
void GPU_fill_rand(double *A, int nr_rows_A, int nr_cols_A) {
    // Create a pseudo-random number generator
    curandGenerator_t prng;
    curandCreateGenerator(&prng, CURAND_RNG_PSEUDO_DEFAULT);

    // Set the seed for the random number generator using the system clock
    curandSetPseudoRandomGeneratorSeed(prng, (unsigned long long) clock());

    // Fill the array with random numbers on the device
    curandGenerateUniformDouble(prng, A, nr_rows_A * nr_cols_A);
}

// Multiply the arrays A and B on GPU and save the result in C
// C(m,n) = A(m,k) * B(k,n)
void gpu_blas_mmul(const double *A, const double *B, double *C, const int m, const int k, const int n) {
    int lda=m,ldb=k,ldc=m;
    const double alf = 1;
    const double bet = 0;
    const double *alpha = &alf;
    const double *beta = &bet;

    // Create a handle for CUBLAS
    cublasHandle_t handle;
    cublasCreate(&handle);

    // Do the actual multiplication
    cublasDgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc);

    // Destroy the handle
    cublasDestroy(handle);
}

//Print matrix A(nr_rows_A, nr_cols_A) storage in column-major format
/*void print_matrix(const double *A, int nr_rows_A, int nr_cols_A) {
    for(int i = 0; i < nr_rows_A; ++i){
        for(int j = 0; j < nr_cols_A; ++j){
            std::cout << A[j * nr_rows_A + i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}*/

int main(int argc, char *argv[]) {
    // Allocate 3 arrays on CPU
    int nr_rows_A, nr_cols_A, nr_rows_B, nr_cols_B, nr_rows_C, nr_cols_C;

    // for simplicity we are going to use square arrays
    nr_rows_A = nr_cols_A = nr_rows_B = nr_cols_B = nr_rows_C = nr_cols_C = strtold(argv[1], NULL);

    double *h_A = (double *)malloc(nr_rows_A * nr_cols_A * sizeof(double));
    double *h_B = (double *)malloc(nr_rows_B * nr_cols_B * sizeof(double));
    double *h_C = (double *)malloc(nr_rows_C * nr_cols_C * sizeof(double));

    // Allocate 3 arrays on GPU
    double *d_A, *d_B, *d_C;
    cudaMalloc(&d_A,nr_rows_A * nr_cols_A * sizeof(double));
    cudaMalloc(&d_B,nr_rows_B * nr_cols_B * sizeof(double));
    cudaMalloc(&d_C,nr_rows_C * nr_cols_C * sizeof(double));

    // Fill the arrays A and B on GPU with random numbers
    GPU_fill_rand(d_A, nr_rows_A, nr_cols_A);
    GPU_fill_rand(d_B, nr_rows_B, nr_cols_B);

    // Optionally we can copy the data back on CPU and print the arrays
    /*cudaMemcpy(h_A,d_A,nr_rows_A * nr_cols_A * sizeof(double),cudaMemcpyDeviceToHost);
    cudaMemcpy(h_B,d_B,nr_rows_B * nr_cols_B * sizeof(double),cudaMemcpyDeviceToHost);
    std::cout << "A =" << std::endl;
    print_matrix(h_A, nr_rows_A, nr_cols_A);
    std::cout << "B =" << std::endl;
    print_matrix(h_B, nr_rows_B, nr_cols_B);*/

    // Multiply A and B on GPU

    uint64_t start = get_time_us();

    gpu_blas_mmul(d_A, d_B, d_C, nr_rows_A, nr_cols_A, nr_cols_B);

    uint64_t runtime = get_time_us() - start;
    printf("floating-point performance: %lf\n", 2.0 * nr_rows_A * nr_rows_A * nr_rows_A / runtime * 1000000);

    // Copy (and print) the result on host memory
    /*cudaMemcpy(h_C,d_C,nr_rows_C * nr_cols_C * sizeof(double),cudaMemcpyDeviceToHost);
    std::cout << "C =" << std::endl;
    print_matrix(h_C, nr_rows_C, nr_cols_C);*/

    //Free GPU memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    // Free CPU memory
    free(h_A);
    free(h_B);
    free(h_C);

    return 0;
}
