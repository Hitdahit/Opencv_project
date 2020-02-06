/*
	sharping filtering은 영상에서 edge혹은 세밀한 부분을 강조시킬 수 있는 기법이다.
	
	1. 상관관계
		일반적으로, 2차원 입력영상 src(x, y)에서 (2*size+1)*(2*size+1)크기의 필터 윈도우(커널) w(s, t)의 상관관계는
		대응되는 위치끼리의 곱을 모두 합하여 출력영상 dst(x, y)에 저장한다.
		그러나 opencv에서는 위와 같은 상태에서 상관관계를 계산할때 anchor를 사용한다(기준점.
		)
	2. 회선(convolution)
		상관관계와 같은 셋업에서, 윈도우를 180도 회전시켜 대응되는 위치의 값을 곱셈하여 합을 출력영상 dst에 저장한다.
		만약 윈도우(커널/필터)이 대칭형이라면, 상관과 회선은 서로 같은 역할을 한다. 
		회선은 결합법칙이 성립한다. 이로 인해, 필터(윈도우)는 분리가 가능하다고 말할 수 있다.
	3. 2D 필터링함수
		void filter2D(InputArray src, OutputArray dst, int ddepth, InputArray kernel, 
						Point anchor=Point(-1, -1), double delta = 0, int borderType=BORDER_DEFAULT);
		입력 src에 윈도우(커널)를 이용하여 회선(convolution)을 계산 후 dst에 저장하는 함수. ddepth는 dst의 깊이로, 이것이 -1이면
		dst.depth == src.depth()이다.
		kernel은 1채널 float형 행렬로, 모든 채널에 동일하게 적용됨
		anchor는 커널의 중심점이다(kernel 내부의 위치.)
		
		filter2D 함수는 상관관계로 동작하지만, 대부분의 윈도우 커널은 대칭이므로, convolution한다고 할 수 있다.
		
		void sepFilter2D(InputArray src, OutputArray dst, int ddepth, 
				InputArray kernelX, InputArray kernelY, Point anchorc = cPoint(-1, -1), 
				double deltac = c0, int borderTypec = cBORDER_DEFAULT
		)
		분리 가능한 선형필터를 적용함. 입력src의 각 행에 커널(윈도우) kernelX를 적용 후 그 결과의 각 열에 커널(윈도우) kernelY를 적용하여
		회선을 계산한 후 delta를 덧셈하여 dst에 저장함. ddepth는 dst의 깊이.
*/
//filter2D를 사용gks 3*3 평균 필터링
/*
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	uchar dataA[] = {
		1,2,4,5,2,1,
		3,6,6,9,0,3,
		1,8,3,7,2,5,
		2,9,8,9,9,1,
		3,9,8,8,7,2,
		4,9,9,9,9,3
	};

	Mat A(6, 6, CV_8U, dataA);
	cout << "A = " << A << endl;

	Mat avgKernel = (Mat_<float>(3, 3) << 1./9., 1./9., 1./9.,
										  1./9., 1./9., 1./9.,
										  1./9., 1./9., 1./9.
	);   //사용할 필터 미리 선언

	Point anchor(-1, -1);  //same as anchor(1,1)
	
	Mat B;
	filter2D(A, B, -1, avgKernel, anchor);
	cout << "B = " << B << endl;

	anchor = Point(1, 1);
	Mat C;
	filter2D(A, C, -1, avgKernel, anchor);
	cout << "C = " << C << endl;

	//conv
	Point newAnchor = Point(avgKernel.cols - anchor.x - 1, avgKernel.rows - anchor.y - 1);
	Mat D;
	Mat flipKernel;
	flip(avgKernel, flipKernel, -1);  //사용하던 필터를 180도 회전해야 conv.
	filter2D(A, D, -1, flipKernel, anchor);
	cout << "D = " << D << endl;


}
*/
//sepFilter2D를 사용한 3*3 평균필터링
/*
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	uchar dataA[] = {
		1,2,4,5,2,1,
		3,6,6,9,0,3,
		1,8,3,7,2,5,
		2,9,8,9,9,1,
		3,9,8,8,7,2,
		4,9,9,9,9,3
	};

	Mat A(6, 6, CV_8U, dataA);
	cout << "A = " << A << endl;

	Mat avgX = (Mat_<float>(1, 3) << 1./3., 1./3., 1./3.);
	Mat avgY = (Mat_<float>(3, 1) << 1. / 3., 1. / 3., 1. / 3.);

	Mat B, C;
	filter2D(A, B, -1, avgX);
	cout << "B = " << B << endl;

	filter2D(A, C, -1, avgY);
	cout << "C = " << C << endl;

	Mat D;
	sepFilter2D(A, D, -1, avgX, avgY);
	cout << "D = " << D << endl;

	waitKey();
	return 0;
}
*/
//영상에서 filter2D, sepFilter2D를 사용한 평균 필터링
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImg = imread("lena.jpg");
	if (srcImg.empty())return -1;

	Size ksize(7, 7);  //ksize(21, 21)
	Mat avgKernel = Mat::ones(ksize, CV_32F);
	avgKernel /= avgKernel.total();

	Mat avgImg;
	filter2D(srcImg, avgImg, -1, avgKernel);
	imshow("avgImg", avgImg);

	Mat avgX = Mat::ones(1, ksize.width, CV_32F);
	Mat avgY = Mat::ones(ksize.height, 1, CV_32F);
	avgX /= avgX.total();
	avgY /= avgY.total();

	Mat avgImg2;
	sepFilter2D(srcImg, avgImg2, -1, avgX, avgY);
	imshow("avgImg2", avgImg2);

	waitKey();
	return 0;
}