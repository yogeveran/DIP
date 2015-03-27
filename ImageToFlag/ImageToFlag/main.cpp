// ImageToFlag.cpp : Defines the entry point for the console application.
//

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <math.h>
#include <iostream>
#define MY_PI 3.14159265358979323846
#define MAT_SIZE 4
using namespace cv;
using namespace std;
Mat leftUp, leftDown, rightUp, rightDown;
Mat dst, dst_inter, srcWithMirror;

bool in_Range(double value, int from, int to) {
	return (from <= floor(value)) && (ceil(value) < to);
}
float uFunc(float d) {
	if (d < 1 && d >= 0) {
		return abs((1.5 * pow(d, 3) - 2.5 * pow(d, 2) + 1));
	} else if (d < 2 && d >= 1) {
		return abs((-1.5 * pow(d, 3) + 2.5 * pow(d, 2) - 4 * d + 2));
	} else {
		return 0;
	}
}
Vec3f uFunc(Vec3f d) {
	Vec3f ans = Vec3f(uFunc(d(0)), uFunc(d(1)), uFunc(d(2)));
	return ans;
}

void calcRightUp(Mat src) {
	float** rightUpXFloat = new float*[MAT_SIZE];
	for (int i = 0; i < MAT_SIZE; ++i)
		rightUpXFloat[i] = new float[MAT_SIZE];
	float** rightUpYFloat = new float*[MAT_SIZE];
	for (int i = 0; i < MAT_SIZE; ++i)
		rightUpYFloat[i] = new float[MAT_SIZE];

	rightUpXFloat[0][0] = 5 / 4;
	rightUpXFloat[0][1] = 1 / 4;
	rightUpXFloat[0][2] = 3 / 4;
	rightUpXFloat[0][3] = 7 / 4;
	rightUpXFloat[1][0] = 5 / 4;
	rightUpXFloat[1][1] = 1 / 4;
	rightUpXFloat[1][2] = 3 / 4;
	rightUpXFloat[1][3] = 7 / 4;
	rightUpXFloat[2][0] = 5 / 4;
	rightUpXFloat[2][1] = 1 / 4;
	rightUpXFloat[2][2] = 3 / 4;
	rightUpXFloat[2][3] = 7 / 4;
	rightUpXFloat[3][0] = 5 / 4;
	rightUpXFloat[3][1] = 1 / 4;
	rightUpXFloat[3][2] = 3 / 4;
	rightUpXFloat[3][3] = 7 / 4;

	rightUpYFloat[0][0] = 7 / 4;
	rightUpYFloat[0][1] = 7 / 4;
	rightUpYFloat[0][2] = 7 / 4;
	rightUpYFloat[0][3] = 7 / 4;
	rightUpYFloat[1][0] = 3 / 4;
	rightUpYFloat[1][1] = 3 / 4;
	rightUpYFloat[1][2] = 3 / 4;
	rightUpYFloat[1][3] = 3 / 4;
	rightUpYFloat[2][0] = 1 / 4;
	rightUpYFloat[2][1] = 1 / 4;
	rightUpYFloat[2][2] = 1 / 4;
	rightUpYFloat[2][3] = 1 / 4;
	rightUpYFloat[3][0] = 5 / 4;
	rightUpYFloat[3][1] = 5 / 4;
	rightUpYFloat[3][2] = 5 / 4;
	rightUpYFloat[3][3] = 5 / 4;

	float sumForNormal = 0;
	for (int i = 0; i < MAT_SIZE; i++) {
		for (int j = 0; j < MAT_SIZE; j++) {
			//float absD = sqrt(pow(rightUpXLong[i][j],2) + pow(rightUpYLong[i][j],2));
			//cout << absD << endl;
			//float uFuncAns = uFunc(absD);
			float uFuncAns = uFunc(rightUpXFloat[i][j])
					* uFunc(rightUpYFloat[i][j]);
			sumForNormal += uFuncAns;
			rightUp.at<Vec3f>(i, j)(0) = uFuncAns;
			rightUp.at<Vec3f>(i, j)(1) = uFuncAns;
			rightUp.at<Vec3f>(i, j)(2) = uFuncAns;
		}
	}
	for (int i = 0; i < MAT_SIZE; i++) {
		for (int j = 0; j < MAT_SIZE; j++) {
			rightUp.at<Vec3f>(i, j)(0) = rightUp.at<Vec3f>(i, j)(0)
					/ sumForNormal;
			rightUp.at<Vec3f>(i, j)(1) = rightUp.at<Vec3f>(i, j)(1)
					/ sumForNormal;
			rightUp.at<Vec3f>(i, j)(2) = rightUp.at<Vec3f>(i, j)(2)
					/ sumForNormal;
		}
	}

	delete rightUpXFloat;
	delete rightUpYFloat;
}
void calcRightDown(Mat src) {
	float** rightDownXFloat = new float*[MAT_SIZE];
	for (int i = 0; i < MAT_SIZE; ++i)
		rightDownXFloat[i] = new float[MAT_SIZE];
	float** rightDownYFloat = new float*[MAT_SIZE];
	for (int i = 0; i < MAT_SIZE; ++i)
		rightDownYFloat[i] = new float[MAT_SIZE];
	rightDownXFloat[0][0] = 5 / 4;
	rightDownXFloat[0][1] = 1 / 4;
	rightDownXFloat[0][2] = 3 / 4;
	rightDownXFloat[0][3] = 7 / 4;
	rightDownXFloat[1][0] = 5 / 4;
	rightDownXFloat[1][1] = 1 / 4;
	rightDownXFloat[1][2] = 3 / 4;
	rightDownXFloat[1][3] = 7 / 4;
	rightDownXFloat[2][0] = 5 / 4;
	rightDownXFloat[2][1] = 1 / 4;
	rightDownXFloat[2][2] = 3 / 4;
	rightDownXFloat[2][3] = 7 / 4;
	rightDownXFloat[3][0] = 5 / 4;
	rightDownXFloat[3][1] = 1 / 4;
	rightDownXFloat[3][2] = 3 / 4;
	rightDownXFloat[3][3] = 7 / 4;

	rightDownYFloat[0][0] = 5 / 4;
	rightDownYFloat[0][1] = 5 / 4;
	rightDownYFloat[0][2] = 5 / 4;
	rightDownYFloat[0][3] = 5 / 4;
	rightDownYFloat[1][0] = 1 / 4;
	rightDownYFloat[1][1] = 1 / 4;
	rightDownYFloat[1][2] = 1 / 4;
	rightDownYFloat[1][3] = 1 / 4;
	rightDownYFloat[2][0] = 3 / 4;
	rightDownYFloat[2][1] = 3 / 4;
	rightDownYFloat[2][2] = 3 / 4;
	rightDownYFloat[2][3] = 3 / 4;
	rightDownYFloat[3][0] = 7 / 4;
	rightDownYFloat[3][1] = 7 / 4;
	rightDownYFloat[3][2] = 7 / 4;
	rightDownYFloat[3][3] = 7 / 4;

	float sumForNormal = 0;
	for (int i = 0; i < MAT_SIZE; i++) {
		for (int j = 0; j < MAT_SIZE; j++) {
			float uFuncAns = uFunc(rightDownXFloat[i][j]) * uFunc(rightDownYFloat[i][j]);
			sumForNormal += uFuncAns;
			rightDown.at<Vec3f>(i, j)(0) = uFuncAns;
			rightDown.at<Vec3f>(i, j)(1) = uFuncAns;
			rightDown.at<Vec3f>(i, j)(2) = uFuncAns;
		}
	}
	for (int i = 0; i < MAT_SIZE; i++) {
		for (int j = 0; j < MAT_SIZE; j++) {
			rightDown.at<Vec3f>(i, j)(0) = rightDown.at<Vec3f>(i, j)(0)
					/ sumForNormal;
			rightDown.at<Vec3f>(i, j)(1) = rightDown.at<Vec3f>(i, j)(1)
					/ sumForNormal;
			rightDown.at<Vec3f>(i, j)(2) = rightDown.at<Vec3f>(i, j)(2)
					/ sumForNormal;
		}
	}
}
void calcMatrices(Mat src) {
	rightUp = Mat::zeros(MAT_SIZE, MAT_SIZE, src.type());
	rightDown = Mat::zeros(MAT_SIZE, MAT_SIZE, src.type());
	calcRightUp(src);
	calcRightDown(src);
}
int main(int argc, char** argv) {
	int wave_frequency = 3; //Default wave frequency
	double amplitude = 0.03; //Defined after load of picture to be 3%
	if (argc != 4) {
		cout
				<< "Usage: ImageToFlag <image> <wave_frequency> <interpolation_type: n,b,c>"
				<< endl;
		waitKey(0);                        // Wait for a keystroke in the window
		return -1;
	}
	wave_frequency = atoi(argv[2]);
	char* interpolation = argv[3];
	Mat src = imread(argv[1], IMREAD_COLOR);   // Read the file
	amplitude = amplitude * src.rows;   //% of picture height.

	if ((!src.data) || src.empty())                   // Check for invalid input
			{
		cout << "Could not open or find the image" << std::endl;
		waitKey(0);                        // Wait for a keystroke in the window
		return -2;
	}

	/// Set the dst image the same type as src but in size + amplitude for height.
	Size size(src.cols, (int) ceil(src.rows + 2 * amplitude));
	//Create destination Matrix
	Size sizeMirror(src.cols + 2, src.rows + 2);
	srcWithMirror = Mat::zeros(sizeMirror, src.type());
	dst = Mat::zeros(size, src.type());
	dst_inter = Mat::zeros(size, src.type());
	//Set Background to white.
	dst.setTo(Scalar(255, 255, 255));
	dst_inter.setTo(Scalar(255, 255, 255));
	cv::copyMakeBorder(src, srcWithMirror, 2, 2, 2, 2, cv::BORDER_REFLECT,0);
	calcMatrices(src);
	//Distort done here using forward scanning with no interpolation.
	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			int new_y = (int) (y
					+ amplitude
							* (1 + sin(wave_frequency * MY_PI * x / src.cols)));
			dst.at<Vec3b>(new_y, x) = src.at<Vec3b>(y, x);
		}
	}
	cout << "done sin func\n";

	//Distort done here using backward scanning with interpolation.

	for (int dst_y = 0; dst_y < dst_inter.rows; dst_y++) {
		for (int x = 0; x < dst_inter.cols; x++) {
			double y = dst_y - amplitude
							* (1 + sin(wave_frequency * MY_PI * x / src.cols));
			int src_y;
			double src_y1, src_y2;
			switch (interpolation[0]) {
			case 'n':
				src_y = (int) round(y);
				if (in_Range(src_y, 0, src.rows))
					dst_inter.at<Vec3f>(dst_y, x) = src.at<Vec3f>(src_y, x);
				break;
			case 'b': //Bi-Linear
				src_y1 = floor(y);
				src_y2 = ceil(y);
				if (in_Range(src_y1, 0, src.rows)) {
					if (in_Range(src_y2, 0, src.rows)) {         //Both in range
						for (int i = 0; i < 3; i++) {
							dst_inter.at<Vec3b>(dst_y, x)(i) = src.at<Vec3b>(
									(int) src_y1, x)(i) * (src_y2 - y)
									+ src.at<Vec3b>((int) src_y2, x)(i)
											* (y - src_y1);
						}
					} else {
						// 1 in range
						dst_inter.at<Vec3f>(dst_y, x) = src.at<Vec3f>(
								(int) src_y1, x);
					}
				} else if (in_Range(src_y2, 0, src.rows)) {
					// 2 in range
					dst_inter.at<Vec3f>(dst_y, x) = src.at<Vec3f>((int) src_y2,x);
				}                              //else None in range
				break;
			case 'c': {
				//Cubic
				float distFromSrcY = abs(y - src_y);
				int mirrX = x + 2;
				int mirrY = ((int)round(y)) + 2;
				Mat toUse;
				Point p1;
				if (in_Range(round(y), 0, src.rows)) {
					if (distFromSrcY > 0.5) { //Use topRight
						toUse = rightDown;
						p1 = Point(mirrX - 2, mirrY - 2);
					} else {  //user bottomRight
						toUse = rightUp;
						p1 = Point(mirrX - 1, mirrY - 1);
					}
					Rect rect(p1, Size(4, 4));
					Mat cropped = srcWithMirror(rect);
					Vec3f newVec = Vec3f(0, 0, 0);
					for (int cubic_i = 0; cubic_i < MAT_SIZE; cubic_i++) {
						for (int cubic_j = 0; cubic_j < MAT_SIZE; cubic_j++) {
							for(int cubic_k = 0; cubic_k < 3; cubic_k++){
								newVec(cubic_k) += cropped.at<Vec3f>(cubic_i, cubic_j)(cubic_k)
												 * toUse.at<Vec3f>(cubic_i, cubic_j)(cubic_k);
							}
						}
					}
					dst_inter.at<Vec3f>(dst_y, x) = newVec;
				}
				break;
			}
			default:
				src_y = ((int) round(y));
				if (in_Range(src_y, 0, src.rows))
					dst_inter.at<Vec3b>(dst_y, x) = src.at<Vec3b>(src_y, x);
				break;

			}

		}
	}
	cout << "\ndone backward \n";

	namedWindow("Before", WINDOW_AUTOSIZE);  // Create a window for display.
	namedWindow("No Interpolation", WINDOW_AUTOSIZE); // Create a window for display.
	namedWindow("With Interpolation", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Before", src);                   // Show Before Image
	imshow("No Interpolation", dst);               // Show After  Image
	imshow("With Interpolation", dst_inter);   // Create a window for display.

	waitKey(0);                            // Wait for a keystroke in the window
	/*src.release();
	dst_inter.release();
	dst.release();
	rightDown.release();
	rightUp.release();*/
	return 0;
}

