#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat B(3, 3, CV_8U, 1);  //1ä�� 3*3 ������� ��� 1�� �ʱ�ȭ��.
	Mat C(3, 3, CV_8U, Scalar(2));  //2�� ������ �ʱ�ȭ Scalar�� pair tuple � �ɼ��ִ�.

	cout << "B = " << B << endl;
	cout << "C = " << C << endl;

	Mat A1 = B;
	cout << "A1 = " << A1 << endl;

	Mat A2 = B + C;
	cout << "A2 = " << A2 << endl;

	B = 255;
	cout << "B = " << B << endl;

	Mat D(3, 3, CV_8UC3);
	D = 255;	//b g r �߿� b�� 255�� �ʱ�ȭ ��
	cout << "D = " << D << endl;

	D = Scalar(255, 255, 255);   //������ g, r���� 255�� ����
	cout << "D = " << D << endl;
	return 0;


}