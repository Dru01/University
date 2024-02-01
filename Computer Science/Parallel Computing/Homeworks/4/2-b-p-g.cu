#include <stdio.h>
#include <stdlib.h> 
#include <omp.h>
#include <math.h>
#include <time.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#define ll long long

__global__ void Solve(double *A, double *B, double *C, double alpha, int N, int M) {
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	int idy = blockIdx.y * blockDim.y + threadIdx.y;
	int index = (idy)*M + (idx);
	int index1 = (N - 1 - idy) * M + (M - 1 - idx);
	if (index < N*M) {
		C[index] = (alpha)*A[index] + (1-alpha)*B[index1];
	}
}

int divUp(int a, int b) {
	return (a + b - 1) / b;
}

int main() {

	cudaSetDevice(0);

	ll N = (ll)1e4, M = (ll)1e4;

	double* A = (double*)malloc(N * M * sizeof(double)), * B = (double*)malloc(N * M * sizeof(double)), * C = (double*)malloc(N * M * sizeof(double));
	double alpha = 0.5;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			A[i * M + j] = 1.0;
			B[i * M + j] = i * M + j;
		}
	}

	double* A_device, * B_device, * C_device;
	cudaMalloc((void**)&A_device, N * M * sizeof(double));
	cudaMalloc((void**)&B_device, N * M * sizeof(double));
	cudaMalloc((void**)&C_device, N * M * sizeof(double));
	cudaMemcpy(A_device, A, N * M * sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(B_device, B, N * M * sizeof(double), cudaMemcpyHostToDevice);

	clock_t t;
	t = clock();

	dim3 threads(16, 16, 1), grid(divUp(M, 16), divUp(N, 16), 1);
	Solve <<< grid, threads >>> (A_device, B_device, C_device, alpha, N, M);
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