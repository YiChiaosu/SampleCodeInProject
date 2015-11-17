// Standard Library
#include <iostream>
#include<algorithm>
// OpenCV Header
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
int main(int argc, char** argv)
{
	cv::Mat Img = cv::imread("a.jpg", 0);
	cv::Mat Img2;
	cv::threshold(Img, Img2, 129, 255, cv::THRESH_BINARY);
	cv::namedWindow("Img2", cv::WINDOW_NORMAL);
	cv::imshow("Img2", Img2);
	cv::waitKey(0);
	return 0;
}
