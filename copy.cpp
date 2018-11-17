#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <opencv2/imgproc/imgproc.hpp> //filter2D�Լ��� ���ؼ� include
using namespace cv;
using namespace std;

#define BYTE unsigned char

int main(int argc, char** argv) {
	Mat src = imread("Mandrill.bmp", IMREAD_COLOR);
	Mat dst = Mat::zeros(src.size(), src.type());




	// �ڵ� ���� �κ�

	for (int i = 0; i<src.rows; i++)
		for (int j = 0; j<src.cols; j++)
			for (int c = 0; c<3; c++)
				dst.at<Vec3b>(i, j)[c] = src.at<Vec3b>(i, j)[c];

	namedWindow("Original Image");
	imshow("Original Image", src);

	namedWindow("Result Image");
	imshow("Result Image", dst);

	waitKey(0);
}