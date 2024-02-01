#include <stdio.h>

#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include <opencv2/highgui/highgui.hpp>

using namespace cv;

__global__ void AlphaMatting(uchar3* image_source_1, uchar3* image_source_2, uchar* image_mask, uchar3* image_result, int N) {
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if (idx < N) {
		int alpha = (image_mask[idx] > 255 / 2) ? 1 : 0;
		image_result[idx].x = image_source_1[idx].x * alpha + (1 - alpha) * image_source_2[idx].x;
		image_result[idx].y = image_source_1[idx].y * alpha + (1 - alpha) * image_source_2[idx].y;
		image_result[idx].z = image_source_1[idx].z * alpha + (1 - alpha) * image_source_2[idx].z;
	}
}

int divUp(int a, int b) {
	return (a + b - 1) / b;
}

int main() {
	
	cudaSetDevice(0);
	
	Mat frame_source_1 = imread("./greenScreen.jpg", IMREAD_COLOR),
		frame_source_2 = imread("./fondo.bmp", IMREAD_COLOR),
		frame_mask = imread("./greenscreenMask.bmp", IMREAD_GRAYSCALE),
		frame_result;

	int imageW = frame_source_1.cols, imageH = frame_source_1.rows, N = imageW * imageH;

	uchar3* image_source_1, * image_source_2, * image_result;
	uchar* image_mask;
	cudaMalloc((void**)&image_source_1, N * sizeof(uchar3));
	cudaMalloc((void**)&image_source_2, N * sizeof(uchar3));
	cudaMalloc((void**)&image_result, N * sizeof(uchar3));
	cudaMalloc((void**)&image_mask, N * sizeof(uchar));
	cudaMemcpy(image_source_1, frame_source_1.data, N * sizeof(uchar3), cudaMemcpyHostToDevice);
	cudaMemcpy(image_source_2, frame_source_2.data, N * sizeof(uchar3), cudaMemcpyHostToDevice);
	cudaMemcpy(image_mask, frame_mask.data, N * sizeof(uchar), cudaMemcpyHostToDevice);

	int threads = 512, grid = divUp(N, threads);

	AlphaMatting <<< grid, threads >>> (image_source_1, image_source_2, image_mask, image_result, N);
	cudaDeviceSynchronize();

	frame_result.create(imageH, imageW, CV_8UC(3));
	cudaMemcpy(frame_result.data, image_result, N * sizeof(uchar3), cudaMemcpyDeviceToHost);
	imshow("ImagenResultado", frame_result);

	waitKey(0);

	frame_result.release();

	cudaFree(image_source_1);
	cudaFree(image_source_2);
	cudaFree(image_mask);
	cudaFree(image_result);

	return 0;
}