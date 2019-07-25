// XBOpenCV.cpp: 定义应用程序的入口点。
//

#include "XBOpenCV.h"
#include "opencv2/opencv.hpp"


using namespace std;
using namespace cv;

int main()
{
	//打开摄像头
	cout << "Hello CMake。" << endl;
	VideoCapture capture(0);
	Mat p;

	while (1) {
		capture >> p;
		imshow("video", p);
		waitKey(300);
	}

	//加载图片
	Mat img = imread("C:/Users/Administrator/Desktop/girl.jpg");
	imshow("img",img);
	//图片灰色处理
	cvtColor(img, img, COLOR_BGR2GRAY);
	imshow("img2", img);
	waitKey(30000);
	return 0;
}
