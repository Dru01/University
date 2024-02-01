#include <stdio.h>
#include <stdlib.h> 
#include <omp.h>
#include <math.h>
#include <time.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#define ll long long

__global__ void mat_prod(double *A, double *B, double *C, int N, int K, int M)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
	int idy = blockIdx.y * blockDim.y + threadIdx.y;
	int index = (idy)*M + (idx);
    C[index] = 0.0;
    for (int k = 0; k < K; k++)
        C[index] += A[idy * K + k] * B[idx * K + k];
}

int divUp(int a, int b) {
    return (a + b - 1) / b;
}

int main()
{
    ll N = 1e4, K = 1e3, M = 1e3;

    double* A = (double*)malloc(N * K * sizeof(double)), * B = (double*)malloc(M * K * sizeof(double)), * C = (double*)malloc(N * M * sizeof(double));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < K; j++)
            A[i * K + j] = i * K + j;

    for (int i = 0; i < M; i++)
        for (int j = 0; j < K; j++)
            B[i * K + j] = i * K + j;

    double* A_device, * B_device, * C_device;
    cudaMalloc((void**)&A_device, N * K * sizeof(double));
	cudaMalloc((void**)&B_device, M * K * sizeof(double));
	cudaMalloc((void**)&C_device, N * M * sizeof(double));
	cudaMemcpy(A_device, A, N * K * sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(B_device, B, M * K * sizeof(double), cudaMemcpyHostToDevice);

    clock_t t;
	t = clock();

	dim3 threads(16, 16, 1), grid(divUp(M, 16), divUp(N, 16), 1);
	mat_prod <<< grid, threads >>> (A_device, B_device, C_device, N, K, M);
	cudaDeviceSynchronize();
	
	t = clock() - t;

	cudaMemcpy(C, C_device, N * M* sizeof(double), cudaMemcpyDeviceToHost);

	cudaFree(A_device);
	cudaFree(B_device);
	cudaFree(C_device);
	free(A);
	free(B);
	free(C);

	printf("%f", ((double)t) / CLOCKS_PER_SEC);
    return 0;
}