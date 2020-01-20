//Range 클래스의 활용
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Matx33f A(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	);

	Mat B(A);  //Mat 변수의 생성.

	Mat C = B(Range(1, 3), Range::all());   //B(행, 열);
	cout << "C = " << C<<endl;

	Mat D = B(Range::all(), Range(1, 3));
	cout << "D = " << D << endl;
	
	return 0;
}