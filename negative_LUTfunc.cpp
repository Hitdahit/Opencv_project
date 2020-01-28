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

	//1*256 크기 행렬 lut 행렬로 LUT함수에 넣어서 반전영상을 만듬. 걍 전 걸로 할게...
	Mat_<uchar> lut(1, 256);
	for (int i = 0; i < 256; i++) 
		lut(i) = 256 - i;

	Mat dstImg;
	LUT(srcImg, lut, dstImg);
	
	imshow("dstImg", dstImg);
	waitKey();

	return 0;
	
}