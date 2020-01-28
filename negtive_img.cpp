//영상 반전하기
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImg = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImg.empty()) {    //잘하자...
		return -1;
	}
	
	Mat_<uchar> image(srcImg);           //1채널짜리로 변환
	Mat_<uchar> dstImg(srcImg.size());   //srcImg의 변환을 받아주기 위해 선언.

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			uchar r = image(i, j);
			dstImg(i, j) = 255 - r;     //원래 픽셀 값과 픽셀 최대값 255와의 차를 넣어주면 이미지 색 반전이 된다.
		}
	}
	
	imshow("dstImg", dstImg);

	waitKey();
	return 0;
}