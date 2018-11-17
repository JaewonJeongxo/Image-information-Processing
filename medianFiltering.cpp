#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#define BYTE unsigned char

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src, dst;
	src = imread("Mandrill_g.bmp", IMREAD_GREYSCALE); // Read the file
	dst = Mat::zeros(src.size(), src.type());

	int h = src.rows;
	int w = src.cols;

	for (int i = 0; i<256; i++)
	{
		for (int j = 0; j<256; j++)
		{
			
			int px = (int)(x / 3);
			int py = (int)(y / 3);

			double fx1 = (double)x / 3 - px;
			double fx2 = 1 - fx1;
			double fy1 = (double)y / 3 - py;
			double fy2 = 1 - fy1;

			double w1 = fx2 * fy2;
			double w2 = fx1 * fy2;
			double w3 = fx2 * fy1;
			double w4 = fx1 * fy1;

			uchar P1 = src.at<uchar>(py, px);
			uchar P2 = src.at<uchar>(py, px + 1);
			uchar P3 = src.at<uchar>(py + 1, px);
			uchar P4 = src.at<uchar>(py+1, px + 1);
			
			dst.at<ucahr>(i, j) = w1 * P1 + w2 * P2 + w3 * P3 + w4 * P4;
			
		}
	}

	namedWindow("result", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("result", dst);                // Show our image inside it.
	imwrite("median_filtering.bmp", dst);
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}