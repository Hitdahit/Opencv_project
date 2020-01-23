#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImage = imread("lena.jpg", IMREAD_GRAYSCALE);  //lena.jpg를 그레이 스케일로 로드.
	if (srcImage.empty())return -1;

	Point pt1(10, 10), pt2(400, 400);  
	LineIterator it(srcImage, pt1, pt2, 8);   //pt1, 2를 연결하는 직선을 connectivity 8로 하여 직선알고리즘을 사용하는 반복자를 생성.

	vector<uchar> buffer(it.count);  //3채널이면 uchar가 아닌 Vec3b를 사용.
	for (int i = 0; i < it.count; i++, ++it) {
		buffer[i] = **it;   //영상의 화솟값 **it를  벡터인 buffer에 저장.

		//buffer[i] = srcImage.at<uchar>(it.pos());  //1채널.
		//buffer[i] = *(const Vec3b)*it;  //3채널일 경우는 이하 코드 사용.
		//buffer[i] = srcImage.at<Vec3b>(it.pos());  //3채널.
	}
	cout << (Mat)buffer << endl;  //buffer에 저장된 화솟값 출력.
	line(srcImage, pt1, pt2, Scalar(255), 2);   //pt1, 2를 연결하는 직선을 화면에 출력.(흰색임.)

	Mat dstImage(512, 512, CV_8UC3, Scalar(255, 255, 255));  //3채널 512*512 영상을 만들어 흰색으로 초기화 
	pt1 = Point(0, dstImage.cols - buffer[0]);

	for (int i = 1; i < buffer.size(); i++, ++it) {
		pt2 = Point(0, dstImage.cols - buffer[i]);  
		line(dstImage, pt1, pt2, Scalar(255), 2);   //line함수를 이용해서 dstImage 영상에 buffer에 저장된 화소값을 잉요해 프로파일을 그린다.

		pt1 = pt2;
	}

	imshow("srcImage", srcImage);
	imshow("dstImage", dstImage);

}