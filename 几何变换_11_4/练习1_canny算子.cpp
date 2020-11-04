#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;

int main()
{
	cv::Mat srcMat = imread("C:\\Users\\Lenovo\\Desktop\\∫Ï–°∂π2.jpg");
	cv::Mat dstMat;
	double threshold1 = 120, threshold2 = 220;

	Canny(srcMat, dstMat, threshold1, threshold2);

	imshow("‘≠Õº", srcMat);
	imshow("±ﬂ‘µºÏ≤‚",dstMat);
	waitKey(0);

}