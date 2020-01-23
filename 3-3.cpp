#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);  //lena.jpg�� �׷��� �����Ϸ� �ε�.
	if (srcImage.empty())return -1;

	Point pt1(10, 10), pt2(400, 400);  
	LineIterator it(srcImage, pt1, pt2, 8);   //pt1, 2�� �����ϴ� ������ connectivity 8�� �Ͽ� �����˰����� ����ϴ� �ݺ��ڸ� ����.

	vector<uchar> buffer(it.count);  //3ä���̸� uchar�� �ƴ� Vec3b�� ���.
	for (int i = 0; i < it.count; i++, ++it) {
		buffer[i] = **it;   //������ ȭ�ڰ� **it��  ������ buffer�� ����.

		//buffer[i] = srcImage.at<uchar>(it.pos());  //1ä��.
		//buffer[i] = *(const Vec3b)*it;  //3ä���� ���� ���� �ڵ� ���.
		//buffer[i] = srcImage.at<Vec3b>(it.pos());  //3ä��.
	}
	cout << (Mat)buffer << endl;  //buffer�� ����� ȭ�ڰ� ���.
	line(srcImage, pt1, pt2, Scalar(255), 2);   //pt1, 2�� �����ϴ� ������ ȭ�鿡 ���.(�����.)

	Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));  //3ä�� 512*512 ������ ����� ������� �ʱ�ȭ 
	pt1 = Point(0, dstImage.cols - buffer[0]);

	for (int i = 1; i < buffer.size(); i++, ++it) {
		pt2 = Point(0, dstImage.cols - buffer[i]);  
		line(dstImage, pt1, pt2, Scalar(255), 2);   //line�Լ��� �̿��ؼ� dstImage ���� buffer�� ����� ȭ�Ұ��� �׿��� ���������� �׸���.

		pt1 = pt2;
	}

	imshow("srcImage", srcImage);
	imshow("dstImage", dstImage);

}