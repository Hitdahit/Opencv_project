#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImg = imread("lena.jpg", IMREAD_GRAYSCALE);  
	if (srcImg.empty()) return -1;

	Mat fimg;
	srcImg.convertTo(fimg, CV_32F);  //영상을 CV_32F형태로 변환.
	add(fimg, Scalar(1), fimg);  //모든 화소값에 1을 더함. 최소가 log(0)가 되도록 만들기 위해.

	Mat logImg;
	log(fimg, logImg);     //각 화소에 로그를 취해주는 함수.  logimg에 값이 저장됨.
	//pow(fimg원본, 원하는 power값, powimg결과);    거듭제곱변환.

	double minVal, maxVal;
	minMaxLoc(logImg, &minVal, &maxVal);   //로그를 취한 이미지의 최대 최소값 찾아줌(위치도 가능,)

	cout << "Before normalizing in logimg" << endl;   //
	cout << "minVal = " << minVal << endl;
	cout << "maxVal = " << maxVal << endl;

	normalize(logImg, logImg, 0, 1.0, NORM_MINMAX);   //영상의 값을 0~1사이의 실수로 정규화.
	minMaxLoc(logImg, &minVal, &maxVal);

	cout << "After noemalizing in logImg" << endl;
	cout << "minVal = " << minVal << endl;
	cout << "maxVal = " << maxVal << endl;

	imshow("logImg", logImg);
	waitKey();
	return 0;

}