#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat dstImage(512, 512, CV_8UC3, Scalar(55, 255, 255));
	rectangle(dstImage, Point(100, 100), Point(400, 400), Scalar(0, 0, 255), 2);   //thickness=2

	line(dstImage, Point(400, 100), Point(100, 400), Scalar(0, 255, 0));  //선 그리기. 색도 정해줄 수 있음

	line(dstImage, Point(400, 100), Point(100, 400), Scalar(0, 255, 0), 2, 8, 1);   //...thickness=2, linetype=8, shift=1
	//->shift가 1이므로, 사실상 그려지는 좌표는 각 좌표값의 절반이 되어, 아래의 사각형의 대각선을 그리게 됨.

	rectangle(dstImage, Point(400 / 2, 100 / 2), Point(100 / 2, 400 / 2),
		Scalar(255, 0, 0));
	
	imshow("dstImage", dstImage);
	waitKey();
	return 0;
}