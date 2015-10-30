// Standard Library
#include <iostream>

// OpenCV Header
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

// Kinect for Windows SDK Header
#include <Kinect.h>

using namespace std;

int main(int argc, char** argv)
{
	// 1a. Get default Sensor
	IKinectSensor* pSensor = nullptr;
	GetDefaultKinectSensor(&pSensor);

	// 1b. Open sensor
	pSensor->Open();

	// 2a. Get frame source
	IDepthFrameSource* pFrameSource = nullptr;
	pSensor->get_DepthFrameSource(&pFrameSource);

	// 2b. Get frame description
	int        iWidth = 0;
	int        iHeight = 0;
	IFrameDescription* pFrameDescription = nullptr;
	pFrameSource->get_FrameDescription(&pFrameDescription);
	pFrameDescription->get_Width(&iWidth);
	pFrameDescription->get_Height(&iHeight);
	pFrameDescription->Release();
	pFrameDescription = nullptr;

	// 2c. get some dpeth only meta
	UINT16 uDepthMin = 0, uDepthMax = 0;
	pFrameSource->get_DepthMinReliableDistance(&uDepthMin);
	pFrameSource->get_DepthMaxReliableDistance(&uDepthMax);
	cout << "Reliable Distance: "
		<< uDepthMin << " – " << uDepthMax << endl;

	// perpare OpenCV
	cv::Mat mDepthImg{ iHeight, iWidth, CV_16UC1 };
	cv::Mat mImg8bit(iHeight, iWidth, CV_8UC1);
	int a[] = { 1, 2, 3, 4 };

	cv::Mat Img = cv::imread("Hello.jpg", CV_LOAD_IMAGE_COLOR);
	cv::namedWindow("Depth Map");
	cv::namedWindow("Display window", CV_WINDOW_AUTOSIZE);// Create a window for display.
	cv::imshow("Display window", Img);
	
	cv::Mat gray, edge, draw;
	cv::cvtColor(Img, gray, CV_BGR2GRAY);

	cv::Canny(gray, edge, 50, 150, 3);

	edge.convertTo(draw, CV_8U);
	cv::namedWindow("image", CV_WINDOW_AUTOSIZE);
	cv::imshow("image", draw);


	// 3a. get frame reader
	IDepthFrameReader* pFrameReader = nullptr;
	pFrameSource->OpenReader(&pFrameReader);

	// Enter main loop
	while (true)
	{
		// 4a. Get last frame
		IDepthFrame* pFrame = nullptr;
		if (pFrameReader->AcquireLatestFrame(&pFrame) == S_OK)
		{
			// 4c. copy the depth map to image
			pFrame->CopyFrameDataToArray(iWidth * iHeight,
				reinterpret_cast<UINT16*>(mDepthImg.data));

			// 4d. convert from 16bit to 8bit
			mDepthImg.convertTo(mImg8bit, CV_8U, 255.0f / uDepthMax);
			cv::imshow("Depth Map", mImg8bit);

			// 4e. release frame
			pFrame->Release();
		}

		// 4f. check keyboard input
		if (cv::waitKey(30) == VK_ESCAPE){
			break;
		}
	}

	// 3b. release frame reader
	pFrameReader->Release();
	pFrameReader = nullptr;

	// 2d. release Frame source
	pFrameSource->Release();
	pFrameSource = nullptr;

	// 1c. Close Sensor
	pSensor->Close();

	// 1d. Release Sensor
	pSensor->Release();
	pSensor = nullptr;

	return 0;
}
