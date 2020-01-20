#include <iostream>
#include <opencv2/core.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat A1(1, 2, DataType<uchar>::type);  //Mat A1(1, 2, CV_8U); 로 대체할 수 있다. 1채널짜리 Mat.
	A1.at<uchar>(0, 0) = 1;
	A1.at<uchar>(0, 1) = 1;

	cout << "A1: " << A1 << endl;
	cout << "depth = " << A1.depth() << ", " <<
					"channels = " << A1.channels() << endl;

	Mat A2(1, 2, CV_8UC3);   //3채널짜리 Mat.
	A2.at<Vec<uchar, 3>>(0.0) = Vec3d(10, 20, 30);
	A2.at<Vec<uchar, 3>>(0, 1) = Vec3d(40, 50, 60);
	
	cout << "A2: " << A2 << endl;
	cout << "depth = " << A2.depth() << ", " <<
					"channels = " << A2.channels() << endl;

	cout << "\n";
	Mat B(1, 2, DataType<float>::type);   //(1, 2, CV32_F);로 대체 가능. 역시 1채널짜리.
	B.at<float>(0, 0) = 10.0f;
	B.at<float>(0, 1) = 20.0f;
	cout << "B: " << B << endl;
	cout << "depth = " << B.depth() << ", " <<
					"channels = " << B.channels() << endl;

	cout << "\n";
	Mat C(1, 2, CV_32SC2);  //Point 타입. 1*2행렬. 
	C.at<Point>(0, 0) = Point(100, 100);
	C.at<Point>(0, 1) = Point(200, 200);
	cout << "C " << C << endl;
	cout << "depth = " << C.depth() << ", "<<
					"channels = " << C.channels() << endl;

	cout << "\n";
	Mat D(1, 2, DataType<complex<double>>::type);   //CV_64FC2로 대체.
	D.at <complex <double>>(0, 0) = complex<double>(10.0, 20.0);
	D.at<complex<double>>(0, 1) = complex<double>(10.0, 20.0);
	cout << "D " << D << endl;
	cout << "depth = " << D.depth() << ", " <<
					"channels = " << D.channels() << endl;

	return 0;
}