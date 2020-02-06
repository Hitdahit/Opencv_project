#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
Mat roi(Mat src)
{
	Mat mask;
	Scalar color;
	int width = src.cols;
	int height = src.rows;

	Point vertices[1][4];
	vertices[0][0] = Point(0, height);
	vertices[0][1] = Point(0, height/2 );
	vertices[0][2] = Point(width, height/2);
	vertices[0][3] = Point(width, height);

	const Point* ppt[1] = { vertices[0] };
	int npt[] = { 4 };

	if (src.channels() == 3) {
		mask = Mat::zeros(src.rows, src.cols, CV_8UC3);
		color = Scalar(255, 255, 255);
	}
	else {
		mask = Mat::zeros(src.rows, src.cols, CV_8UC1);
		color = 255;
	}

	fillPoly(mask, ppt, npt, 1, color);

	Mat ROI = mask & src;
	
	return ROI;
}
Mat hough_lines(Mat src, int threshold=30)
{
	//threshold: r,세타 평면에서 몇개의 곡선이 한점에서 만날 때 직선으로 판단할지에 대한 최소값
	vector <Vec4i> lines;
	HoughLinesP(src, lines, 5, CV_PI/180, threshold);

	Mat dst = src.clone();  //오 이거 찾고 있었는데 개꿀팁
	for (size_t i = 0; i < lines.size(); i++) {
		Vec4i l = lines[i];

		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1);
	}

	return dst;
}
Mat mask_roi(Mat src, Mat mask)   //결국 색을 입힘ㅋ
{
	for (int i = src.rows / 2; i < src.rows; i++) {  //roi로 자른 부분은 무시해도 됨.
	//for(int i = 0; i < src.rows; i++){     //이거쓰면 더 멀리까지 보일순 있음 근데 엄한 흰색도 잡게됨.
		for (int j = 0; j < src.cols; j++) {
			if (mask.at<uchar>(i, j) > 200 || src.at<Vec3b>(i, j)[0] > 200 
					&& src.at<Vec3b>(i, j)[1] > 200
					&&src.at<Vec3b>(i, j)[2] > 200) {
				src.at<Vec3b>(i, j)[0] = 0;
				src.at<Vec3b>(i, j)[1] = 0;
				src.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}
	return src;
}
int main()
{
	//경계선(contour)들을 찾는 과정.
	Mat srcImg = imread("road.jpg");
	Mat res = srcImg.clone();

	srcImg = roi(srcImg);
	imshow("srcimg", srcImg);
	int width = srcImg.cols;
	int height = srcImg.rows;

	Mat grayImg;
	//color 이미지는 세세하게는 볼 수 있지만 불필요한 것까지 계산하게됨.
	cvtColor(srcImg, grayImg, COLOR_BGR2GRAY);
	imshow("grayImg", grayImg);



	Mat gaussImg;
	//blur는 이미지의 노이즈와 불필요한 gradient를 없애기 위해서 사용한다.
	GaussianBlur(grayImg, gaussImg, Size(9, 9), 0.7);
	imshow("gaussImg", gaussImg);

	Mat cannyImg;
	//1:3은 징그러운데..?  값을 키우니까 되네
	//Canny(gaussImg, cannyImg, (gaussImg.rows + gaussImg.cols) / 4, (gaussImg.rows + gaussImg.cols) / 2);
	Canny(gaussImg, cannyImg, 130, 400);
	imshow("cannyImg", cannyImg);

	//hough transform함수를 이용하여 contour들 중 직선을 검출
	/*
		hough공간이란 한마디로 image space위의 직선에 대하여
		원점에서 수선의 발을 내렸을 때, 원점~ 수직의 발:p, :수선과 x축이 이루는 각:세타로
		두어서 이를 2차원 평면의 점으로 표현한 것. 
		(직선의 파라미터를 사용하는 parameter space는 직선의 기울기가 무한대인 경우 표현할 수없기에 만듬.)
	*/
	Mat houghImg = hough_lines(cannyImg, 120);
	imshow("houghImg", houghImg);

	res = mask_roi(res, houghImg);
	imshow("res", res);

	waitKey();
	return 0;
}