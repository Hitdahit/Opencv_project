//적응형 threshold
/*
	void adaptiveThreshold(InputArray src, OutputArray dst, double maxValue, 
						int adaptiveMethod, int thresholdType, int blockSize, double C);
		src: 8비트 단일 채널 영상 
		blockSize*blockSize 크기의 이웃에서 계산한 평균 또는 가중 평균에서 C값을 뺄셈하여 임계값을 계산.
		그 후 thresholdType에 따라서 dst를 계산함.
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