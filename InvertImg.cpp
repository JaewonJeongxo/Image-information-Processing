#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;


int main(int argc, char** argv) {
	Mat image, InvertedImage;
	image = imread("invert.png", IMREAD_COLOR); // Read the file

												  //방법 1  not 연산자 사용
												  //image = ~image;

												  //방법 2 채널 분리
	Mat channel[3], channelOut[3];

	split(image, channel);

	bitwise_not(channel[0], channelOut[0]);
	bitwise_not(channel[1], channelOut[1]);
	bitwise_not(channel[2], channelOut[2]);

	merge(channelOut, 3, InvertedImage);
	imshow("Display window", InvertedImage);                // Show our image inside it.
	imwrite("invertedImg.png", InvertedImage);
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}