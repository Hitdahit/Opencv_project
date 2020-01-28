//선형변환
/*
	변환에는 선형변환, 로그변환, 거듭제곱 변환이 있다.

	선형 변환: 입력영상 r을 기울기(scale), y절편(shift)이 있는 직선의 방정식에 대입하여 영상을 변환함.

	로그 변환: 입력 r에 대하여, s=log(r)의 식으로 영상을 변환.

	거듭제곱 변환: 지수의 값에 의해 다양하게 입력영상을 변환 시킴. s=r^p
*/

#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImg = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImg.empty())return -1;

	double minVal, maxVal;
	Point minLoc, maxLoc;

	minMaxLoc(srcImg, &minVal, &maxVal, &minLoc, &maxLoc);   //src영상의 최대 최소와 그위치를 찾아주는 함수.

	cout << "In srcImg" << endl;
	cout << "minVal = " << minVal << endl;
	cout << "maxVal = " << maxVal << endl;
	cout << "minLoc = " << minLoc << endl;
	cout << "maxLoc = " << maxLoc << endl;

	Mat dstImg;
	double scale = 100.0 / (maxVal - minVal);   //scale
	srcImg.convertTo(dstImg, -1, scale, -scale * minVal);
	//normalize(srcImg, dstImg, 0, 100, NORM_MINMAX);    0~100의 범위로 선형 변환. 위와 같은 코드.

	minMaxLoc(dstImg, &minVal, &maxVal, &minLoc, &maxLoc);
	cout << "in dstImg" << endl;
	cout << "minVal = " << minVal << endl;
	cout << "maxVal = " << maxVal << endl;
	cout << "minLoc = " << minLoc << endl;
	cout << "maxLoc = " << maxLoc << endl;

	imshow("dstImg", dstImg);
	waitKey();
	
	return 0;
}