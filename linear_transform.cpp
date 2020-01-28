//������ȯ
/*
	��ȯ���� ������ȯ, �α׺�ȯ, �ŵ����� ��ȯ�� �ִ�.

	���� ��ȯ: �Է¿��� r�� ����(scale), y����(shift)�� �ִ� ������ �����Ŀ� �����Ͽ� ������ ��ȯ��.

	�α� ��ȯ: �Է� r�� ���Ͽ�, s=log(r)�� ������ ������ ��ȯ.

	�ŵ����� ��ȯ: ������ ���� ���� �پ��ϰ� �Է¿����� ��ȯ ��Ŵ. s=r^p
*/

#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImg = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImg.empty())return -1;

	double minVal, maxVal;
	Point minLoc, maxLoc;

	minMaxLoc(srcImg, &minVal, &maxVal, &minLoc, &maxLoc);   //src������ �ִ� �ּҿ� ����ġ�� ã���ִ� �Լ�.

	cout << "In srcImg" << endl;
	cout << "minVal = " << minVal << endl;
	cout << "maxVal = " << maxVal << endl;
	cout << "minLoc = " << minLoc << endl;
	cout << "maxLoc = " << maxLoc << endl;

	Mat dstImg;
	double scale = 100.0 / (maxVal - minVal);   //scale
	srcImg.convertTo(dstImg, -1, scale, -scale * minVal);
	//normalize(srcImg, dstImg, 0, 100, NORM_MINMAX);    0~100�� ������ ���� ��ȯ. ���� ���� �ڵ�.

	minMaxLoc(dstImg, &minVal, &maxVal, &minLoc, &maxLoc);
	cout << "in dstImg" << endl;
	cout << "minVal = " << minVal << endl;
	cout << "maxVal = " << maxVal << endl;
	cout << "minLoc = " << minLoc << endl;
	cout << "maxLoc = " << maxLoc << endl;

	imshow("dstImg", dstImg);
	waitKey();
	
	return 0;
}