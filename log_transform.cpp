#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImg = imread("lena.jpg", IMREAD_GRAYSCALE);  
	if (srcImg.empty()) return -1;

	Mat fimg;
	srcImg.convertTo(fimg, CV_32F);  //������ CV_32F���·� ��ȯ.
	add(fimg, Scalar(1), fimg);  //��� ȭ�Ұ��� 1�� ����. �ּҰ� log(0)�� �ǵ��� ����� ����.

	Mat logImg;
	log(fimg, logImg);     //�� ȭ�ҿ� �α׸� �����ִ� �Լ�.  logimg�� ���� �����.
	//pow(fimg����, ���ϴ� power��, powimg���);    �ŵ�������ȯ.

	double minVal, maxVal;
	minMaxLoc(logImg, &minVal, &maxVal);   //�α׸� ���� �̹����� �ִ� �ּҰ� ã����(��ġ�� ����,)

	cout << "Before normalizing in logimg" << endl;   //
	cout << "minVal = " << minVal << endl;
	cout << "maxVal = " << maxVal << endl;

	normalize(logImg, logImg, 0, 1.0, NORM_MINMAX);   //������ ���� 0~1������ �Ǽ��� ����ȭ.
	minMaxLoc(logImg, &minVal, &maxVal);

	cout << "After noemalizing in logImg" << endl;
	cout << "minVal = " << minVal << endl;
	cout << "maxVal = " << maxVal << endl;

	imshow("logImg", logImg);
	waitKey();
	return 0;

}