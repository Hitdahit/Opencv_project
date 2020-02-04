#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImg = imread("road.jpg"); 
	Mat grayImg;
	cvtColor(srcImg, grayImg, COLOR_BGR2GRAY);
	imshow("grayImg", grayImg);

	Mat gaussImg;
	GaussianBlur(grayImg, gaussImg, Size(9, 9), 0.7);
	imshow("gaussImg", gaussImg);

	Mat dstImg;
	Canny(gaussImg, dstImg, 10, 400);
	//imshow("dstImg", dstImg);


	


	//고정 ROI 설정
	Rect rect(0, 400, 960, 320);
	Mat subImg = srcImg(rect);
	
	//하얀색 검출하기
	Mat whiteImg = subImg;
	for (int i = 0; i < subImg.rows; i++) {
		for (int j = 0; j < subImg.cols; j++) {
			if (whiteImg.at<Vec3b>(i, j)[0] < 230
				&& whiteImg.at<Vec3b>(i, j)[1] < 230
				&& whiteImg.at<Vec3b>(i, j)[2] < 230) {
				
				whiteImg.at<Vec3b>(i, j)[0] = 0;
				whiteImg.at<Vec3b>(i, j)[1] = 0;
				whiteImg.at<Vec3b>(i, j)[2] = 0;
			}
		}
	}

	for (int i = 0; i < 400; i++) {
		for (int j = 0; j < subImg.cols; j++) {
			srcImg.at<Vec3b>(i, j)[0] = 0;
			srcImg.at<Vec3b>(i, j)[1] = 0;
			srcImg.at<Vec3b>(i, j)[2] = 0;
		}
	}
	cvtColor(srcImg, srcImg, COLOR_BGR2GRAY);
	imshow("srcImg", srcImg);

	dstImg = srcImg & dstImg;
	

	imshow("dstImg", dstImg);
	waitKey();
	return 0;

}