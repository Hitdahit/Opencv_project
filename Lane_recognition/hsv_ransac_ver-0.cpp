#include <ctime>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <utility>
#include <iostream>
#include <opencv2/opencv.hpp>

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

	//사용할 영역의 좌상귀부터 반시계방향으로 좌표 적어둔거
	Point vertices[1][4];
	vertices[0][0] = Point(0, height * 3 / 7);
	vertices[0][1] = Point(0, height);
	vertices[0][2] = Point(width, height);
	vertices[0][3] = Point(width, height * 3 / 7);
	

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

Mat get_param3(int p1, int p2, int p3, int p4, vector<pii> lane)
{
	float x_val[] = {     //long long.....
			pow(lane[p1].first, 3), pow(lane[p1].first, 2), lane[p1].first, 1,
			pow(lane[p2].first, 3), pow(lane[p2].first, 2), lane[p2].first, 1,
			pow(lane[p3].first, 3), pow(lane[p3].first, 2), lane[p3].first, 1,
			pow(lane[p4].first, 3), pow(lane[p4].first, 2), lane[p4].first, 1
	};
	Mat x_mat = Mat(Size(4, 4), CV_64FC1);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) x_mat.at<double>(i, j) = x_val[i * 4 + j];

	float ans[] = {	
		lane[p1].second, lane[p2].second, lane[p3].second, lane[p4].second
	};
	Mat ans_mat = Mat(Size(1, 4), CV_64FC1);
	for (int i = 0; i < 4; i++) ans_mat.at<double>(i, 0) = ans[i];


	Mat new_x = Mat(Size(4, 4), CV_64FC1);
	invert(x_mat, new_x, DECOMP_SVD);
	
	Mat answer = new_x * ans_mat;  //Mat
	
	
	return answer;
}

Mat cal_function3(Mat param, vector<pii> lane)
{
	Mat X_in = Mat(Size(4, lane.size()), CV_64FC1);
	Mat residual = Mat(Size(1, lane.size()), CV_64FC1);

	for (int i = 0; i < lane.size(); i++) {
		for (int j = 3; j >= 0; j--)
			X_in.at<double>(i, 3 - j) = (double)pow(lane[i].first, j);
	}
	
	residual = X_in * param;   //(n,4)*(4*1)
	return residual;
}

Mat ransac3(int n, double t, vector<pii>lane)
{
	srand((unsigned int)time(NULL));
	int c_max = 0;
	Mat param_max;
	sort(lane.begin(), lane.end());

	for (int i = 0; i < n; i++) {
		int p1 = 0, p2, p3, p4 = lane.size() - 1, c = 0;
		p2 = rand() % lane.size();
		p3 = rand() % lane.size();

		Mat Y_out = Mat(Size(1, lane.size()), CV_64FC1);
		for(int i=0;i < lane.size();i++)
			Y_out.at<double>(i, 0) = (double)lane[i].second;

		Mat param = get_param3(p1, p2, p3, p4, lane);
		Mat residual = cal_function3(param, lane);
		residual -= Y_out;

		for (int i = 0; i < lane.size(); i++)
			if (residual.at<double>(i, 0) < t && residual.at<double>(i, 0) > -t) c++;

		if (c > c_max) {
			c_max = c;
			param_max = param;
		}
		c = 0;
	}
	cout << c_max<<endl;
	return param_max;
}

void find_route(Mat src, Mat left_param, Mat right_param, vector<pii>left_lane, vector<pii>right_lane)
{
	vector <pii> std_lane = min(left_lane.size(), right_lane.size()) == left_lane.size()? left_lane:right_lane;
	Mat left_y = cal_function3(left_param, left_lane);
	Mat right_y = cal_function3(right_param, right_lane);

	for (int idx = 0; idx < std_lane.size(); idx++) {
		int a = std_lane[idx].first;
		int b = (int)(left_y.at<double>(idx, 0) + right_y.at<double>(idx, 0)) / 2;
		for (int i = -5; i < 5; i++) {
			src.at<Vec3b>(a, b + i)[0] = 255;
			src.at<Vec3b>(a, b + i)[1] = 0;
			src.at<Vec3b>(a, b + i)[2] = 0;
		}
	}
	imshow("result", src);
}

void test_3ransac(Mat src, Mat param, vector<pii> lane)
{
	int idx = 0;
	Mat y = cal_function3(param, lane);

	for (int idx = 0; idx < lane.size(); idx++) {
		for (int i = -5; i < 5; i++) {
			src.at<Vec3b>(lane[idx].first, (int)y.at<double>(idx, 0) + i)[0] = 0;
			src.at<Vec3b>(lane[idx].first, (int)y.at<double>(idx, 0) + i)[1] = 0;
			src.at<Vec3b>(lane[idx].first, (int)y.at<double>(idx, 0) + i)[2] = 255;
		}
	}
	
	//imshow("3ransac_res", src);
}

int main()
{
	Mat srcImg = imread("road13.jpg"); 
	Mat src_clone = srcImg.clone();

	if (srcImg.empty()) {
		cerr << "invalid file";
		return -1;
	}

	Mat hsvImg;
	cvtColor(srcImg, hsvImg, COLOR_BGR2HSV);

	Mat roi_hsv = roi(hsvImg);
	Mat	white_line = mask(roi_hsv);
	clustering(white_line);

	//3차 란삭.
	Mat left_param = ransac3(500, 0.3, white1);
	Mat right_param = ransac3(500, 0.3, white2);
	test_3ransac(src_clone, left_param, white1);
	test_3ransac(src_clone, right_param, white2);

	find_route(src_clone, left_param, right_param, white1, white2);
	
	waitKey();
	return 0;
}
