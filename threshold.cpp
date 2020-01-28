//�Ӱ谪 ����.
/*
	�Է¿����� ��Ⱚ r�� �־��� �Ӱ谪(threshold)���� ũ�� max_value,
	�׷��� ������ 0���� ��� ������ ��⸦ �����Ѵ�.
	threshold �Լ��� �پ��� �Ӱ谪 ������ �����Ѵ�.
*/
/*
	1. double threshold(InputArray src, OuputArray dst, double thresh, double maxval, int type);
	=>src: ���� ä���� CV_8U/CV_32F�� �Է¿���.(�Ƹ��� IMREAD_GRAYSCALE)
	thresh�� �Ӱ谪, type�� �Ӱ谪�� ������ ��Ÿ����.
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
	//OTSU�� �Ӱ谪 thresh�� ���� ���� �Ӱ谪�� Otsu�˰����� �����Ͽ� ����ϰ� ��ȯ.
	double th2 = threshold(srcImg, dstImg2, 100, 255, THRESH_BINARY+THRESH_OTSU);

	cout << "th2 = " << th2 << endl;
	
	imshow("dstImg1", dstImg1);
	imshow("dstImg2", dstImg2);

	waitKey();

	return 0;

}
