// Standard Library
#include <iostream>
#include<algorithm>
// OpenCV Header
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
void printstar(int n)
{
	for (int i = 0; i < n; i++)
		std::cout << "*";
	std::cout << endl;
}
int main(int argc, char** argv)
{

	cv::Mat Img = cv::imread("L.jpg", 0);
	cv::imshow("Display window", Img);
	for (auto &pixel : cv::Mat_<uchar>(Img))
		/*statement*/;
	cv::waitKey(0);
	return 0;
}
