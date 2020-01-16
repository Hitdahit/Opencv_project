//cvtColor함수, at으로 픽셀 접근하기.

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat img_color;

	//프로젝트 디렉토리에 있는 이미지 파일을 원색 그대로 불러옴.
	img_color = imread("image.jpg", IMREAD_COLOR);

	//만약 이미지 파일이 비어있다면
	if (img_color.empty()) {
		cout << "Could not open or find the image\n";
		return -1;
	}

	Mat img_gray;
	//불러온 이미지 파일을 gray scale로 바꿔줌
	//참고 BGR은 RGB색상 채널을 의미함. -> Byte역순.
	cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

	//바꿔준 이미지 파일을 프로젝트 디렉토리에 저장.
	imwrite("image_gray.jpg", img_gray);

	//윈도우 생성. resize할 수 없다. 동시에 생략해도 상관x
	//namedWindow("BGR", WINDOW_AUTOSIZE);
	//namedWindow("Grayscale", WINDOW_AUTOSIZE);

	imshow("BGR", img_color);
	imshow("Grayscale", img_gray);

	while (waitKey(0) != 27);  //esc 눌러야 꺼짐

	/*
	컬러 이미지는 B, G, R의 채널을 가지며, 각 채널들은
	0~255사이의 값을 가진다.
	그레이 이미지는 이를 이용하여, 컬러 이미지의 3개 채널의 
	평균값을 구해서 3개의 채널을 모두 그 평균으로 채워준다.
	*/

	//cvtColor를 사용하지 않고 gray scale로 만들기
	/*
	1. 3개의 채널을 가진 Mat 객체와 1개의 채널을 가진 Mat객체를
	각각 생성한다.

	2. 컬러 이미지의 각 픽셀에서 B, G, R 채널값을 가져옴

	3. 평균을 구해서 저장해줌. 1채널짜리로 해도 되고, 3채널 
	짜리로 해도 됨
	*/
	/*
	
	Mat img_gray_1channel, img_gray_3channel;

	
	//Mat.create(,,)  원하는 이미지 파일의 행, 열을 이용하여
	//자신이 원하는 채널 수를 지정해서 새로운 Mat 생성.
	
	//CV_8UC3->3채널짜리로 Mat 생성.
	img_gray_3channel.create(img_color.rows, img_color.cols, CV_8UC3);
	img_gray_1channel.create(img_color.rows, img_color.cols, CV_8UC1);

	for (int i = 0; i < img_color.rows; i++) {
		for (int j = 0; j < img_color.cols; j++) {
			//이미지 픽셀 값에 접근할 때
			//이미지파일변수명.at<Vec3b>(i, j)[0~2](b, g, r순서).
			uchar b = img_color.at<Vec3b>(i, j)[0];  //unsigned char
			uchar g = img_color.at<Vec3b>(i, j)[1];
			uchar r = img_color.at<Vec3b>(i, j)[2];

			uchar gray = (b + g + r) / 3.0;

			//1채널짜리는 하나만 저장하면 되니까 그냥 uchar로 접근
			img_gray_1channel.at<uchar>(i, j) = gray;

			img_gray_3channel.at<Vec3b>(i, j)[0] = gray;
			img_gray_3channel.at<Vec3b>(i, j)[1] = gray;
			img_gray_3channel.at<Vec3b>(i, j)[2] = gray;
		}
	}
	*/

	return 0;
}
