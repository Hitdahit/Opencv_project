#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));  //512*512 크기의 3채널 컬러 이미지. (255,255,255)로 초기화
	if (dstImage.empty()) return -1;    

	Rect imgRect(100, 100, 300, 300);
	rectangle(dstImage, imgRect.tl(), imgRect.br(), Scalar(255, 0, 0), 2); //사각형의 두 모서리 좌표를 tl, br로 받아옴. 
	//CV_RGB(0,0,255)의 색으로 초기화

	Point pt1(120, 50), pt2(300, 500);
	line(dstImage, pt1, pt2, Scalar(0, 255, 0), 2);   //pt1, pt2를 양끝점으로 하는 직선을 생성.

	clipLine(imgRect, pt1, pt2);   //점 pt1, 2를 잇는 직선이 사각형 imgRect에 의해 절단 되는 좌표점을 계산하여 다시 pt1, pt2에 저장.

	cout << "pt1 = " << pt1 << endl;
	cout << "pt2 = " << pt2 << endl;

	circle(dstImage, pt1, 5, Scalar(0, 0, 255), 2);   //다시 계산된 점들을 이요하여 반지름 5, 선두께 2짜리 원을 그림
	circle(dstImage, pt2, 5, Scalar(255, 0, 0), 2);

	imshow("dstImage", dstImage);
	waitKey();
	return 0;
}