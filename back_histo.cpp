/*
	void calcBackProject(const Mat*images, int nimages, const int* channels, const SparseMat& hist,
		OuputArray backProject, const float** reanges, double scale = 1, bool uniform = true);

	������׷� hist�� ��Ʃ���� backProject�� ���. ���νĿ��� �Ǻλ����� �̿��ϴ� ���,
	���ÿ����� �Ǻο����� ������׷��� ����� �Ŀ� �� �����ϸ� ��, �� ���� ������ ������ �� �ִ�. 
	��, ROI�� �����ϰ� �� �÷�����(hue)�� ������׷����� ����� �Ŀ�, ������ ����� ������׷��� �������� �� threshold�� ���̸�
	������ ���� ����� �÷������� ����� �������� ������ �� �ִ�. 
	
	* findContours �Լ��� ����Ͽ� ��ü�� ��踦 ����. 
	meanShift, Camshift�� ���� ��ü ����������� ������׷� �������� �����.
*/
//1ä�� ������׷� ������.
/*
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	uchar dataA[16] = {
		0, 0, 0, 0,
		1, 1, 3, 5,
		6, 1, 1, 3,
		4, 3, 1, 7
	};

	Mat A(4, 4, CV_8U, dataA);
	cout << "A = " << A << endl;

	int histSize[] = { 8 };  //histSize[]={4};   ������׷� �� ����
	float valueRange[] = { 0, 8 };
	const float* ranges[] = { valueRange };
	int channels[] = { 0 };   //0�� ä��, 
	int dims = 1;      //1����

	Mat hist;
	calcHist(&A, 1, channels, Mat(), hist, dims, histSize, ranges, true);
	cout << "hist = " << hist << endl;

	Mat backProject;

	calcBackProject(&A, 1, channels, hist, backProject, ranges);
	cout << "backProject = " << backProject << endl;
	return 0;
}
*/
//2ä��
/*
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	uchar dataA[16] = {
		0, 0, 0, 0,
		1, 1, 1, 1,
		1, 1, 1, 2,
		1, 2, 1, 3
	};

	Mat A(4, 2, CV_8UC2, dataA);
	cout << "A = " << A << endl;

	int histSize[] = { 4, 4 };
	float range1[] = { 0, 4 };
	float range2[] = { 0, 4 };
	const float* ranges[] = { range1, range2 };
	int channels[] = { 0, 1 };
	int dims = 2;

	Mat hist;
	calcHist(&A, 1, channels, Mat(), hist, dims, histSize, ranges, true);
	cout << "hist = " << hist << endl;

	Mat backProject;
	calcBackProject(&A, 1, channels, hist, backProject, ranges);
	cout << "backProject = " << endl;

	return 0;

}
*/
//Hue-ä��
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImg = imread("lena.jpg");
	if (srcImg.empty()) {
		return -1;
	}

	Mat hsvImg;
	cvtColor(srcImg, hsvImg, COLOR_BGR2HSV);
	vector <Mat> planes;
	split(hsvImg, planes);
	Mat hueImg = planes[0];

	Rect roi(10, 10, 150, 150);   //�»�� ���.
	rectangle(srcImg, roi, Scalar(0, 0, 255), 2);
	Mat roiImg = hueImg(roi);

	int histSize = 256;
	float hValue[] = { 0, 256 };
	const float* ranges[] = { hValue };
	int channels = 0;
	int dims = 1;
	
	Mat hist;
	calcHist(&roiImg, 1, &channels, Mat(), hist, dims, &histSize, ranges);

	Mat hueImg2;
	hueImg2.convertTo(hueImg2, CV_32F);

	Mat backProject;
	calcBackProject(&hueImg2, 1, &channels, hist, backProject, ranges);

	double minVal, maxVal;

	minMaxLoc(backProject, &minVal, &maxVal);

	cout << "minVal = " << minVal << endl;
	cout << "maxVal = " << maxVal << endl;

	Mat backProject2;
	normalize(backProject, backProject2, 0, 255, NORM_MINMAX, CV_8U);

	cout << "fuck you" << endl;

	//imshow("backProject2", backProject2);
	imshow("srcImg", srcImg);

	waitKey();
	return 0;


}