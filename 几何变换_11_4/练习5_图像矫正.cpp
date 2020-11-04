#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main()
{
	//����˼·Ϊ������imagewatch��۲�ԭͼ����ֵ��������200��Ϊ����ǰ���ͱ�������ֵ����������ֵ���ҵ������߽ǵ㣨��Ϊ����ֵС��200��һ�������е��е�Ϊ�߽ǵ㣩�����ɷ�������ٽ��з���任������ͼ��
	cv::Mat srcMat = imread("C:\\Users\\Lenovo\\Pictures\\��ͼ\\��תlena.jpg",0);
	cv::Mat dstMat;//ͼ�������
	cv::Point2f	src_pt[3];
	cv::Point2f dst_pt[3];
	int height = srcMat.rows;
	int width = srcMat.cols;
	int corner_num = 0;//�ҵ��ı߽ǵ����
	int step = 0;//��ʼɨ�����
	int start = 0;
	int stop = 0;
	int first_flag, second_flag, third_flag;//�ֱ��ʾ�Ƿ��ҵ����Ϸ��߽ǵ㡢���·��߽ǵ㡢���Ϸ��߽ǵ�
	uchar threshold = 200;

	first_flag = second_flag = third_flag = 0;
	while (corner_num < 3)
	{
		//�����Ϸ��ı߽ǵ� �ӵ�0�п�ʼ��
		if (first_flag == 0)
		{
			for (int j = 0; j < width; j++)
			{
				start = stop = 0;
				if (srcMat.at<uchar>(step, j) < threshold)
				{
					start = j; //��¼��һ������Ϊǰ��������ֵС��200�������ص������
					while (srcMat.at<uchar>(step, j) < threshold)
					{
						stop = j;//��¼���һ������Ϊǰ�������ص������
						j++;
					}
				}
				if (start != stop)
				{
					corner_num++;
					src_pt[0].x = (stop + start) / 2; //ȡ�е���Ϊ�Ǳ߽ǵ�
					src_pt[0].y = step;
					dst_pt[0].x = 0;
					dst_pt[0].y = 0;
					first_flag = 1;
					break;
				}
			}
		}

		//�����·��ı߽ǵ� �ӵ�0�п�ʼ��
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

		//�����Ϸ��ı߽ǵ� �����һ�п�ʼ��
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
	std::cout << "�����꣺" << src_pt[0].x << std::endl;
	std::cout << "�����꣺" << src_pt[0].y << std::endl;
	const cv::Mat affine_matrix = cv::getAffineTransform(src_pt, dst_pt);//����������

	cv::warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());//����任

	cv::imshow("src", srcMat);
	cv::imshow("dst", dstMat);
	cv::waitKey(0);
}