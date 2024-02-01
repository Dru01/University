#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

void AlphaMatting(Mat &frame_source_1, Mat &frame_source_2, Mat &frame_mask, Mat &frame_result, int N)
{
	for(int idx = 0; idx < N; idx++)
	{
		int alpha = (frame_mask.data[idx] > 255 / 2) ? 1 : 0;
		frame_result.data[idx * 3 + 0] = frame_source_1.data[idx * 3 + 0] * alpha + (1 - alpha) * frame_source_2.data[idx * 3 + 0];
		frame_result.data[idx * 3 + 1] = frame_source_1.data[idx * 3 + 1] * alpha + (1 - alpha) * frame_source_2.data[idx * 3 + 1];
		frame_result.data[idx * 3 + 2] = frame_source_1.data[idx * 3 + 2] * alpha + (1 - alpha) * frame_source_2.data[idx * 3 + 2];
	}
}

int main()
{
	
	Mat frame_source_1 = imread("./greenScreen.jpg", IMREAD_COLOR),
		frame_source_2 = imread("./fondo.bmp", IMREAD_COLOR),
		frame_mask = imread("./greenscreenMask.bmp", IMREAD_GRAYSCALE),
		frame_result;

	int imageW = frame_source_1.cols, imageH = frame_source_1.rows, N = frame_source_1.cols * frame_source_1.rows;
	frame_result.create(imageH, imageW, CV_8UC(3));
	AlphaMatting (frame_source_1, frame_source_2, frame_mask, frame_result, N);
	
	imshow("ImagenResultado", frame_result);
	waitKey(0);

	frame_result.release();

	return 0;
}