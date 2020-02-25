//tried to capture lanes' points with HoughLinesP, since hsv sometimes cannot capture lane with inRange function.
//it captured points not so bad but failed to implement curve ransac

#include <opencv2/opencv.hpp>
#include <ctime>
#include <cmath>
using namespace std;
using namespace cv;
vector <Vec4i> lines;
vector<Point> curve;
vector<Point> left_line;
vector<Point> right_line;
Mat roi(Mat src)
{
	Mat mask;
	Scalar color;
	int width = src.cols;
	int height = src.rows;

	Point vertices[1][4];
	vertices[0][0] = Point(0, height);
	vertices[0][1] = Point(0, height*2/5+10);
	vertices[0][2] = Point(width, height*2/5+10);
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
Mat hough_lines(Mat src, int threshold=10)
{
	src = roi(src);
	Mat grayImg;
	cvtColor(src, grayImg, COLOR_BGR2GRAY);
	 
	Mat gaussImg;
	GaussianBlur(grayImg, gaussImg, Size(9, 9), 0.7);
	

	Mat cannyImg;
	Canny(gaussImg, cannyImg, 130, 400);
	imshow("realcannyImg", cannyImg);


	
	//threshold: r,세타 평면에서 몇개의 곡선이 한점에서 만날 때 직선으로 판단할지에 대한 최소값
	HoughLinesP(cannyImg, lines, 1, CV_PI/180, threshold, 0.01, 40);
	
	
	Mat dst = src.clone();  //오 이거 찾고 있었는데 개꿀팁
	for (size_t i = 0; i < lines.size(); i++) {
		Vec4i l = lines[i];
		if (l[0] == l[2])continue;
		double slope = (l[1] - l[3]) / double(l[0] - l[2]);

		if (slope < 0.3 && slope>-0.4)continue;
		else {
			curve.push_back(Point(l[0], l[1]));
			curve.push_back(Point(l[2], l[3]));
			line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1);
		}
	}

	imshow("hough", dst);

	return dst;
}

void cluster(int mid)
{
	for (int i = 0; i < curve.size(); i++) {
		if (curve[i].x < mid) left_line.push_back(curve[i]);
		else right_line.push_back(curve[i]);
	}
}

int* find_param(vector<Point> x, int p1, int p2, int p3)
{
	float param[] = {     //long long.....
			x[p1].y * x[p1].y, x[p1].y, 1,
			x[p2].y * x[p2].y, x[p2].y, 1,
			x[p3].y * x[p3].y, x[p3].y, 1
	};
	float ans[] = {
		x[p1].x,
		x[p2].x,
		x[p3].x
	};
	Mat param_mat = Mat(Size(3, 3), CV_32FC1, param);
	Mat ans_mat = Mat(Size(1, 3), CV_32FC1, ans);
	
	Mat new_param = param_mat.inv();
	Mat answer = param_mat * ans_mat;

	int a[3] = { answer.at<float>(0, 0), answer.at<float>(1, 0), answer.at<float>(2, 0) };
	
	return a;
}

int* convex_ransac(vector<Point> x, int n, int t)
{
	srand((unsigned int)time(NULL));
	int c_max = 0;
	int* param_max = NULL;

	for (int i = 0; i < n; i++) {
		int p1 = rand() % x.size(), p2 = rand() % x.size(), p3 = rand() % x.size();
		int* param = find_param(x, p1, p2, p3);
		//rm
		//cout << param[0] << " " << param[1] << " " << param[2] << endl;
		int c = 0;
		for (int j = 0; j < x.size(); j++) {
			//cout << abs(param[0] * x[j].y * x[j].y + param[1] * x[j].y + param[2] - x[j].x) << endl;
			if (abs(param[0] * x[j].y * x[j].y - param[1] * x[j].y - param[2] - x[j].x) < t) {
				c++;
			}
			//cout << c_max << endl;
			if (c_max < c) {
				c_max = c;
				param_max = param;
			}
		}
	}

	return param_max;

}

void test_ransac(Mat src, int* param, int t)
{
	cout << "Tlqkf";
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			if (param[0] * i * i  + param[1]*i + param[3] <= j + t && param[0] * i * i + param[1] * i + param[3] >= j - t) {
				//cout << "Tlqkf";
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
	//경계선(contour)들을 찾는 과정.
	Mat srcImg = imread("road13.jpg");
	Mat res = srcImg.clone();

	Mat hough = hough_lines(res);

	cluster(srcImg.cols / 2);

	int *left_fun = convex_ransac(left_line, 20, 1000);
	int *right_fun = convex_ransac(right_line, 20, 1000);

	test_ransac(res, left_fun, 1000);

	//res = mask_roi(res, houghImg);
	imshow("res", res);

	waitKey();
	return 0;
}


/*
Mat mask_roi(Mat src, Mat mask)   //분리해낸 영상->mask  즉, 원본이미지에 분리할 영상을 시각화하는 함수
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
/*
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
		(직선의 파라미터를 사용하는 parameter space는 직선의 기울기가 무한대인 경우 표현할 수없기에 만듬.)/
*/
