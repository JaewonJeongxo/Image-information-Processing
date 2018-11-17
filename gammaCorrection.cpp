#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <math.h>
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

	for (int i = 0; i<256; i++)
		for (int j = 0; j<256; j++)
			dst.at<uchar>(i, j) = int(255 * pow(double(src.at<uchar>(i, j)) / 255, 0.5));

	namedWindow("source", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("source", src); // Show our image inside it.

	namedWindow("result", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("result", dst); // Show our image inside it.
	imwrite("GammaCrr.bmp", dst);
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}