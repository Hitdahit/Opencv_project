//VecŬ���� Ȱ���ϱ�

#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Vec<float, 3> X(1, 0, 0);  // Vec3f X(1, 0, 0);
	Vec<float, 3> Y(0, 1, 0);  //Vec3f Y(0,1,0);
	Vec3f Z = X.cross(Y);   //X x Y �� ������ ����.

	Point3f pt3 = X;  //Vec�� Point�� ȣȯ�� �����ϴ�.

	X = Vec3f(1, 2, 3);
	Y = Vec3f(10, 100, 1000);
	Z = X.mul(Y);    //������ ��Һ� ����. Z�� ���ʹ�.

	sum(Z);  //Z�� ��� ��Ҹ� ����. ������ cv::Scalar.

	X = Vec3f::all(1.0f);

	return 0;
}