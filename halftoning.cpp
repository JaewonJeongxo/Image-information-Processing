#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;


int main(int argc, char** argv) {
	Mat inputImage, outputImage;
	inputImage = imread("Mandrill_g.bmp", IMREAD_GRAYSCALE); // Read the file
	double p, g, T, th;
	p = 0;
	g = 0;
	th = 120.0;
	for (int i = 0; i<256; i++)
	{
		for (int j = 0; j<256; j++)
		{
			p = g;
			T = (inputImage.at<uchar>(i, j)) + p;

			if (T>th)
			{
				for (int c = 0; c<3; c++)
					inputImage.at<uchar>(i, j) = 255;
				g = T - 2 * th;
			}
			else
			{
				for (int c = 0; c<3; c++)
					inputImage.at<uchar>(i, j) = 0;
				g = th;
			}

		}
	}


	namedWindow("Display window");
	imshow("Display window", inputImage);                // Show our image inside it.
	imwrite("halftoning.bmp", inputImage);
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}