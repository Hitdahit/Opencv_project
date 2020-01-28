/*
	void calcBackProject(const Mat*images, int nimages, const int* channels, const SparseMat& hist,
		OuputArray backProject, const float** reanges, double scale = 1, bool uniform = true);

	히스토그램 hist의 역튜영을 backProject에 계산. 얼굴인식에서 피부색상을 이용하는 경우,
	샘플영상을 피부영역의 히스토그램을 계산한 후에 역 투영하면 손, 얼굴 등의 영역을 분할할 수 있다. 
	즉, ROI를 지정하고 그 컬러정보(hue)를 히스토그램으로 계산한 후에, 추적시 계산한 히스토그램을 역투영한 후 threshold를 먹이면
	추적을 위한 영상과 컬러정보가 비슷한 영역만을 검출할 수 있다. 
	
	* findContours 함수를 사용하여 물체의 경계를 검출. 
	meanShift, Camshift와 같은 물체 추적방법에서 히스토그램 역투영을 사용함.
*/
//1채널 히스토그램 역투영.
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

	int histSize[] = { 8 };  //histSize[]={4};   히스토그램 빈 개수
	float valueRange[] = { 0, 8 };
	const float* ranges[] = { valueRange };
	int channels[] = { 0 };   //0번 채널, 
	int dims = 1;      //1차원

	Mat hist;
	calcHist(&A, 1, channels, Mat(), hist, dims, histSize, ranges, true);
	cout << "hist = " << hist << endl;

	Mat backProject;

	calcBackProject(&A, 1, channels, hist, backProject, ranges);
	cout << "backProject = " << backProject << endl;
	return 0;
}
*/
//2채널
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
//Hue-채널
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

	Rect roi(10, 10, 150, 150);   //좌상귀 기억.
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