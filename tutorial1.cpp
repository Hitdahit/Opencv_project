#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat image;
	/*
	Mat이란 행렬 구조체이다.
	class CV_EXPORTS Mat	
	{
		public:
		// ... a lot of methods ...
		...

		! includes several bit-fields:
		 - the magic signature
		 - continuity flag
		 - depth
		 - number of channels
	 
		int flags;
		//! the array dimensionality, >= 2
		int dims;
		//! the number of rows and columns or (-1, -1) when the array has more than 2 dimensions
		int rows, cols;
		//! pointer to the data
		uchar* data;

		//! pointer to the reference counter;
		// when array points to user-allocated data, the pointer is NULL
		int* refcount;

		// other members
		...
	};

	*/
	//이미지를 읽되 컬러로 읽어와라 == IMREAD_COLOR
	image = imread("image.jpg", IMREAD_COLOR);  

	if (image.empty()) {   //행렬이 공백인지 확인하는 함수
		cout << "cannot open or find this image\n";
		return -1;
	}

	//void namedWindow(const string& winname, int flags = WINDOW_AUTOSIZE )
	/*
	winname변수에 저장된 문자열의 윈도우 캡션을 갖는 윈도우 생성.
	flags 변수가 WINDOW_AUTOSIZE라면 
	resizeWindow()로 크기조정을 할 수 없다.

	flags변수가 WINDOW_OPENGL이라면
	OpenGL을 지원하는 윈도우를 생성함.

	만약 winname이 동일한 윈도우가 이미 생성되어 있으면
	namedWindow함수는 아무일도 하지 않는다.

	만약 namedWindow함수를 호출하지 않고 바로 imshow함수로 영상을
	표시하면 flags=WINDOW_AUTOSIZE인 윈도우를 자동 생성한다.
	*/
	namedWindow("Original", WINDOW_AUTOSIZE);   

	//void imshow( const string& winname, InputArray mat )
	/*
	mat에 winname캡션을 갖는 윈도우에 표시
	*/
	imshow("Original", image);


	//그외의 함수들
	/*
	void destroyWindow(const string& winname)
	winname 캡션 이름을 갖는 윈도우 파괴

	void destroyAllWindows()
	모든 윈도우를 파괴

	void moveWindow(const string& winname , int x , int y )
	winname캡션 이름을 갖는 윈도우의 좌측-상단 위치 x,y위치로 이동

	void resizeWindow(const string& winname, int width, int height)
	winname 캡션이름을 갖는 윈도우를 width, height로 변경
	*/

	//키입력 대기시간을 지정하는 함수
	/*
	0이면 무한대기, ms단위임.
	리턴이 -1이면 입력 대기시간 동안 아무키도 눌리지 않은 것
	그 외의 리턴값은 키보드로 입력한 키값.
	'A'를 입력하면 97/65 둘 중 하나가 리턴된다.
	enter: 13(carriage return)
	esc: 27(excape)
	*/
	waitKey(0);
}
