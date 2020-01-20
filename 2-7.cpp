//Matx 클래스 -> 행렬연산.
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	Matx23f A(1, 2, 3,
		4, 5, 6);  //Matx<float, 2, 3> A(1,2,3,4,5,6);
	//print("A", A);

	cout << "A = " << (Mat)A << endl;
	Matx13f A0 = A.row(0);  //A의 0번째 row를 가져옴. 단 그 형태에 맞는 자료형으로 선언할 것.
	cout << "A0 = " << (Mat)A0 << endl;  //이런 크기가 지정되어 typedef된 Mat들은 출력시 형변환 할 것.

	Matx21f A1 = A.col(0);
	cout << "A1 = " << (Mat)A1 << endl;

	Matx22f A2 = A.get_minor<2, 2>(0, 1);   //행렬의 (0,1)을 기준으로 2*2 부분행렬을 떼어줌.
	cout << "A2 = " << (Mat)A2 << endl;

	Matx23f B = Matx23f::all(10.0f);  //2*3짜리 행렬을 모두 10.0f로 초기화 하여 만듬.

	Matx23f C, D, E, F;
	C = A + B;
	D = A - B;
	E = A * 5;
	F = A.mul(B);

	cout << "C= " << (Mat)C << endl;
	float dotAB = A.dot(B); //행렬곱

	Matx22f G = A * B.t();   //B.t()는 B의 전치행렬이다.

	return 0;
}