#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImg;
	srcImg.create(512, 512, CV_8UC3);  //8bit 3channel

	for (int i = 0; i < srcImg.rows; i++) {
		for (int j = 0; j < srcImg.cols; j++) {
			srcImg.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
		}
	}
	
	imshow("srcImg", srcImg);

	waitKey(0);
	return 0;
}