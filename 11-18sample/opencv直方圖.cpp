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
	cv::Mat dstHist;
	float hranges[] = { 0, 255 };
	const float *ranges[] = { hranges };
	const int channels[] = { 0, 1 };
	int size = 256;
	cv::calcHist(&Img, 1,channels, cv::Mat(), dstHist, 1, &size, ranges);
	int scale = 1;
	cv::Mat dstImg(size*scale, size, CV_8U, cv::Scalar(0));
	double maxValue = 0;
	double minValue = 0;
	cv::minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);
	int hpt = cv::saturate_cast<int>(0.9*size);
	for (int i = 0; i < 256; i++)
	{
		float binValue = dstHist.at<float>(i);
		int realValue = cv::saturate_cast<int>(binValue*hpt/maxValue);
		cv::rectangle(dstImg, 
			cv::Point(i*scale, size - 1), 
			cv::Point((i + 1)*scale , size - realValue), 
			cv::Scalar(255));
		printstar(realValue / 3);
	}
	cv::imshow("Hist", dstImg);
	cv::Mat Img2;
	cv::threshold(Img, Img2, 129, 255, cv::THRESH_BINARY);
	cv::namedWindow("Img2", cv::WINDOW_NORMAL);
	cv::imshow("Img2", Img2);
	cv::waitKey(0);
	
	return 0;
}
