/*
	sharping filtering�� ���󿡼� edgeȤ�� ������ �κ��� ������ų �� �ִ� ����̴�.
	
	1. �������
		�Ϲ�������, 2���� �Է¿��� src(x, y)���� (2*size+1)*(2*size+1)ũ���� ���� ������(Ŀ��) w(s, t)�� ��������
		�����Ǵ� ��ġ������ ���� ��� ���Ͽ� ��¿��� dst(x, y)�� �����Ѵ�.
		�׷��� opencv������ ���� ���� ���¿��� ������踦 ����Ҷ� anchor�� ����Ѵ�(������.
		)
	2. ȸ��(convolution)
		�������� ���� �¾�����, �����츦 180�� ȸ������ �����Ǵ� ��ġ�� ���� �����Ͽ� ���� ��¿��� dst�� �����Ѵ�.
		���� ������(Ŀ��/����)�� ��Ī���̶��, ����� ȸ���� ���� ���� ������ �Ѵ�. 
		ȸ���� ���չ�Ģ�� �����Ѵ�. �̷� ����, ����(������)�� �и��� �����ϴٰ� ���� �� �ִ�.
	3. 2D ���͸��Լ�
		void filter2D(InputArray src, OutputArray dst, int ddepth, InputArray kernel, 
						Point anchor=Point(-1, -1), double delta = 0, int borderType=BORDER_DEFAULT);
		�Է� src�� ������(Ŀ��)�� �̿��Ͽ� ȸ��(convolution)�� ��� �� dst�� �����ϴ� �Լ�. ddepth�� dst�� ���̷�, �̰��� -1�̸�
		dst.depth == src.depth()�̴�.
		kernel�� 1ä�� float�� ��ķ�, ��� ä�ο� �����ϰ� �����
		anchor�� Ŀ���� �߽����̴�(kernel ������ ��ġ.)
		
		filter2D �Լ��� �������� ����������, ��κ��� ������ Ŀ���� ��Ī�̹Ƿ�, convolution�Ѵٰ� �� �� �ִ�.
		
		void sepFilter2D(InputArray src, OutputArray dst, int ddepth, 
				InputArray kernelX, InputArray kernelY, Point anchorc = cPoint(-1, -1), 
				double deltac = c0, int borderTypec = cBORDER_DEFAULT
		)
		�и� ������ �������͸� ������. �Է�src�� �� �࿡ Ŀ��(������) kernelX�� ���� �� �� ����� �� ���� Ŀ��(������) kernelY�� �����Ͽ�
		ȸ���� ����� �� delta�� �����Ͽ� dst�� ������. ddepth�� dst�� ����.
*/
//filter2D�� ���gks 3*3 ��� ���͸�
/*
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	uchar dataA[] = {
		1,2,4,5,2,1,
		3,6,6,9,0,3,
		1,8,3,7,2,5,
		2,9,8,9,9,1,
		3,9,8,8,7,2,
		4,9,9,9,9,3
	};

	Mat A(6, 6, CV_8U, dataA);
	cout << "A = " << A << endl;

	Mat avgKernel = (Mat_<float>(3, 3) << 1./9., 1./9., 1./9.,
										  1./9., 1./9., 1./9.,
										  1./9., 1./9., 1./9.
	);   //����� ���� �̸� ����

	Point anchor(-1, -1);  //same as anchor(1,1)
	
	Mat B;
	filter2D(A, B, -1, avgKernel, anchor);
	cout << "B = " << B << endl;

	anchor = Point(1, 1);
	Mat C;
	filter2D(A, C, -1, avgKernel, anchor);
	cout << "C = " << C << endl;

	//conv
	Point newAnchor = Point(avgKernel.cols - anchor.x - 1, avgKernel.rows - anchor.y - 1);
	Mat D;
	Mat flipKernel;
	flip(avgKernel, flipKernel, -1);  //����ϴ� ���͸� 180�� ȸ���ؾ� conv.
	filter2D(A, D, -1, flipKernel, anchor);
	cout << "D = " << D << endl;


}
*/
//sepFilter2D�� ����� 3*3 ������͸�
/*
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	uchar dataA[] = {
		1,2,4,5,2,1,
		3,6,6,9,0,3,
		1,8,3,7,2,5,
		2,9,8,9,9,1,
		3,9,8,8,7,2,
		4,9,9,9,9,3
	};

	Mat A(6, 6, CV_8U, dataA);
	cout << "A = " << A << endl;

	Mat avgX = (Mat_<float>(1, 3) << 1./3., 1./3., 1./3.);
	Mat avgY = (Mat_<float>(3, 1) << 1. / 3., 1. / 3., 1. / 3.);

	Mat B, C;
	filter2D(A, B, -1, avgX);
	cout << "B = " << B << endl;

	filter2D(A, C, -1, avgY);
	cout << "C = " << C << endl;

	Mat D;
	sepFilter2D(A, D, -1, avgX, avgY);
	cout << "D = " << D << endl;

	waitKey();
	return 0;
}
*/
//���󿡼� filter2D, sepFilter2D�� ����� ��� ���͸�
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImg = imread("lena.jpg");
	if (srcImg.empty())return -1;

	Size ksize(7, 7);  //ksize(21, 21)
	Mat avgKernel = Mat::ones(ksize, CV_32F);
	avgKernel /= avgKernel.total();

	Mat avgImg;
	filter2D(srcImg, avgImg, -1, avgKernel);
	imshow("avgImg", avgImg);

	Mat avgX = Mat::ones(1, ksize.width, CV_32F);
	Mat avgY = Mat::ones(ksize.height, 1, CV_32F);
	avgX /= avgX.total();
	avgY /= avgY.total();

	Mat avgImg2;
	sepFilter2D(srcImg, avgImg2, -1, avgX, avgY);
	imshow("avgImg2", avgImg2);

	waitKey();
	return 0;
}