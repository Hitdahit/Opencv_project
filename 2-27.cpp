//여러가지 방법으로 행렬요소에 접근하기
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat A(3, 3, CV_32F);
	int idx[2];
	for(int i=0;i<A.rows;i++)
		for (int j = 0; j < A.cols; j++) {
			A.at<float>(i, j) = i * A.cols + j;
			A.at<float>(Point(j, i)) = i * A.cols + j;

			idx[0] = i; idx[1] = j;
			A.at<float>(idx) = i * A.cols + j;
		}
	cout << "A = " << A << endl;

	int nSum = 0;
	for(int i=0;i<A.rows;i++)
		for (int j = 0; j < A.cols; j++) {
			nSum += A.at<float>(i, j);
			nSum += A.at<float>(Point(j, i));

			idx[0] = i; idx[1] = j;
			nSum += A.at<float>(idx);

		}
	cout << "nSum = " << nSum << endl;
	return 0;

}