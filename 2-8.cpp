#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Matx33f A = Matx33f::zeros();   //��� 0�� ��ĸ����
	Matx33f B = Matx33f::ones();    //��� 1�� ��ĸ����
	Matx33f C = Matx33f::eye();     //��� ��������� �밢��Ҹ� 1�̰� �������� ��� 0�� ���� ���.
	Matx33f D = Matx33f::all(10.0f); //����� ��� ���� 10.0f�� ��ĸ����
}