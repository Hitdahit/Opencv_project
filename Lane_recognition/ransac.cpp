#include <opencv2/opencv.hpp>
#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;
using namespace cv;

typedef pair<int, int> pii;
vector <pii> white1;
vector <pii> white2;
Mat roi(Mat srcImg)
{
	Mat mask;
	Scalar color;

	int height = srcImg.rows;
	int width = srcImg.cols;

	Point vertices[1][6];
	vertices[0][0] = Point(0, height);
	vertices[0][1] = Point(0, height * 7 / 8);
	vertices[0][2] = Point(width / 4, height * 7 / 11);
	vertices[0][3] = Point(width * 6 / 7, height * 7 / 11);
	vertices[0][4] = Point(width, height * 7 / 8);
	vertices[0][5] = Point(width, height);

	const Point* ppt[1] = { vertices[0] };
	int npt[] = { 6 };

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
Mat mask(Mat hsvImg)
{
	Mat white_line(hsvImg.rows, hsvImg.cols, CV_8UC1);
	Mat yellow_line(hsvImg.rows, hsvImg.cols, CV_8UC1);

	//inRange 함수는 그 범위안에 들어가게되면 0으로 만들어주고 나머지는 1로 만들어 흑백사진을 만든다.
	inRange(hsvImg, Scalar(0, 0, 200), Scalar(255, 20, 255), white_line);
	inRange(hsvImg, Scalar(20, 80, 80), Scalar(60, 255, 255), yellow_line);

	imshow("white", white_line);
	imshow("yellow", yellow_line);

	return	white_line;
}
/*
int find_mid(Mat white_line)
{
	int first_flag = 0, second_flag = 1;
	int left = 0, right = 0;

	for (int i = white_line.rows; i > 0; i--) {
		for (int j = 0; j < white_line.cols; j++) {
			if (white_line.at<uchar>(i, j) && !first_flag) {
				first_flag = 1;
				left = i;
			}
			else if(white_line.at<uchar>(i, j) && first_flag)
				d
			}
		}
	}
}
*/
void clustering(Mat white_line)
{
	int mid = white_line.cols / 2;

	for (int i = 0; i < white_line.rows; i++) {
		for (int j = 0; j < white_line.cols; j++) {
			if (white_line.at<uchar>(i, j)) {
				if (j < mid) white1.push_back(make_pair(i, j));
				else white2.push_back(make_pair(i, j));
			}
		}
	}
	cout << white1.size();
}
//클러스터링 테스트 용
void test_cluster(Mat srcImg)
{
	int idx = 0;
	for (int i = 0; i < srcImg.rows; i++) {
		for (int j = 0; j < srcImg.cols; j++) {
			if (idx < white1.size() && white1[idx].first == i && white1[idx].second == j) {
				srcImg.at<Vec3b>(i, j) = Vec3b(0, 0, 255);
				idx++;
			}
		}
	}
	imshow("test", srcImg);
}

pii ransac(int n, int t)
{
	srand((unsigned int)time(NULL));
	int c_max = 0;
	pii param_max;
	
	for (int i = 0; i < n; i++) {
		
		int p1, p2, c = 0;
		p1 = rand() % white1.size();
		p2 = rand() % white1.size();

		double param_a, param_b;
		param_a = (white1[p1].first - white1[p2].first) / (white1[p1].second - white1[p2].second);
		param_b = white1[p1].second - param_a * white1[p1].first;
		
		for (int j = 0; j < white1.size(); j++) {
			int test = double(white1[j].first) - white1[j].second * param_a + param_b;
			if (abs(test) <= t) c++;
		}
		if (c > c_max) {
			c_max = c;
			param_max.first = param_a;
			param_max.second = param_b;
		}

		c = 0;
	
	}

	return param_max;
}
void test_ransac(Mat src, pii param)
{
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			if (-1*param.first * j - param.second == i) {
				src.at<Vec3b>(i, j)[0] = 0;
				src.at<Vec3b>(i, j)[1] = 0;
				src.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}
	imshow("ransac", src);
}
int main()
{
	Mat srcImg = imread("road9.jpg");  //hsv 명도 채도 ???를 써서 검출 (노란색 흰색 차선 검출 따로시키기 위해)
	Mat origin = srcImg.clone();

	if (srcImg.empty()) {
		cerr << "invalid file";
		return -1;
	}

	Mat hsvImg;
	cvtColor(srcImg, hsvImg, COLOR_BGR2HSV);
	Mat roi_hsv = roi(hsvImg);

	Mat	white_line = mask(roi_hsv);

	
	clustering(white_line);

	/*
	//테스트
	test_cluster(origin);
	*/
	pii param = ransac(30, 5);

	test_ransac(origin,param);
	//imshow("res", white_line);
	waitKey();
	return 0;
}
