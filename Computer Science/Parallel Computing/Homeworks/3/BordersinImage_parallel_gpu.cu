#include <stdio.h>

#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include <opencv2/highgui/highgui.hpp>

using namespace cv;

__constant__ int k[2][3][3] = {
	{
		{-1, 0, 1},
		{-2, 0, 2},
		{-1, 0, 1}
	},
	{
		{-1, -2, -1},
		{0, 0, 0},
		{1, 2, 1}
	}
};

__global__ void Derivates(uchar* image, int* Dx, int* Dy, int imageW, int imageH, int N) 
{
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	int idy = blockIdx.y * blockDim.y + threadIdx.y;
	int index, index1;

	if (0 < idx && idx < imageW - 1 && 0 < idy && idy < imageH - 1)
	{
		index = (idy) * imageW + (idx);
		Dx[index] = 0;
		Dy[index] = 0;
		for (int k_i = -1; k_i < 2; k_i++)
		{
			for (int k_j = -1; k_j < 2; k_j++)
			{
				index1 = (idy + k_i) * imageW + (idx + k_j);
				Dx[index] += image[index1] * k[0][k_i + 1][k_j + 1];
				Dy[index] += image[index1] * k[1][k_i + 1][k_j + 1];
			}
		}
	}
}

__global__ void BordersinImage(int* Dx, int* Dy, uchar* MG, uchar* MGT, int imageW, int imageH, int N)
{
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	int idy = blockIdx.y * blockDim.y + threadIdx.y;
	int index = (idy)*imageW + (idx);

	if (0 < idx && idx < imageW - 1 && 0 < idy < imageH - 1)
		MG[index] = fminf(sqrtf(Dx[index] * Dx[index] + Dy[index] * Dy[index]), 255);
	else if (0 <= idx && idx < imageW && 0 <= idy && idy < imageH)
		MG[index] = 0;
	MGT[index] = (MG[index] > 255 / 2 ? 255 : 0);
}

int divUp(int a, int b) {
	return (a + b - 1) / b;
}

int main() {
	
	cudaSetDevice(0);
	
	Mat frame = imread("./pinzas_gray.png", IMREAD_GRAYSCALE), frameMG, frameMGT;

	int imageW = frame.cols, imageH = frame.rows, N = imageW * imageH;

	// Crear memoria en la GPU
	uchar* image, * MG, * MGT;
	int* Dx, * Dy;
	cudaMalloc((void**)&image, N * sizeof(uchar));
	cudaMalloc((void**)&Dx, N * sizeof(int));
	cudaMalloc((void**)&Dy, N * sizeof(int));
	cudaMalloc((void**)&MG, N * sizeof(uchar));
	cudaMalloc((void**)&MGT, N * sizeof(uchar));

	cudaMemcpy(image, frame.data, N * sizeof(uchar), cudaMemcpyHostToDevice);

	dim3 threads(16, 16, 1), grid(divUp(imageW, 16), divUp(imageH, 16), 1);

	Derivates <<< grid, threads >>> (image, Dx, Dy, imageW, imageH, N);
	cudaDeviceSynchronize();
	BordersinImage <<< grid, threads >>> (Dx, Dy, MG, MGT, imageW, imageH, N);
	cudaDeviceSynchronize();

	frameMG.create(imageH, imageW, CV_8UC(1));
	frameMGT.create(imageH, imageW, CV_8UC(1));
	cudaMemcpy(frameMG.data, MG, N * sizeof(uchar), cudaMemcpyDeviceToHost);
	cudaMemcpy(frameMGT.data, MGT, N * sizeof(uchar), cudaMemcpyDeviceToHost);
	imshow("MG", frameMG);
	imshow("MGT", frameMGT);
	waitKey(0);

	frameMG.release();
	frameMGT.release();

	cudaFree(image);
	cudaFree(Dx);
	cudaFree(Dy);
	cudaFree(MG);
	cudaFree(MGT);

	return 0;
}