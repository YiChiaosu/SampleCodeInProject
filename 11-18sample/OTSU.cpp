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
	std::cout << "show the Hello.bmp";
	vector<int> acc( 256 );
	for (auto &pixel : cv::Mat_<uchar>(Img))
		acc[static_cast<int>(pixel)]++;
	int max=0;
	int i = 1;
	double u = 0;
	vector<double> P(256);
	vector<double> uT(256);
	vector<double> wT(256);
	for (auto n : acc)
	{
		P[i - 1] = n / static_cast<double>(Img.cols*Img.rows);
		u += i*(P[i - 1]);
		i++;
	}
	cout << u << endl;
	int T=0;
	for (; T < 256; T++)
	{
		for (int i=1; i < T; i++)
		{
			uT[T] += i*P[i - 1];
			wT[T] += P[i - 1];
		}
	}
	double maxT = 0;
	double maxsigma = 0;
	double sigma=0;
	for (T=0; T < 255; T++)
	{
		sigma = wT[T] * (uT[T] - u)*(uT[T] - u) + (1 - wT[T]) * ((u - uT[T]) / (1 - wT[T]) - u) * ((u - uT[T]) / (1 - wT[T]) - u);
		if (sigma>maxsigma)
		{
			maxT = T;
			maxsigma = sigma;
		}
		//cout << sigma << endl;
	}
	cout << maxT;
	for (auto &pixel : cv::Mat_<uchar>(Img))
	{
		if (static_cast<int>(pixel) < maxT) pixel = 255;
		else pixel = 0;
	}
	
	cv::namedWindow("window", cv::WINDOW_NORMAL);
	cv::imshow("window", Img);
	return 0;
}
