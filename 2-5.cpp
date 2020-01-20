//Rect Ŭ���� Ȱ��

#include <iostream>
#include <opencv2/opencv.hpp>   //�����δ� �̷��� ����!

using namespace cv;
using namespace std;
int main()
{
	Rect rt1(100, 100, 320, 240), rt2(200, 200, 320, 240);   //x, y, width, height ������ ����.
	Point pt1(100, 100);   //Rect�� �׻� ���簢���� ���¸� ����. x, y�� topleft���� ��ǥ�� �����Ѵ�.

	Size size(100, 100);     

	Rect rt3 = rt1 + pt1;  //x,y�� �ٲ�.
	Rect rt4 = rt1 + size;  //width, height�� �ٲ�.
	//method: tl(), br(), size(), area(), contains()
	
	cout << "rt1: " << rt1.x << ", " << rt1.y << ", " << rt1.width << ", " << rt1.height << endl;
	cout << "rt1: " << rt1;

	Point TopLeft = rt1.tl();
	Point BottomRight = rt1.br();
	cout << "TopLeft in rt1: " << TopLeft << endl;
	cout << "BottomRight in rt1: " << BottomRight << endl;

	Point pt2(200, 200);
	if (rt1.contains(pt2)) cout << "pt2�� rt1�ȿ� ���Ե�." << endl;

	Rect rt5 = rt1 & rt2; //intersection.  1, 2�簢���� ������. (���ٸ� Rect(0,0,0,0))
	Rect rt6 = rt1 | rt2; //minimum area rectangle containing rt1 and rt2. 1, 2�簢���� ��� �����ϴ� �ϳ��� �簢��. ������

	cout << "rt5: " << rt5 << endl;
	cout << "rt6: " << rt6 << endl;

	if (rt1 != rt2)
		cout << "rt1 and rt2 are not same rect." << endl;

	Mat img(600, 800, CV_8UC3);  //3ä�� 600*800���.
	namedWindow("image", WINDOW_AUTOSIZE);

	rectangle(img, rt1, Scalar(255, 0, 0), 2);   //Mat ��Ŀ� ���ݱ����� �簢������ �׸�. Scalar�� ��, 2�� ���β��� ����
	rectangle(img, rt2, Scalar(0, 255, 0), 2);
	rectangle(img, rt5, Scalar(0, 0, 255), 2);

	imshow("image", img);   //�̹����� ������.

	waitKey(0);  //escŰ�� â����

	rectangle(img, rt6, Scalar(0, 0, 0), 1);
	circle(img, pt2, 5, Scalar(255, 0, 255), 2);   //pt2�� �����������ϴ� ������ 5 ���׸���.
	imshow("image", img);
	waitKey(0);

	return 0;




}
