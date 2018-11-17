#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src, dst;
	src = imread("coin.bmp", IMREAD_GRAYSCALE); // Read the file
	dst = Mat::zeros(src.size(), src.type());

	int hist[256];
	for (int i = 0; i<256; i++)
		hist[i] = 0;

	for (int i = 0; i<256; i++) //È÷½ºÅä±×·¥ È¹µæ
		for (int j = 0; j<256; j++)
			hist[src.at<uchar>(i, j)]++;

	float prob[256];
	for (int i = 0; i<256; i++)
		prob[i] = float(hist[i]) / (256 * 256); //p[i]

	float q1, q2, m1, m2, d1, d2, dw;
	float var = 10000000000000.0f;
	int T;
	//int t=19;
	for (int t = 0; t<256; t++)
	{
		q1 = 0.0f;
		q2 = 0.0f;
		m1 = 0.0f;
		m2 = 0.0f;
		d1 = 0.0f;
		d2 = 0.0f;
		for (int i = 0; i<t; i++)
			q1 = q1 + prob[i];
		for (int i = t; i<256; i++)
			q2 = q2 + prob[i];
		if (q1 == 0 || q2 == 0) continue;

		for (int i = 0; i<t; i++)
			m1 = m1 + i * prob[i] / q1;

		for (int i = t; i<256; i++)
			m2 = m2 + i * prob[i] / q2;

		for (int i = 0; i<t; i++)
			d1 = d1 + (i - m1)*(i - m1)*prob[i] / q1;

		for (int i = t; i<256; i++)
			d2 = d2 + (i - m2)*(i - m2)*prob[i] / q2;

		dw = q1 * d1 + q2 * d2;

		if (dw<var)
		{
			T = t;
			var = dw;
		}
	}


	for (int i = 0; i<256; i++)
		for (int j = 0; j<256; j++)
		{
			if (src.at<uchar>(i, j) < T)
				dst.at<uchar>(i, j) = 0;
			else
				dst.at<uchar>(i, j) = 255;

		}

	namedWindow("result", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("result", dst);                // Show our image inside it.
	imwrite("Otsu.bmp", dst);
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}