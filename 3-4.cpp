#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat dstImg(512, 512, CV_8UC3, Scalar(255, 255, 255));  //512*512ũ�� 3ä�� �÷� ���� ����. ��� �ʱ�ȭ.

	rectangle(dstImg, Point(100, 100), Point(400, 400), Scalar(0, 0, 255));  //dstImg���� 100,100 400,400���� ���� ���� ���簢�� �׸���
	line(dstImg, Point(250, 100), Point(250, 400), Scalar(0, 0, 255));   //���簢���� 1/4�� ������ �� ���� �׸���
	line(dstImg, Point(100, 250), Point(400, 250), Scalar(0, 0, 255));
	circle(dstImg, Point(250, 250), 150, Scalar(255, 0, 0));   //���� ���簢���� �����ϴ� �� �׸���.

	circle(dstImg, Point(250, 250), 50, Scalar(0, 255, 0), -1);   //-1�� ä���. �ʷϻ�����! bgr.

	imshow("dstImg", dstImg);
	waitKey();
	return 0;
}