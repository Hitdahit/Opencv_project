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
	//threshold: r,��Ÿ ��鿡�� ��� ��� �������� ���� �� �������� �Ǵ������� ���� �ּҰ�
	vector <Vec4i> lines;
	HoughLinesP(src, lines, 5, CV_PI/180, threshold);

	Mat dst = src.clone();  //�� �̰� ã�� �־��µ� ������
	for (size_t i = 0; i < lines.size(); i++) {
		Vec4i l = lines[i];

		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1);
	}

	return dst;
}
Mat mask_roi(Mat src, Mat mask)   //�ᱹ ���� ������
{
	for (int i = src.rows / 2; i < src.rows; i++) {  //roi�� �ڸ� �κ��� �����ص� ��.
	//for(int i = 0; i < src.rows; i++){     //�̰ž��� �� �ָ����� ���ϼ� ���� �ٵ� ���� ����� ��Ե�.
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
	//��輱(contour)���� ã�� ����.
	Mat srcImg = imread("road.jpg");
	Mat res = srcImg.clone();

	srcImg = roi(srcImg);
	imshow("srcimg", srcImg);
	int width = srcImg.cols;
	int height = srcImg.rows;

	Mat grayImg;
	//color �̹����� �����ϰԴ� �� �� ������ ���ʿ��� �ͱ��� ����ϰԵ�.
	cvtColor(srcImg, grayImg, COLOR_BGR2GRAY);
	imshow("grayImg", grayImg);



	Mat gaussImg;
	//blur�� �̹����� ������� ���ʿ��� gradient�� ���ֱ� ���ؼ� ����Ѵ�.
	GaussianBlur(grayImg, gaussImg, Size(9, 9), 0.7);
	imshow("gaussImg", gaussImg);

	Mat cannyImg;
	//1:3�� ¡�׷��..?  ���� Ű��ϱ� �ǳ�
	//Canny(gaussImg, cannyImg, (gaussImg.rows + gaussImg.cols) / 4, (gaussImg.rows + gaussImg.cols) / 2);
	Canny(gaussImg, cannyImg, 130, 400);
	imshow("cannyImg", cannyImg);

	//hough transform�Լ��� �̿��Ͽ� contour�� �� ������ ����
	/*
		hough�����̶� �Ѹ���� image space���� ������ ���Ͽ�
		�������� ������ ���� ������ ��, ����~ ������ ��:p, :������ x���� �̷�� ��:��Ÿ��
		�ξ �̸� 2���� ����� ������ ǥ���� ��. 
		(������ �Ķ���͸� ����ϴ� parameter space�� ������ ���Ⱑ ���Ѵ��� ��� ǥ���� �����⿡ ����.)
	*/
	Mat houghImg = hough_lines(cannyImg, 120);
	imshow("houghImg", houghImg);

	res = mask_roi(res, houghImg);
	imshow("res", res);

	waitKey();
	return 0;
}