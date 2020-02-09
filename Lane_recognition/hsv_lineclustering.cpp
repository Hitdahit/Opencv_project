#include <opencv2/opencv.hpp>
#include <utility>
#include <vector>
#include <cmath>
using namespace std;
using namespace cv;
typedef pair<int, int> pii;
vector <pii> yellow;
vector <pii> white1;
vector <pii> white2;
Mat roi(Mat srcImg)
{
	Mat mask;
	Scalar color;

	int height = srcImg.rows;
	int width = srcImg.cols;

	Point vertices[1][4];
	vertices[0][0] = Point(0, height);
	vertices[0][1] = Point(0, height / 2);
	vertices[0][2] = Point(width, height / 2);
	vertices[0][3] = Point(width, height);

	const Point* ppt[1] = { vertices[0] };
	int npt[] = { 4 };

	if (srcImg.channels() == 3) {
		mask = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC3);   //src와 같은 크기의 빈이미지
		color = Scalar(255, 255, 255);
	}
	else {
		mask = Mat::zeros(srcImg.rows, srcImg.cols, CV_8UC1);
		color = 255;
	}

	fillPoly(mask, ppt, npt, 1, color);

	Mat ROI = srcImg & mask;

	return ROI;

}
//개뻘짓
/*
void comp_pixel(Mat img, int i, int j, Mat& dst)
{
	//흰색의 경우에는 h값과 상관없이, s값이 작아질수록 흰색에 가까워지며(0~255)
	//v 값은 밝기를 관장하므로, 밝기 조절을 위해 아래와 같이 조절했다.
	if (img.at<Vec3b>(i, j)[1] < 20 && img.at<Vec3b>(i, j)[2] > 150) {   
		dst.at<Vec3b>(i, j)[0] = 0;
		dst.at<Vec3b>(i, j)[1] = 0;
		dst.at<Vec3b>(i, j)[2] = 255;
	}
	else if (img.at<Vec3b>(i, j)[0] < 40 && img.at<Vec3b>(i, j)[0] > 20
		&& img.at<Vec3b>(i, j)[1] > 25 
		&& img.at<Vec3b>(i, j)[2]<200) {
		dst.at<Vec3b>(i, j)[0] = 0;
		dst.at<Vec3b>(i, j)[1] = 255;
		dst.at<Vec3b>(i, j)[2] = 0;
	}
	else {
		dst.at<Vec3b>(i, j)[0] = 0;
		dst.at<Vec3b>(i, j)[1] = 0;
		dst.at<Vec3b>(i, j)[2] = 0;
	}
}
*/
Mat mask(Mat hsvImg)
{
	Mat white_line(hsvImg.rows, hsvImg.cols, CV_8UC1);
	Mat yellow_line(hsvImg.rows, hsvImg.cols, CV_8UC1);
	Mat wy_line(hsvImg.rows, hsvImg.cols, CV_8UC3);
	
	//개뻘짓
	/*
	for (int i = 0; i < hsvImg.rows; i++) {
		for (int j = 0; j < hsvImg.cols; j++)
			comp_pixel(hsvImg, i, j, line);
	}
	*/

	//inRange 함수는 그 범위안에 들어가게되면 0으로 만들어주고 나머지는 1로 만들어 흑백사진을 만든다.
	inRange(hsvImg, Scalar(0, 0, 200), Scalar(255, 20, 255), white_line);
	inRange(hsvImg, Scalar(20, 80, 80), Scalar(60, 255, 255), yellow_line);

	//imshow("")
	imshow("white", white_line);
	imshow("yellow", yellow_line);
	return	wy_line;



}

//HSV 색 공간은 색을 표현하는 하나의 방법이자, 그 방법에 따라 색을 배치하는 방식이다. 색상(Hue), 채도(Saturation), 명도(Value)의 좌표를 써서 특정한 색을 지정한다.
//hue는 회전한 값이므로 각도, saturation은 원기둥의 반지름, Value는 높이

int main()
{
	Mat srcImg = imread("road3.png");  //hsv 명도 채도 ???를 써서 검출 (노란색 흰색 차선 검출 따로시키기 위해)
	Mat origin = srcImg.clone();
	
	if (srcImg.empty())return -1;
	imshow("src", srcImg);
	
	Mat hsvImg;
	cvtColor(srcImg, hsvImg, COLOR_BGR2HSV);

	Mat	white_line = mask(hsvImg);
	
	white_line = roi(white_line);
	
	imshow("res", white_line);
	waitKey();
	return 0;
}
