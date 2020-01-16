//영상 캡쳐, 저장, 불러오기
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	/*
	//영상을 캡처하기 위한 코드.
	Mat img_color;

	//비디오 캡쳐 객체 초기화.
	VideoCapture cap(0);
	if (!cap.isOpened()) { //웹캠을 사용할 수 있는지 확인하는 메소드
		cerr << "error: camera disabled\n";
		return -1;
	}

	//카메라 사용이 가능하면
	while (1) {
		//웹캠으로부터 캡쳐한 프레임 1개를 Mat변수에 저장.
		cap.read(img_color);
		if (img_color.empty()) {
			cerr << "empty video.\n";
			return -1;
		}
		//이미지 정보를 윈도우로 만들어 보여줌.
		imshow("color", img_color);



		while (waitKey(0) != 27);
		return 0;
	}
	*/

	/*
	//영상을 저장하기 위한 코드.
	//아래와 따로 동작시킬것.
	Mat img_color;

	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cerr << "cannot open camera\n";
		return -1;
	}

	//동영상 파일을 저장하기 위해 Size형 변수에 동영상 크기 설정해줌.
	Size size = Size((int)cap.get(CAP_PROP_FRAME_WIDTH),
		(int)cap.get(CAP_PROP_FRAME_HEIGHT));

	//비디오 라이터로 파일 저장.
	VideoWriter writer;
	double fps = 30.0;
	//writer.open()메소드로 저장할 영상 형식을 지정.
	writer.open("output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'),
		fps, size, true);
	
	if (!writer.isOpened()) {
		cerr << "VideoWriter got error\n";
		return -1;
	}

	while (1) {
		cap.read(img_color);
		if (img_color.empty()) {
			cerr << "invalid video\n";
			break;
		}
		//라이터로 정했던 동영상 파일 형식에 맞춰서 프레임 저장.
		writer.write(img_color);
		imshow("Color", img_color);

		if (waitKey(0) == 27)	break;

	}*/
	
	//영상을 읽어오기 위한 코드
	Mat read_img;

	VideoCapture cap2("output.avi");
	if (!cap2.isOpened()) {
		cerr << "invalid file\n";
		return -1;
	}

	while (1) {
		cap2.read(read_img);  //만약 두번째 코드 더미를 살리고 여기의 cap2를
		//cap으로 바꾼다면 계속 다른 영상을 띄울 수 있다.
		if (read_img.empty()) {
			cerr << "invalid file\n";
			return -1;
		}

		imshow("color", read_img);
		//x를 첫번째로 누르면 위의 저장에서 벗어나고,
		//그이후부터는 저장된 프레임들을 읽어오는 이곳에서 윈도우들을 띄우는 것
		//즉, 영상을 
		if (waitKey(0) == 27) break;
	}


	return 0;
	
}
