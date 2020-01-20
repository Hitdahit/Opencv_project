//Matx Ŭ���� -> ��Ŀ���.
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
	Matx13f A0 = A.row(0);  //A�� 0��° row�� ������. �� �� ���¿� �´� �ڷ������� ������ ��.
	cout << "A0 = " << (Mat)A0 << endl;  //�̷� ũ�Ⱑ �����Ǿ� typedef�� Mat���� ��½� ����ȯ �� ��.

	Matx21f A1 = A.col(0);
	cout << "A1 = " << (Mat)A1 << endl;

	Matx22f A2 = A.get_minor<2, 2>(0, 1);   //����� (0,1)�� �������� 2*2 �κ������ ������.
	cout << "A2 = " << (Mat)A2 << endl;

	Matx23f B = Matx23f::all(10.0f);  //2*3¥�� ����� ��� 10.0f�� �ʱ�ȭ �Ͽ� ����.

	Matx23f C, D, E, F;
	C = A + B;
	D = A - B;
	E = A * 5;
	F = A.mul(B);

	cout << "C= " << (Mat)C << endl;
	float dotAB = A.dot(B); //��İ�

	Matx22f G = A * B.t();   //B.t()�� B�� ��ġ����̴�.

	return 0;
}