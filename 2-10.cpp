#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Matx33d A(1, 1, 2,
		2, -3, -5
		- 1, 3, 5);   //double.

	Matx33d B = A.inv(DECOMP_CHOLESKY);   //DECOMP_CHOLESKY�� ������� ������� ����.
	Matx33d C = A.inv(DECOMP_LU);   //LU���ط� ����� ����.

	Matx33d D = A * B;
	Matx33d E = A * C;
	//������� �� ���Ǿ��ٸ�, D��E�� ��� ��������� �ȴ�.
}