#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat A(3, 3, CV_32F);   //3*3 float 1채널 행렬
	for (int i = 0; i < A.rows; i++) {
		for (int j = 0; j < A.cols; j++) {
			A.at<float>(i, j) = (float)(i * A.cols + j);
		}
	}
	cout << "A = " << A << endl;

	Mat B = A.clone();  //행렬복제
	cout << "B = " << B << endl;

	Mat C1;
	A.copyTo(C1);
	cout << "C1 = " << C1 << endl;

	Mat C2;
	A.row(1).copyTo(C2);
	cout << "C2 = " << C2 << endl;

	Mat mask(3, 3, CV_8UC1, Scalar(0));
	mask.row(1).setTo(Scalar::all(1));
	cout << "mask = " << mask << endl;

	Mat C3;
	A.copyTo(C3, mask);
	cout << "C3 = " << C3 << endl;

	Mat D1;
	A.convertTo()
}