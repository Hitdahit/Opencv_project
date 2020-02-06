//영상분할_에지, 직선 원 검출
/*
	1. 에지, 직선, 원 검출
		에지: 영상의 물체와 물체 사이 또는 물체와 배경사이의 경계에서 발생.
			공간필터링시 1차 미분의 그래디언트 크기를 사용해서에지를 검출하는 sobel함수와
			2차미분 필터링 함수인 laplacian 또는 laplacian of gaussian으로 필터링한 후
			0-교차점을 찾아서 에지를 검출한다 (ex. canny)
			
			void Canny(InputArray image. OutputArray edges, 
				double threshold1, double threshold2, 
				int apertureSize=3, bool L2gradient=false
			);
			->1채널 8비트 입력영상 image에서 에지를 검출하여 edges에 저장함. 
			apetureSize: 그래디언트를 계산하기 위한 Sobel피러의 크기로 사용
			threshold 1, 2: 히스테리시스 임계값에 사용. (1<2)
			L2gradient == true ((dI/dx)^2 + (dI/dy)^2)^1/2 로 그래디언트 계산
						  false |dI/dx| + |dI/dy|로 그래디언트 계산.

				Canny 알고리즘:
					1. 가우시안 필터링을 하여 영상을 부드럽게 한다.  (실제로는 직접 스무딩을 해줘야함)
					2. Sobel 연산자를 이용하여 그래디언트 벡터의 크기(magnitude)를 계산한다.  (cvSobel(src, dx, 1, 0, apetureSize))
					3. 가느다란 에지를 얻기 위해 3*3 창을 이용하여 그래디언트 벡터 방향에서 그래디언트 크기가 
					최대인 화소만 남기고, 나머지는 0으로 억제(non-maximum suppression)
					4. 연결된 에지를 얻기 위해 두개의 threshold1, 2를 사용. 높은 값의 임계 값을 사용하여,
					그래디언트 방향에서 낮은 값의 임계값이 나올때까지 추적하며 에지를 연결하는 히스테리시스 임계값 방식을 사용.

				Hough 변환:
					Sobel, Canny 검출로 얻은 에지는 단순한 화소들의 집합일 뿐, 연결된 직선, 사각형, 원, 곡선등의 구조적 정보를 갖지 않는다.
					허프 변환은 극좌표를 사용해서 이미지공간의 에지들을 표현하고 검출한다.  (p, a)
					1. 직선 검출: p = xcos(a) + ysin(a)
						각 에지 점(x, y)에 대하여 이산격자 간격에서 점(x, y)를 지나가는 가능한 모든 직선의 파라미터(p, a)를 계산하여
						대응하는 정수배열 A(k, h)를 1씩 증가 시킨다.
						이를 모든 에지점에 대하여 시행하면 A(k, h)에는 (p_k, a_h)인 직선위에 있는 에지 갯수가 누적됨.
						이때 A(k, h) > threshold인 모든 (k, h)중에서 지역극값(local maxima)인 직선을 찾는다.
						(A(k, h)의 각 위치는 하나의 직선의 방정식을 표현함.)
						i. (p, a)공간을 일정간격의 격자배열 A(k, h)로 이산화
						ii. A(k, h)를 모두 0으로 초기화
						iii. 모든 0이 아닌 에지 화소 E(x, y)에 대하여,
								for h=0~H-1
									p=xcos(a_h)+ysin(a_h)
									p와 가장 가까운 p_k의 k를 찾기.
									A(k, h) = A(k, h) + 1
						iv. A(k, h) > threshold인 모든 (k, h) 중에 지역극값(local maxima)인 직선만을 찾고,
						배열 A(k, h)의 각 위치는 하나의 직선의 방정식을 표현함.
*/
//Canny edge
/*
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat srcImg = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImg.empty()) return -1;

	Mat edges;
	Canny(srcImg, edges, 50, 100);
	imshow("edges", edges);

	waitKey();
	return 0;
}
*/
//HoughLines 함수로 직선 검출
/*
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImg = imread("line.jpg", IMREAD_GRAYSCALE);
	if (srcImg.empty())return -1;

	Mat edges;
	Canny(srcImg, edges, 50, 100);
	imshow("edges", edges);

	vector<Vec2f> lines;
	HoughLines(edges, lines, 1, CV_PI / 180.0, 100);

	Mat dstImg(srcImg.size(), CV_8UC3);
	cvtColor(srcImg, dstImg, COLOR_GRAY2BGR);
	cout << "lines.size() = " << lines.size() << endl;

	Vec2f params;
	float rho, theta;
	float c, s;
	float x0, y0;

	for (int k = 0; k < lines.size(); k++) {  //검출된 직선의 갯수
		params = lines[k];

		rho = params[0];
		theta = params[1];

		printf("lines[%2d] = (rho, theta)=(%f, %f)\n", k, rho, theta);

		c = cos(theta);
		s = sin(theta);

		x0 = rho * c;
		y0 = rho * s;

		Point p1, p2;
		p1.x = cvRound(x0 + 1000 * (-s));
		p1.y = cvRound(y0 + 1000 * (c));

		p2.x = cvRound(x0 - 1000 * (-s));
		p2.y = cvRound(y0 - 1000 * (c));

		line(dstImg, p1, p2, Scalar(0, 0, 255), 2);
	}

	imshow("dstImg", dstImg);
	waitKey();
	return 0;

}
*/
//HoughLinesP 함수로 선분 검출
/*
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImg = imread("line.jpg", IMREAD_GRAYSCALE);
	if (srcImg.empty()) return -1;

	Mat edges;
	Canny(srcImg, edges, 50, 100);
	imshow("edges", edges);

	vector<Vec4i> lines;
	HoughLinesP(edges, lines, 1, CV_PI/180.0, 10, 30, 10);

	Mat dstImg(srcImg.size(), CV_8UC3);
	cvtColor(srcImg, dstImg, COLOR_GRAY2BGR);

	Vec4i params;
	int x1, y1, x2, y2;

	for (int k = 0; k < lines.size(); k++) {
		params = lines[k];
		x1 = params[0];
		y1 = params[1];
		x2 = params[2];
		y2 = params[3];
		printf("lines[%2d] = P1(%4d, %4d)) = P2(%4d, %4d)\n", k, x1, y1, x2, y2);
	
		//draw a line segment
		Point p1(x1, y1), p2(x2, y2);
		line(dstImg, p1, p2, Scalar(0, 0, 255), 2);
	}

	imshow("dstImg", dstImg);

	waitKey();
	return 0;
}
*/
//HoughCircles로 원 검출
/*/
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImg = imread("circle.jpg", IMREAD_GRAYSCALE);
	if (srcImg.empty())return -1;

	//Mat circles;
	vector<Vec3f> circles;
	HoughCircles(srcImg, circles, HOUGH_GRADIENT, 1, 50);

	cout << "circles.size() = " << circles.size() << endl;

	Mat dstImg(srcImg.size(), CV_8UC3);
	cvtColor(srcImg, dstImg, COLOR_GRAY2BGR);

	Vec3f params;
	int cx, cy, r;
	for (int k = 0; k < circles.size(); k++) {
		//params = circles.at<Vec3f>(0, k);
		params = circles[k];
		cx = cvRound(params[0]);
		cy = cvRound(params[1]);
		r = cvRound(params[2]);
		printf("cirles[%2d]:(cx, cy) = (%d, %d), r = %d\n", k, cx, cy, r);

		Point center(cx, cy);
		circle(dstImg, center, r, Scalar(0, 0, 255), 2);

	}

	imshow("dstImg", dstImg);
	waitKey();
	return 0;
}
*/