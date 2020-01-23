#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat B(3, 3, CV_8U, 1);  //1채널 3*3 정방행렬 모두 1로 초기화함.
	Mat C(3, 3, CV_8U, Scalar(2));  //2의 값으로 초기화 Scalar는 pair tuple 등도 될수있다.

	cout << "B = " << B << endl;
	cout << "C = " << C << endl;

	Mat A1 = B;
	cout << "A1 = " << A1 << endl;

	Mat A2 = B + C;
	cout << "A2 = " << A2 << endl;

	B = 255;
	cout << "B = " << B << endl;

	Mat D(3, 3, CV_8UC3);
	D = 255;	//b g r 중에 b만 255로 초기화 됨
	cout << "D = " << D << endl;

	D = Scalar(255, 255, 255);   //나머지 g, r까지 255로 만듬
	cout << "D = " << D << endl;
	return 0;


}