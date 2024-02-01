#include <stdio.h>
#include <stdlib.h> 
#include <omp.h>
#include <math.h>
#include <time.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#define ll long long

__global__ void Solve(long double *v, long double *v_1, int N) {
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if (idx < N) {
		v_1[idx] = v[idx] + v[idx + 1];
	}
}

int divUp(int a, int b) {
	return (a + b - 1) / b;
}

int main() {

	cudaSetDevice(0);

	ll N = (ll)1e7;

	long double* v = (long double*)malloc(N * sizeof(long double));
	long double* v_1 = (long double*)malloc((N - 1) * sizeof(long double));

	for (int i = 0; i < N; i++)
		v[i] = (long double)i / exp(1);

	long double* v_device,* v_1_device;
	cudaMalloc((void**)&v_device, N * sizeof(long double));
	cudaMalloc((void**)&v_1_device, (N-1) * sizeof(long double));
	cudaMemcpy(v_device, v, N * sizeof(long double), cudaMemcpyHostToDevice);

	clock_t t;
	t = clock();

	int threads = 512, grid = divUp(N, threads);
	Solve <<< grid, threads >>> (v_device, v_1_device, N);
	cudaDeviceSynchronize();
	
	t = clock() - t;

	cudaFree(v_device);
	cudaFree(v_1_device);
	free(v);
	free(v_1);

	printf("%f", ((long double)t) / CLOCKS_PER_SEC);

	return 0;
}