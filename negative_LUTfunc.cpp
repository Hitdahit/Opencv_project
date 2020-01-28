#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImg = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImg.empty()) return -1;

	//Mat lut(1, 256, CV_8U);

	//for (int i = 0; i < 256; i++) {
	//	lut.at<uchar>(0, i) = 256 - i;
	//}

	//1*256 ũ�� ��� lut ��ķ� LUT�Լ��� �־ ���������� ����. �� �� �ɷ� �Ұ�...
	Mat_<uchar> lut(1, 256);
	for (int i = 0; i < 256; i++) 
		lut(i) = 256 - i;

	Mat dstImg;
	LUT(srcImg, lut, dstImg);
	
	imshow("dstImg", dstImg);
	waitKey();

	return 0;
	
}