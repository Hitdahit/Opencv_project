#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat dstImg(512, 512, CV_8UC3, Scalar(255, 255, 255));  //512*512크기 3채널 컬러 영상 생성. 흰색 초기화.

	rectangle(dstImg, Point(100, 100), Point(400, 400), Scalar(0, 0, 255));  //dstImg영상에 100,100 400,400으로 만든 빨간 정사각형 그리기
	line(dstImg, Point(250, 100), Point(250, 400), Scalar(0, 0, 255));   //정사각형을 1/4로 나누는 두 선분 그리기
	line(dstImg, Point(100, 250), Point(400, 250), Scalar(0, 0, 255));
	circle(dstImg, Point(250, 250), 150, Scalar(255, 0, 0));   //빨간 정사각형에 내접하는 원 그리기.

	circle(dstImg, Point(250, 250), 50, Scalar(0, 255, 0), -1);   //-1은 채우기. 초록색으로! bgr.

	imshow("dstImg", dstImg);
	waitKey();
	return 0;
}