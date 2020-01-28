/*
	영상처리에서 영상의 히스토그램은 영상화소의 분표에 대한 매우 중요한 정보.
	히스토그램의 계산, 히스토그램을 이용한 역두영, 히스토그램 비교 히스토그램 평활화 들을 다룬다.
*/
/*
	calcHist(~);
*/
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

	//히스토그램 설정용,
	int histSize[] = { 4 };
	float valueRange[] = { 0, 8 };
	const float* ranges[] = { valueRange };
	int channels[] = { 0 };
	int dims = 1;

	Mat hist;
	calcHist(&A, 1, channels, Mat(), hist, dims, histSize, ranges, true);   //매개변수와 같은 설정을 가진 등간격 히스토그램을 계산하여
	//hist 행렬에 저장.

	cout << "hist = " << hist << endl;

	Mat pdf;
	normalize(hist, pdf, 1, 0, NORM_L1);   //합계가 1이 되도록 정규화
	cout << "pdf =" << pdf << endl;

	return 0;
}