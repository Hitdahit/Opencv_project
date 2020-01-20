#include <opencv2/core.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
	Point2f pt1(0.1f, 0.2f), pt2(0.3f, 0.4f);  //float형 포인터 객체 두개 생성.

	Point pt3 = (pt1 + pt2) * 10.0f;
	Point2f pt4 = (pt1 - pt2) * 10.0f;
	Point pt5 = Point(10, 10);
	Point2f pt6 = Point2f(10.0f, 10.0f);

	cout << "pt1: " << pt1 << endl;
	cout << "pt2: " << pt2 << endl;
	cout << "pt3: " << pt3 << endl;
	cout << endl;
	cout << "pt4: " << pt4 << endl; 
	cout << "pt5: " << pt5 << endl; 
	cout << "pt6: " << pt6 << endl;

	if (pt1 == pt2)
		cout << "pt1 is equal to pt2" << endl;
	else
		cout << "pt1 is not equal to pt2" << endl;

	float fValue = pt1.dot(pt2);   //pt1과 pt2사이의 내적.
	cout << "fValue = " << fValue << endl;

	double normValue = norm(pt1); //L2normalization.
	cout << "normValue = " << normValue << endl;

	Point pt(150, 150);
	Rect rect(100, 1000, 200, 200);

	if (pt.inside(rect))   //Point pt 가 rect 내부의 점인지 확인함.
		cout << "pt is an inside point in the rect" << endl;
	else
		cout << "pt is not an inside point in rect" << endl;

	return 0;
}