#include <opencv2/core.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
	Point3f pt1(1.0f, 2.0f, 3.0f), pt2(0.0f, 1.0f, 0.0f);  //float형의 3차원 점 생성.
	Point3f pt4 = (pt1 - pt2) * 100.0f;

	if (pt1 != pt2)
		cout << "두 점이 서로 다름" << endl;
	else
		cout << "두 점이 서로 같음" << endl;

	float fValue = pt1.dot(pt2);
	cout << "fValue = " << fValue << endl;

	double normValue = norm(pt1); //L2normalization
	cout << "norm pt1: " << normValue << endl;;

	Point3f pt5 = pt1.cross(pt2);   //외적. pt1 x pt2의 꼴이 됨.
	Point3f pt6 = pt2.cross(pt1);
	cout << "pt5: " << pt5 << endl;
	cout << "pt6: " << pt6 << endl;

	return 0;

}