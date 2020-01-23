#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat dstImage(512, 512, CV_8UC3, Scalar(55, 255, 255));
	rectangle(dstImage, Point(100, 100), Point(400, 400), Scalar(0, 0, 255), 2);   //thickness=2

	line(dstImage, Point(400, 100), Point(100, 400), Scalar(0, 255, 0));  //�� �׸���. ���� ������ �� ����

	line(dstImage, Point(400, 100), Point(100, 400), Scalar(0, 255, 0), 2, 8, 1);   //...thickness=2, linetype=8, shift=1
	//->shift�� 1�̹Ƿ�, ��ǻ� �׷����� ��ǥ�� �� ��ǥ���� ������ �Ǿ�, �Ʒ��� �簢���� �밢���� �׸��� ��.

	rectangle(dstImage, Point(400 / 2, 100 / 2), Point(100 / 2, 400 / 2),
		Scalar(255, 0, 0));
	
	imshow("dstImage", dstImage);
	waitKey();
	return 0;
}