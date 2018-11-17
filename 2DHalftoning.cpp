#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <opencv2/imgproc/imgproc.hpp> //filter2D함수를 위해서 include
using namespace cv;
using namespace std;




int main(int argc, char** argv) {
	Mat src = imread("Mandrill_g.bmp", IMREAD_GRAYSCALE);
	Mat dst = Mat::zeros(src.size(), src.type());

	double p, T, th;
	p = 0;
	double g[256][256];
	double M[2][3] = { { 0.0, 0.0, 7. / 16 },{ 3. / 16, 5. / 16, 1. / 16 } };
	th = 150.0;

	for (int i = 0; i<256; i++)
	{
		for (int j = 0; j<256; j++)
		{
			if (j<1)
			{
				p = 0;
			}
			else if (i<2 && j<3)
			{
				p = g[i][j - 1];
			}
			else
			{
				p = 0;
				for (int mi = 0; mi <= 1; mi++)
					for (int mj = -1; mj<= 1; mj++)
						p = p + g[i - mi][j + mj] * M[mi][1 - mj];
			}

			T = (src.at<uchar>(i, j)) + uchar(p);

			if (T>th)
			{
				dst.at<uchar>(i, j) = 255;

				g[i][j] = T - 2 * th;
			}
			else
			{
				dst.at<uchar>(i, j) = 0;

				g[i][j] = th;
			}

		}
	}
	namedWindow("Image");
	imshow("Image", src);
	namedWindow("Result");
	imshow("Result", dst);

	imwrite("2DHalftoning.bmp", dst);
	waitKey(0);

	return 0;
}