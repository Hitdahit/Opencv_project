/*
	opencv C
	Smooth() -> CV_BLUR_NO_SCALE,
				CV_BLUR,
				CV_GAUSSIAN,
				CV_MEDIAN,
				CV_BILATERAL���� �پ��� ������� ������ �ε巴�� ����� ���͸��� ������.

	opencv C++
	boxFilter(), bilateralFilter(), medianBlur(), blur(), GaussianBlur()�� �Լ����� ������ ����.
	noise�� ����.

	void boxFilter(InputArray src, OutputArray dst, int ddepth, Size ksize,
			Point anchor = Point(-1, -1), bool normalize = true,
			int borderType = BORDER_DEFAULT
	)
	�Է¿���� ���� ũ��,�ڷ����� ������, ddepth�� ���̸� ������ ��¿����� ����(ddepth==-1�̸� src�� ���� ����.)
	anchor�� (-1, -1)�̸� Ŀ���߽��� anchor���� �ǹ���. 
	normalizer�� true�� Ŀ��ũ��� ���ԷֵǾ� ������Ϳ� ������.
	borderType�� ���� ���� ȭ�Ҹ� ����ϴ� ����� ����.

	void bilateralFilter(InputArray src, OutputArray dst, int d, double sigmaColor,
		double sigmaSpace, int borderType = BORDER_DEFAULT
	)
	����þ� �Լ��� ����Ͽ� ������ �� ��ȭ��Ű�鼭 ����� ���͸��� ��. 
	src�� 

*/