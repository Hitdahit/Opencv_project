//임계값 영상.
/*
	입력영상의 밝기값 r이 주어진 임계값(threshold)보다 크면 max_value,
	그렇지 않으면 0으로 출력 영상의 밝기를 설정한다.
	threshold 함수는 다양한 임계값 종류를 제공한다.
*/
/*
	1. double threshold(InputArray src, OuputArray dst, double thresh, double maxval, int type);
	=>src: 단일 채널의 CV_8U/CV_32F의 입력영상.(아마도 IMREAD_GRAYSCALE)
	thresh는 임계값, type은 임계값의 종류를 나타낸다.
	type:
		THRESH_BINARY, THRESH_BINARY_INV, THRESH_TRUNC, THRESH_TOZERO, THRESH_TOZERO_INV
*/
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImg = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImg.empty()) return -1;

	Mat dstImg1;
	double th1 = threshold(srcImg, dstImg1, 100, 255, THRESH_BINARY);
	cout << "th1 = " << th1 << endl;

	Mat dstImg2;
	//OTSU는 임계값 thresh와 관계 없이 임계값을 Otsu알고리즘을 적용하여 계산하고 반환.
	double th2 = threshold(srcImg, dstImg2, 100, 255, THRESH_BINARY+THRESH_OTSU);

	cout << "th2 = " << th2 << endl;
	
	imshow("dstImg1", dstImg1);
	imshow("dstImg2", dstImg2);

	waitKey();

	return 0;

}
