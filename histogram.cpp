/*
	����ó������ ������ ������׷��� ����ȭ���� ��ǥ�� ���� �ſ� �߿��� ����.
	������׷��� ���, ������׷��� �̿��� ���ο�, ������׷� �� ������׷� ��Ȱȭ ���� �ٷ��.
*/
/*
	calcHist(~);
*/
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	uchar dataA[16] = {
		0, 0, 0, 0,
		1, 1, 3, 5,
		6, 1, 1, 3,
		4, 3, 1, 7
	};

	Mat A(4, 4, CV_8U, dataA);
	cout << "A = " << A << endl;

	//������׷� ������,
	int histSize[] = { 4 };
	float valueRange[] = { 0, 8 };
	const float* ranges[] = { valueRange };
	int channels[] = { 0 };
	int dims = 1;

	Mat hist;
	calcHist(&A, 1, channels, Mat(), hist, dims, histSize, ranges, true);   //�Ű������� ���� ������ ���� ��� ������׷��� ����Ͽ�
	//hist ��Ŀ� ����.

	cout << "hist = " << hist << endl;

	Mat pdf;
	normalize(hist, pdf, 1, 0, NORM_L1);   //�հ谡 1�� �ǵ��� ����ȭ
	cout << "pdf =" << pdf << endl;

	return 0;
}