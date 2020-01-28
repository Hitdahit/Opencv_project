//������ threshold
/*
	void adaptiveThreshold(InputArray src, OutputArray dst, double maxValue, 
						int adaptiveMethod, int thresholdType, int blockSize, double C);
		src: 8��Ʈ ���� ä�� ���� 
		blockSize*blockSize ũ���� �̿����� ����� ��� �Ǵ� ���� ��տ��� C���� �����Ͽ� �Ӱ谪�� ���.
		�� �� thresholdType�� ���� dst�� �����.
*/
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImg = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImg.empty()) return -1;

	Mat dstImg1;
	adaptiveThreshold(srcImg, dstImg1, 255,
				ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 21, 5);		//

	Mat dstImg2;
	adaptiveThreshold(srcImg, dstImg2, 255,
				ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 21, 5);

	imshow("dstImg1", dstImg1);
	imshow("dstImg2", dstImg2);
	waitKey();

	return 0;
}