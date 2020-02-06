//�������_����, ���� �� ����
/*
	1. ����, ����, �� ����
		����: ������ ��ü�� ��ü ���� �Ǵ� ��ü�� �������� ��迡�� �߻�.
			�������͸��� 1�� �̺��� �׷����Ʈ ũ�⸦ ����ؼ������� �����ϴ� sobel�Լ���
			2���̺� ���͸� �Լ��� laplacian �Ǵ� laplacian of gaussian���� ���͸��� ��
			0-�������� ã�Ƽ� ������ �����Ѵ� (ex. canny)
			
			void Canny(InputArray image. OutputArray edges, 
				double threshold1, double threshold2, 
				int apertureSize=3, bool L2gradient=false
			);
			->1ä�� 8��Ʈ �Է¿��� image���� ������ �����Ͽ� edges�� ������. 
			apetureSize: �׷����Ʈ�� ����ϱ� ���� Sobel�Ƿ��� ũ��� ���
			threshold 1, 2: �����׸��ý� �Ӱ谪�� ���. (1<2)
			L2gradient == true ((dI/dx)^2 + (dI/dy)^2)^1/2 �� �׷����Ʈ ���
						  false |dI/dx| + |dI/dy|�� �׷����Ʈ ���.

				Canny �˰���:
					1. ����þ� ���͸��� �Ͽ� ������ �ε巴�� �Ѵ�.  (�����δ� ���� �������� �������)
					2. Sobel �����ڸ� �̿��Ͽ� �׷����Ʈ ������ ũ��(magnitude)�� ����Ѵ�.  (cvSobel(src, dx, 1, 0, apetureSize))
					3. �����ٶ� ������ ��� ���� 3*3 â�� �̿��Ͽ� �׷����Ʈ ���� ���⿡�� �׷����Ʈ ũ�Ⱑ 
					�ִ��� ȭ�Ҹ� �����, �������� 0���� ����(non-maximum suppression)
					4. ����� ������ ��� ���� �ΰ��� threshold1, 2�� ���. ���� ���� �Ӱ� ���� ����Ͽ�,
					�׷����Ʈ ���⿡�� ���� ���� �Ӱ谪�� ���ö����� �����ϸ� ������ �����ϴ� �����׸��ý� �Ӱ谪 ����� ���.

				Hough ��ȯ:
					Sobel, Canny ����� ���� ������ �ܼ��� ȭ�ҵ��� ������ ��, ����� ����, �簢��, ��, ����� ������ ������ ���� �ʴ´�.
					���� ��ȯ�� ����ǥ�� ����ؼ� �̹��������� �������� ǥ���ϰ� �����Ѵ�.  (p, a)
					1. ���� ����: p = xcos(a) + ysin(a)
						�� ���� ��(x, y)�� ���Ͽ� �̻���� ���ݿ��� ��(x, y)�� �������� ������ ��� ������ �Ķ����(p, a)�� ����Ͽ�
						�����ϴ� �����迭 A(k, h)�� 1�� ���� ��Ų��.
						�̸� ��� �������� ���Ͽ� �����ϸ� A(k, h)���� (p_k, a_h)�� �������� �ִ� ���� ������ ������.
						�̶� A(k, h) > threshold�� ��� (k, h)�߿��� �����ذ�(local maxima)�� ������ ã�´�.
						(A(k, h)�� �� ��ġ�� �ϳ��� ������ �������� ǥ����.)
						i. (p, a)������ ���������� ���ڹ迭 A(k, h)�� �̻�ȭ
						ii. A(k, h)�� ��� 0���� �ʱ�ȭ
						iii. ��� 0�� �ƴ� ���� ȭ�� E(x, y)�� ���Ͽ�,
								for h=0~H-1
									p=xcos(a_h)+ysin(a_h)
									p�� ���� ����� p_k�� k�� ã��.
									A(k, h) = A(k, h) + 1
						iv. A(k, h) > threshold�� ��� (k, h) �߿� �����ذ�(local maxima)�� �������� ã��,
						�迭 A(k, h)�� �� ��ġ�� �ϳ��� ������ �������� ǥ����.
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
//HoughLines �Լ��� ���� ����
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

	for (int k = 0; k < lines.size(); k++) {  //����� ������ ����
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
//HoughLinesP �Լ��� ���� ����
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
//HoughCircles�� �� ����
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