#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;


int main(int argc, char** argv) {
	Mat src, dst;
	src = imread("citrus.bmp", IMREAD_GRAYSCALE); // Read the file
	dst = Mat::zeros(src.size(), src.type());
	if (src.empty()) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}


	int hist[256], chist[256];
	for (int i = 0; i<256; i++)
	{
		hist[i] = 0;
		chist[i] = 0;
	}


	for (int i = 0; i<256; i++)
		for (int j = 0; j<256; j++)
			hist[src.at<uchar>(i, j)]++;
	int sum = 0;
	for (int i = 0; i<256; i++)
	{
		sum = sum + hist[i];
		chist[i] = sum;
	}
	int k;
	for (int i = 0; i<256; i++)
		for (int j = 0; j<256; j++)
		{
			k = src.at<uchar>(i, j);

			dst.at<uchar>(i, j) = int(255 * chist[k] / 256 / 256 + 0.5);

		}

	namedWindow("source", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("source", src); // Show our image inside it.

	namedWindow("result", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("result", dst); // Show our image inside it.
	imwrite("HistogramEq.bmp", dst);
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}