//픽셀 접근시 at, ptr, data로 접근하기.

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("image.jpg", IMREAD_COLOR);
	Mat gray_1channel;
	gray_1channel.create(img.rows, img.cols, CV_8UC1);
	//img.rowSSSSSSSSS!!, colSSSSSSSS!!

	//at으로 접근하기
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			uchar b = img.at<Vec3b>(i, j)[0];
			uchar g = img.at<Vec3b>(i, j)[1];
			uchar r = img.at<Vec3b>(i, j)[2];

			gray_1channel.at<uchar>(i, j) = (b + g + r) / 3.0;
		}
	}

	//ptr로 접근(at보다 빠름)
	for (int i = 0; i < img.rows; i++) {
		//i번째 row의 주소를 포인터로 저장시켜둠
		uchar* ptr_in = img.ptr<uchar>(i);
		uchar* ptr_out = gray_1channel.ptr<uchar>(i);
		for (int j = 0; j < img.cols; j++) {
			//픽셀이 메모리상에 b, g, r순서대로 저장되므로,
			//j마다 3칸씩 옮겨서 0, 1, 2로 접근한다.
			uchar b = ptr_in[j * 3 + 0];
			uchar g = ptr_in[j * 3 + 1];
			uchar r = ptr_in[j * 3 + 2];

			ptr_out[j] = (b + g + r) / 3.0;
		}
	}

	double t = (double)getTickCount();  //코드에서 이 줄이 실행되는 시점 저장.

	//data로 접근(ptr과 비슷.)
	for (int i = 0; i < img.rows; i++) {
		uchar* data_in = img.data;
		uchar* data_out = gray_1channel.data;
		for (int j = 0; j < img.cols; j++) {
			uchar b = data_in[i * img.cols * 3 + j * 3];
			uchar g = data_in[i * img.cols * 3 + j * 3 + 1];
			uchar r = data_in[i * img.cols * 3 + j * 3 + 2];

			data_out[img.cols * i + j] = (b + g + r) / 3.0;  
		}
	}

	//(위의 루프가 끝나는 시점 - 위의 루프가 시작하는 시점)/클락펄스 주기
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "time" << t << "sec\n";

	imshow("color", img);
	imshow("gray", gray_1channel);

	while (waitKey(0) != 27);
}
