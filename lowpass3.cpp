#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat src, dst;
	src = imread("Mandrill.bmp", IMREAD_COLOR); // Read the file
	dst = Mat::zeros(src.size(), src.type());

	double mask[3][3] = { { 1. / 9, 1. / 9, 1. / 9 },{ 1. / 9, 1. / 9, 1. / 9 },{ 1. / 9, 1. / 9, 1. / 9 } };

	double val;

	for (int i = 0; i<256; i++)
	{
		for (int j = 0; j<256; j++)
		{
			for (int c = 0; c<3; c++)
			{
				val = 0;
				for (int mi = -1; mi<2; mi++)
				{
					for (int mj = -1; mj<2; mj++)
					{
						if (i + mi>-1 && i + mi <256 && j + mj>-1 && j + mj <256)
						{
							val = val + double(src.at<Vec3b>((i + mi), (j + mj))[c]) * double(mask[mi + 1][mj + 1]);

						}
					}
				}
				dst.at<Vec3b>(i, j)[c] = int(val);

			}

		}
	}

	namedWindow("result", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("result", dst);                // Show our image inside it.
	imwrite("lowpass_filtering_3.bmp", dst);
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}