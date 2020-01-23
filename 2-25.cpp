//Mat 행렬 정보.

#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat A(4, 5, CV_32FC3);  //4*5 3채널 32비트 float

	cout << "A.rows = " << A.rows << endl;
	cout << "A.cols = " << A.cols << endl;
	cout << "A.dims = " << A.dims << endl;
	
	Mat B = A;
	A.at<Vec3f>(0, 0) = Vec3f(0.75, 1.0, 10); //Vec3f-> 3채널이므로


	//hex == 16진수로 출력하는 옵션.
	cout << "A.data = " << hex << (int*)A.data << endl;
	cout << "B.data = " << hex << (int*)B.data << endl;
	cout << "A.data[0] = " << *(float*)A.data << endl;
	cout << "A.data[4] = " << *(float*)(A.data + 4) << endl;
	
	cout << endl << endl;
	cout << "A.isContinuous() = " << A.isContinuous()<<endl;
	cout << "A.total() = " << A.total() << endl;
	cout << "A.elemSize() = " << A.elemSize() << endl;   //sizeof(float)*3channel
	cout << "A.elemSize1() = " << A.elemSize1() << endl;  //sizeof(float)
	cout << "A.type() = " << A.type() << endl;   //CV_32FC3  == 21
	cout << "A.depth() = " << A.depth() << endl;  //CV_32FC3 == 5
	cout << "A.channels() = " << A.channels() << endl;

	cout << endl << endl;
	cout << "A.step = " << A.step << endl;   // 5*12 == 60
	cout << "A.step1() = " << A.step1() << endl;  //60/4 ==15
	cout << "A.empty() = " << A.empty() << endl;  // false
	cout << "A.size() = " << A.size() << endl;    //5*4 ==20

	return 0;
}