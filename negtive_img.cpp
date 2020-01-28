//���� �����ϱ�
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImg = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (srcImg.empty()) {    //������...
		return -1;
	}
	
	Mat_<uchar> image(srcImg);           //1ä��¥���� ��ȯ
	Mat_<uchar> dstImg(srcImg.size());   //srcImg�� ��ȯ�� �޾��ֱ� ���� ����.

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			uchar r = image(i, j);
			dstImg(i, j) = 255 - r;     //���� �ȼ� ���� �ȼ� �ִ밪 255���� ���� �־��ָ� �̹��� �� ������ �ȴ�.
		}
	}
	
	imshow("dstImg", dstImg);

	waitKey();
	return 0;
}