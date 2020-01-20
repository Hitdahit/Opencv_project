#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat A(2, 3, CV_8UC1); //8bit, uchar로 1channel 2*3 행렬 생성.
	Mat B(2, 3, CV_8UC1, Scalar(0));  //Scalar(0)f로 B초기화.
	Mat C(2, 3, CV_8UC1, Scalar(1, 2, 3));   //8bit, Scalar(1,2,3)으로 초기화 된 1channel 2*3 행렬

	float data[] = { 1,2,3,4,5,6 };

	Mat D(2, 3, CV_32FC1);  //32bit, 실수 1channel.

	cout << "A: " << A << endl;
	cout << "B: " << B << endl;
	cout << "C: " << C << endl;
	cout << "D: " << D << endl;

	Mat A1(Size(3, 2), CV_8UC1);  //2*3행렬이 만들어짐.

	return 0;

}