#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main()
{
	//总体思路为，先在imagewatch里观察原图像素值，决定将200作为划分前景和背景的阈值，遍历像素值来找到三个边角点（认为像素值小于200的一排像素中的中点为边角点），构成仿射矩阵，再进行仿射变换来矫正图像
	cv::Mat srcMat = imread("C:\\Users\\Lenovo\\Pictures\\数图\\旋转lena.jpg",0);
	cv::Mat dstMat;//图像矫正后
	cv::Point2f	src_pt[3];
	cv::Point2f dst_pt[3];
	int height = srcMat.rows;
	int width = srcMat.cols;
	int corner_num = 0;//找到的边角点计数
	int step = 0;//初始扫描的行
	int start = 0;
	int stop = 0;
	int first_flag, second_flag, third_flag;//分别表示是否找到左上方边角点、左下方边角点、右上方边角点
	uchar threshold = 200;

	first_flag = second_flag = third_flag = 0;
	while (corner_num < 3)
	{
		//找左上方的边角点 从第0行开始找
		if (first_flag == 0)
		{
			for (int j = 0; j < width; j++)
			{
				start = stop = 0;
				if (srcMat.at<uchar>(step, j) < threshold)
				{
					start = j; //记录第一个被视为前景（像素值小于200）的像素点横坐标
					while (srcMat.at<uchar>(step, j) < threshold)
					{
						stop = j;//记录最后一个被视为前景的像素点横坐标
						j++;
					}
				}
				if (start != stop)
				{
					corner_num++;
					src_pt[0].x = (stop + start) / 2; //取中点认为是边角点
					src_pt[0].y = step;
					dst_pt[0].x = 0;
					dst_pt[0].y = 0;
					first_flag = 1;
					break;
				}
			}
		}

		//找左下方的边角点 从第0列开始找
		if (second_flag == 0)
		{
			for (int j = 0, step = 0; j < height; j++)
			{
				start = stop = 0;
				if (srcMat.at<uchar>(j, step) < threshold)
				{
					start = j;
					while (srcMat.at<uchar>(j, step) < threshold)
					{
						stop = j;
						j++;
					}
				}
				if (start != stop)
				{
					corner_num++;
					src_pt[1].x = step;
					src_pt[1].y = (stop + start) / 2;
					dst_pt[1].x = 0;
					dst_pt[1].y = height - 1;
					second_flag = 1;
					break;
				}
			}
		}

		//找右上方的边角点 从最后一列开始找
		if (third_flag == 0)
		{
			for (int j = 0, step = width - 1; j < height; j++)
			{
				start = stop = 0;
				if (srcMat.at<uchar>(j, step) < threshold)
				{
					start = j;
					while (srcMat.at<uchar>(j, step) < threshold)
					{
						stop = j;
						j++;
					}
				}
				if (start != stop)
				{
					corner_num++;
					src_pt[2].x = step;
					src_pt[2].y = (stop + start) / 2;
					dst_pt[2].x = width - 1;
					dst_pt[2].y = 0;
					third_flag = 1;
					break;
				}
			}
		}
		step++;

	}
	std::cout << "横坐标：" << src_pt[0].x << std::endl;
	std::cout << "纵坐标：" << src_pt[0].y << std::endl;
	const cv::Mat affine_matrix = cv::getAffineTransform(src_pt, dst_pt);//计算仿射矩阵

	cv::warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());//仿射变换

	cv::imshow("src", srcMat);
	cv::imshow("dst", dstMat);
	cv::waitKey(0);
}