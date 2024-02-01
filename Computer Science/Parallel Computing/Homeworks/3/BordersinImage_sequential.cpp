#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

const int k[2][3][3] = {
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

void Derivates(uchar* image, int* Dx, int* Dy, int imageW, int imageH, int N)
{
	int index, index1;
	for (int idx = 1; idx < imageW - 1; idx++)
	{
		for (int idy = 1; idy < imageH - 1; idy++)
		{
			index = (idy)*imageW + (idx);
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
}

void BordersinImage(int* Dx, int* Dy, uchar* MG, uchar* MGT, int imageW, int imageH, int N)
{
	int index;

	for (int idx = 0; idx < imageW; idx++)
	{
		for (int idy = 0; idy < imageH; idy++)
		{
			index = (idy)*imageW + (idx);
			if (0 < idx && idx < imageW - 1 && 0 < idy && idy < imageH - 1)
				MG[index] = min(sqrt(Dx[index] * Dx[index] + Dy[index] * Dy[index]), 255.0);
			else if (0 <= idx && idx < imageW && 0 <= idy && idy < imageH)
				MG[index] = 0;
			MGT[index] = (MG[index] > 255 / 2 ? 255 : 0);
		}
	}
}

int divUp(int a, int b) {
	return (a + b - 1) / b;
}

int main() {

	Mat frame = imread("./pinzas_gray.png", IMREAD_GRAYSCALE), frameMG, frameMGT;

	int imageW = frame.cols, imageH = frame.rows, N = imageW * imageH;

	// Crear memoria en la GPU
	uchar* image, * MG, * MGT;
	int* Dx, * Dy;
	image = (uchar*)malloc(N * sizeof(uchar));
	Dx = (int*)malloc(N * sizeof(int));
	Dy = (int*)malloc(N * sizeof(int));
	MG = (uchar*)malloc(N * sizeof(uchar));
	MGT = (uchar*)malloc(N * sizeof(uchar));

	memcpy(image, frame.data, N * sizeof(uchar));
	Derivates(image, Dx, Dy, imageW, imageH, N);
	BordersinImage(Dx, Dy, MG, MGT, imageW, imageH, N);

	frameMG.create(imageH, imageW, CV_8UC(1));
	frameMGT.create(imageH, imageW, CV_8UC(1));
	memcpy(frameMG.data, MG, N * sizeof(uchar));
	memcpy(frameMGT.data, MGT, N * sizeof(uchar));
	imshow("MG", frameMG);
	imshow("MGT", frameMGT);
	waitKey(0);

	frameMG.release();
	frameMGT.release();

	free(image);
	free(Dx);
	free(Dy);
	free(MG);
	free(MGT);

	return 0;
}