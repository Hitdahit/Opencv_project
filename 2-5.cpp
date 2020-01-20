//Rect 클래스 활용

#include <iostream>
#include <opencv2/opencv.hpp>   //앞으로는 이렇게 선언!

using namespace cv;
using namespace std;
int main()
{
	Rect rt1(100, 100, 320, 240), rt2(200, 200, 320, 240);   //x, y, width, height 순으로 선언.
	Point pt1(100, 100);   //Rect는 항상 직사각형의 형태를 가짐. x, y는 topleft점의 좌표를 저장한다.

	Size size(100, 100);     

	Rect rt3 = rt1 + pt1;  //x,y가 바뀜.
	Rect rt4 = rt1 + size;  //width, height가 바뀜.
	//method: tl(), br(), size(), area(), contains()
	
	cout << "rt1: " << rt1.x << ", " << rt1.y << ", " << rt1.width << ", " << rt1.height << endl;
	cout << "rt1: " << rt1;

	Point TopLeft = rt1.tl();
	Point BottomRight = rt1.br();
	cout << "TopLeft in rt1: " << TopLeft << endl;
	cout << "BottomRight in rt1: " << BottomRight << endl;

	Point pt2(200, 200);
	if (rt1.contains(pt2)) cout << "pt2가 rt1안에 포함됨." << endl;

	Rect rt5 = rt1 & rt2; //intersection.  1, 2사각형의 교집합. (없다면 Rect(0,0,0,0))
	Rect rt6 = rt1 | rt2; //minimum area rectangle containing rt1 and rt2. 1, 2사각형을 모두 포함하는 하나의 사각형. 합집합

	cout << "rt5: " << rt5 << endl;
	cout << "rt6: " << rt6 << endl;

	if (rt1 != rt2)
		cout << "rt1 and rt2 are not same rect." << endl;

	Mat img(600, 800, CV_8UC3);  //3채널 600*800행렬.
	namedWindow("image", WINDOW_AUTOSIZE);

	rectangle(img, rt1, Scalar(255, 0, 0), 2);   //Mat 행렬에 지금까지의 사각형들을 그림. Scalar는 색, 2는 선두께를 지정
	rectangle(img, rt2, Scalar(0, 255, 0), 2);
	rectangle(img, rt5, Scalar(0, 0, 255), 2);

	imshow("image", img);   //이미지를 보여줌.

	waitKey(0);  //esc키로 창끄기

	rectangle(img, rt6, Scalar(0, 0, 0), 1);
	circle(img, pt2, 5, Scalar(255, 0, 255), 2);   //pt2를 꼭지점으로하는 반지름 5 원그리기.
	imshow("image", img);
	waitKey(0);

	return 0;




}
