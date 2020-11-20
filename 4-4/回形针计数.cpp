#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("C:/Users/DELL/Desktop/4.jpg", 0);
	if (srcMat.empty())
	{
		cout<<"fail toread pic!" << endl; 
		return 0;

	}
	srcMat = 255 - srcMat;
	Mat stats;
	Mat centroids;
	Mat labels;
	Mat thresh_Mat;
	Mat open_Mat;

	threshold(srcMat, thresh_Mat, 100, 255, THRESH_OTSU);
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(thresh_Mat, open_Mat, MORPH_OPEN, element, Point(-1, -1), 1);
	int nComp = connectedComponentsWithStats(open_Mat, labels, stats, centroids, 8, CV_32S);
	for (int i = 1;i < nComp; i++)
	{
		int width = stats.at<int>(i, 2);
		int height = stats.at<int>(i, 3);
		int ratio = height / width;
		if (ratio > 10)
		{
			nComp--;
		}

	}
	cout << "回型针个数为：" << nComp - 1 << endl;
	waitKey(0);
	return 0;
}
