#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Matx33f A = Matx33f::zeros();   //모두 0인 행렬만들기
	Matx33f B = Matx33f::ones();    //모두 1인 행렬만들기
	Matx33f C = Matx33f::eye();     //모두 정방행렬의 대각요소만 1이고 나머지는 모두 0인 단위 행렬.
	Matx33f D = Matx33f::all(10.0f); //행렬의 모든 값이 10.0f인 행렬만들기
}