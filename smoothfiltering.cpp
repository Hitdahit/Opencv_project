/*
	opencv C
	Smooth() -> CV_BLUR_NO_SCALE,
				CV_BLUR,
				CV_GAUSSIAN,
				CV_MEDIAN,
				CV_BILATERAL등의 다양한 방식으로 영상을 부드럽게 만드는 필터링을 제공함.

	opencv C++
	boxFilter(), bilateralFilter(), medianBlur(), blur(), GaussianBlur()의 함수들을 별도로 제공.
	noise를 제거.

	void boxFilter(InputArray src, OutputArray dst, int ddepth, Size ksize,
			Point anchor = Point(-1, -1), bool normalize = true,
			int borderType = BORDER_DEFAULT
	)
	입력영상과 같은 크기,자료형을 가지고, ddepth의 깊이를 가지는 출력영상을 만듬(ddepth==-1이면 src와 같은 깊이.)
	anchor가 (-1, -1)이면 커널중심이 anchor임을 의미함. 
	normalizer가 true면 커널크기로 정규롸되어 평균필터와 같아짐.
	borderType은 영상 밖의 화소를 취급하는 방법을 결정.

	void bilateralFilter(InputArray src, OutputArray dst, int d, double sigmaColor,
		double sigmaSpace, int borderType = BORDER_DEFAULT
	)
	가우시안 함수를 사용하여 에지를 덜 약화시키면서 양방향 필터링을 함. 
	src는 

*/