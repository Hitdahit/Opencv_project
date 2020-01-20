#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Matx33d A(1, 1, 2,
		2, -3, -5
		- 1, 3, 5);   //double.

	Matx33d B = A.inv(DECOMP_CHOLESKY);   //DECOMP_CHOLESKY의 방법으로 역행렬을 구함.
	Matx33d C = A.inv(DECOMP_LU);   //LU분해로 역행렬 구함.

	Matx33d D = A * B;
	Matx33d E = A * C;
	//역행렬이 잘 계산되었다면, D와E는 모두 단위행렬이 된다.
}