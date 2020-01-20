//Vec클래스 활용하기

#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Vec<float, 3> X(1, 0, 0);  // Vec3f X(1, 0, 0);
	Vec<float, 3> Y(0, 1, 0);  //Vec3f Y(0,1,0);
	Vec3f Z = X.cross(Y);   //X x Y 로 외적을 구함.

	Point3f pt3 = X;  //Vec과 Point는 호환이 가능하다.

	X = Vec3f(1, 2, 3);
	Y = Vec3f(10, 100, 1000);
	Z = X.mul(Y);    //벡터의 요소별 곱셈. Z도 벡터다.

	sum(Z);  //Z의 모든 요소를 더함. 리턴은 cv::Scalar.

	X = Vec3f::all(1.0f);

	return 0;
}