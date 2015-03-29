// ImageToFlag.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "core.hpp"
#include "highgui.hpp"
#include "imgproc.hpp"
#include "opencv.hpp"
#include <math.h>
#include <iostream>
#define MY_PI 3.14159265358979323846
#define MAT_SIZE 4
#define padding 20
using namespace cv;
using namespace std;
Mat_<Vec3b> dst, dst_inter, srcWithMirror;
double leftUp[MAT_SIZE][MAT_SIZE], leftDown[MAT_SIZE][MAT_SIZE], rightUp[MAT_SIZE][MAT_SIZE], rightDown[MAT_SIZE][MAT_SIZE];

double cubicInterpolate(double p[4], double x) {
	return p[1] + 0.5 * x*(p[2] - p[0] + x*(2.0*p[0] - 5.0*p[1] + 4.0*p[2] - p[3] + x*(3.0*(p[1] - p[2]) + p[3] - p[0])));
}

double bicubicInterpolate(double p[4][4], double x, double y) {
	double arr[4];
	arr[0] = cubicInterpolate(p[0], y);
	arr[1] = cubicInterpolate(p[1], y);
	arr[2] = cubicInterpolate(p[2], y);
	arr[3] = cubicInterpolate(p[3], y);
	return cubicInterpolate(arr, x);
}
void calcRightUp(Mat src) {
	double** rightUpXdouble = new double*[MAT_SIZE];
	for (int i = 0; i < MAT_SIZE; ++i)
		rightUpXdouble[i] = new double[MAT_SIZE];
	double** rightUpYdouble = new double*[MAT_SIZE];
	for (int i = 0; i < MAT_SIZE; ++i)
		rightUpYdouble[i] = new double[MAT_SIZE];

	rightUpXdouble[0][0] = 5 / 4;
	rightUpXdouble[0][1] = 1 / 4;
	rightUpXdouble[0][2] = 3 / 4;
	rightUpXdouble[0][3] = 7 / 4;
	rightUpXdouble[1][0] = 5 / 4;
	rightUpXdouble[1][1] = 1 / 4;
	rightUpXdouble[1][2] = 3 / 4;
	rightUpXdouble[1][3] = 7 / 4;
	rightUpXdouble[2][0] = 5 / 4;
	rightUpXdouble[2][1] = 1 / 4;
	rightUpXdouble[2][2] = 3 / 4;
	rightUpXdouble[2][3] = 7 / 4;
	rightUpXdouble[3][0] = 5 / 4;
	rightUpXdouble[3][1] = 1 / 4;
	rightUpXdouble[3][2] = 3 / 4;
	rightUpXdouble[3][3] = 7 / 4;

	rightUpYdouble[0][0] = 7 / 4;
	rightUpYdouble[0][1] = 7 / 4;
	rightUpYdouble[0][2] = 7 / 4;
	rightUpYdouble[0][3] = 7 / 4;
	rightUpYdouble[1][0] = 3 / 4;
	rightUpYdouble[1][1] = 3 / 4;
	rightUpYdouble[1][2] = 3 / 4;
	rightUpYdouble[1][3] = 3 / 4;
	rightUpYdouble[2][0] = 1 / 4;
	rightUpYdouble[2][1] = 1 / 4;
	rightUpYdouble[2][2] = 1 / 4;
	rightUpYdouble[2][3] = 1 / 4;
	rightUpYdouble[3][0] = 5 / 4;
	rightUpYdouble[3][1] = 5 / 4;
	rightUpYdouble[3][2] = 5 / 4;
	rightUpYdouble[3][3] = 5 / 4;

	double sum = 0;
	for (int i = 0; i < MAT_SIZE; i++) {
		for (int j = 0; j < MAT_SIZE; j++) {
			//double uFuncAns = uFunc(rightUpXdouble[i][j]) * uFunc(rightUpYdouble[i][j]);
			double uFuncAns = sqrt(pow(rightUpXdouble[i][j], 2) + pow(rightUpYdouble[i][j], 2));
			rightUp[i][j] = uFuncAns;
			sum += uFuncAns;
		}
	}
	if (sum != 0)
		for (int i = 0; i < MAT_SIZE; i++)
			for (int j = 0; j < MAT_SIZE; j++)
				rightUp[i][j] /= sum;
}
void calcRightDown(Mat src) {
	double** rightDownXdouble = new double*[MAT_SIZE];
	for (int i = 0; i < MAT_SIZE; ++i)
		rightDownXdouble[i] = new double[MAT_SIZE];
	double** rightDownYdouble = new double*[MAT_SIZE];
	for (int i = 0; i < MAT_SIZE; ++i)
		rightDownYdouble[i] = new double[MAT_SIZE];
	rightDownXdouble[0][0] = 5 / 4;
	rightDownXdouble[0][1] = 1 / 4;
	rightDownXdouble[0][2] = 3 / 4;
	rightDownXdouble[0][3] = 7 / 4;
	rightDownXdouble[1][0] = 5 / 4;
	rightDownXdouble[1][1] = 1 / 4;
	rightDownXdouble[1][2] = 3 / 4;
	rightDownXdouble[1][3] = 7 / 4;
	rightDownXdouble[2][0] = 5 / 4;
	rightDownXdouble[2][1] = 1 / 4;
	rightDownXdouble[2][2] = 3 / 4;
	rightDownXdouble[2][3] = 7 / 4;
	rightDownXdouble[3][0] = 5 / 4;
	rightDownXdouble[3][1] = 1 / 4;
	rightDownXdouble[3][2] = 3 / 4;
	rightDownXdouble[3][3] = 7 / 4;

	rightDownYdouble[0][0] = 5 / 4;
	rightDownYdouble[0][1] = 5 / 4;
	rightDownYdouble[0][2] = 5 / 4;
	rightDownYdouble[0][3] = 5 / 4;
	rightDownYdouble[1][0] = 1 / 4;
	rightDownYdouble[1][1] = 1 / 4;
	rightDownYdouble[1][2] = 1 / 4;
	rightDownYdouble[1][3] = 1 / 4;
	rightDownYdouble[2][0] = 3 / 4;
	rightDownYdouble[2][1] = 3 / 4;
	rightDownYdouble[2][2] = 3 / 4;
	rightDownYdouble[2][3] = 3 / 4;
	rightDownYdouble[3][0] = 7 / 4;
	rightDownYdouble[3][1] = 7 / 4;
	rightDownYdouble[3][2] = 7 / 4;
	rightDownYdouble[3][3] = 7 / 4;

	double sum = 0;
	for (int i = 0; i < MAT_SIZE; i++) {
		for (int j = 0; j < MAT_SIZE; j++) {
			//double uFuncAns = uFunc(rightDownXdouble[i][j]) * uFunc(rightDownYdouble[i][j]);
			double uFuncAns = sqrt(pow(rightDownXdouble[i][j], 2) + pow(rightDownYdouble[i][j], 2));
			rightDown[i][j] = uFuncAns;
			sum += uFuncAns;
		}
	}
	if (sum != 0)
		for (int i = 0; i < MAT_SIZE; i++)
			for (int j = 0; j < MAT_SIZE; j++)
				rightUp[i][j] /= sum;
}
void calcMatrices(Mat src) {

	calcRightUp(src);
	calcRightDown(src);
}

bool in_Range(double value, int from, int to) {
	return (from <= floor(value)) && (ceil(value) < to);
}
int newRound(double num) {
	if (abs((num - (int)num)) > 0.5)
		return (int)num + 1;
	else
		return (int)num;
}
double uFunc(double d) {
	if (0 <= d && d < 1)
		return (3 / 2) * (pow(d, 3)) - (5 / 2) * (pow(d, 2)) + 1;
	if (1 <= d && d < 2)
		return -(3 / 2) * (pow(d, 3)) + (5 / 2) * (pow(d, 2)) - 4 * d + 2;
	return 0;
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
	Mat src = imread(argv[1], IMREAD_ANYCOLOR | IMREAD_ANYDEPTH);   // Read the file
	

	if ((!src.data) || src.empty())                   // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		waitKey(0);                        // Wait for a keystroke in the window
		return -2;
	}
	amplitude = amplitude * src.rows;   //% of picture height.

	
	namedWindow("Before", WINDOW_AUTOSIZE);  // Create a window for display.
	imshow("Before", src);  // Show Before Image
	waitKey();
	/// Set the dst image the same type as src but in size + amplitude for height.
 	Size size(src.cols, (int)ceil(src.rows + 2 * amplitude));
	//Create destination Matrix
	Size sizeMirror(src.cols + 2, src.rows + 2);
	srcWithMirror = Mat::zeros(sizeMirror, src.type());
	dst = Mat::zeros(size, src.type());
 	dst_inter = Mat::zeros(size, src.type());
	//Set Background to white.
	dst.setTo(Scalar(255, 255, 255));
	dst_inter.setTo(Scalar(255, 255, 255));
	cv::copyMakeBorder(src, srcWithMirror, padding, padding, padding, padding, BORDER_REPLICATE, 0);
	calcMatrices(src);
	//Distort done here using forward scanning with no interpolation.
	for (int x = 0; x < src.cols; x++) {
		for (int y = 0; y < src.rows; y++) {
			int new_y = (int)(y
				+ amplitude
				* (1 + sin(wave_frequency * MY_PI * x / src.cols)));
			dst.at<Vec3b>(new_y, x) = src.at<Vec3b>(y, x);
		}
	}
	namedWindow("No Interpolation", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("No Interpolation", dst);  // Show After  Image
	waitKey();

	//Distort done here using backward scanning with interpolation.
	for (int x = 0; x < dst_inter.cols; x++) {
		for (int dst_y = 0; dst_y < dst_inter.rows; dst_y++) {
			double y = dst_y
				- amplitude
				* (1 + sin(wave_frequency * MY_PI * x / src.cols));
			int src_y;
			double src_y1, src_y2;
			switch (interpolation[0]) {
			case 'n':
				src_y = (int)round(y);
				if (in_Range(src_y, 0, src.rows))
					dst_inter.at<Vec3b>(dst_y, x) = src.at<Vec3b>(src_y, x);
				break;
			case 'b': //Bi-Linear
				src_y1 = floor(y);
				src_y2 = ceil(y);
				if (in_Range(src_y1, 0, src.rows)) {
					if (in_Range(src_y2, 0, src.rows)) {         //Both in range
						for (int i = 0; i < 3; i++) {
							dst_inter.at<Vec3b>(dst_y, x)(i) = src.at<Vec3b>(
								(int)src_y1, x)(i)* (src_y2 - y)
								+ src.at<Vec3b>((int)src_y2, x)(i)
								* (y - src_y1);
						}
					}
					else {
						// 1 in range
						dst_inter.at<Vec3b>(dst_y, x) = src.at<Vec3b>(
							(int)src_y1, x);
					}
				}
				else if (in_Range(src_y2, 0, src.rows)) {
					// 2 in range
					dst_inter.at<Vec3b>(dst_y, x) = src.at<Vec3b>((int)src_y2, x);
				}                              //else None in range
				break;
			case 'c': {
				if (in_Range(y, 0, src.rows)) {
					double distFromSrcY = abs(y - (int)y);
					int mirrX = x + 2;
					int mirrY = ((int)newRound(y)) + 2;
					Point p1;
					if (distFromSrcY > 0.5) { //Use bottomRight
						p1 = Point(mirrX - 2, mirrY - 2);

						Rect rect(p1, Size(4, 4));
						Mat cropped = srcWithMirror(rect);

						Rect roi(mirrX - 2, mirrY - 2, 4, 4);
						cv::Mat croppedRef(srcWithMirror, roi);
						croppedRef.copyTo(cropped);

						for (int i = 0; i < 3; i++) {
							dst_inter.at<Vec3b>(dst_y, x)(i) = cropped.at<Vec3b>(0, 0)(i)*rightDown[0][0] + cropped.at<Vec3b>(0, 1)(i)*rightDown[0][1] + cropped.at<Vec3b>(0, 2)(i)*rightDown[0][2] + cropped.at<Vec3b>(0, 3)(i)*rightDown[0][3]
								+ cropped.at<Vec3b>(1, 0)(i)*rightDown[1][0] + cropped.at<Vec3b>(1, 1)(i)*rightDown[1][1] + cropped.at<Vec3b>(1, 2)(i)*rightDown[1][2] + cropped.at<Vec3b>(1, 3)(i)*rightDown[1][3]
								+ cropped.at<Vec3b>(2, 0)(i)*rightDown[2][0] + cropped.at<Vec3b>(2, 1)(i)*rightDown[2][1] + cropped.at<Vec3b>(2, 2)(i)*rightDown[2][2] + cropped.at<Vec3b>(2, 3)(i)*rightDown[2][3]
								+ cropped.at<Vec3b>(3, 0)(i)*rightDown[3][0] + cropped.at<Vec3b>(3, 1)(i)*rightDown[3][1] + cropped.at<Vec3b>(3, 2)(i)*rightDown[3][2] + cropped.at<Vec3b>(3, 3)(i)*rightDown[3][3];
						}
					}
					else {  //Use topRight
						p1 = Point(mirrX - 1, mirrY - 1);

						Rect rect(p1, Size(4, 4));
						Mat cropped = srcWithMirror(rect);

						Rect roi(mirrX - 1, mirrY - 1, 4, 4);
						cv::Mat croppedRef(srcWithMirror, roi);
						croppedRef.copyTo(cropped);

						for (int i = 0; i < 3; i++) {
							dst_inter.at<Vec3b>(dst_y, x)(i) = cropped.at<Vec3b>(0, 0)(i)*rightUp[0][0] + cropped.at<Vec3b>(0, 1)(i)*rightUp[0][1] + cropped.at<Vec3b>(0, 2)(i)*rightUp[0][2] + cropped.at<Vec3b>(0, 3)(i)*rightUp[0][3]
								+ cropped.at<Vec3b>(1, 0)(i)*rightUp[1][0] + cropped.at<Vec3b>(1, 1)(i)*rightUp[1][1] + cropped.at<Vec3b>(1, 2)(i)*rightUp[1][2] + cropped.at<Vec3b>(1, 3)(i)*rightUp[1][3]
								+ cropped.at<Vec3b>(2, 0)(i)*rightUp[2][0] + cropped.at<Vec3b>(2, 1)(i)*rightUp[2][1] + cropped.at<Vec3b>(2, 2)(i)*rightUp[2][2] + cropped.at<Vec3b>(2, 3)(i)*rightUp[2][3]
								+ cropped.at<Vec3b>(3, 0)(i)*rightUp[3][0] + cropped.at<Vec3b>(3, 1)(i)*rightUp[3][1] + cropped.at<Vec3b>(3, 2)(i)*rightUp[3][2] + cropped.at<Vec3b>(3, 3)(i)*rightUp[3][3];
						}
					}

				}
				break;
			}
			default:
				src_y = ((int)round(y));
				if (in_Range(src_y, 0, src.rows))
					dst_inter.at<Vec3b>(dst_y, x) = src.at<Vec3b>(src_y, x);
				break;

			}

		}
	}
 	cout << "\ndone backward \n";

	

	namedWindow("With Interpolation", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("With Interpolation", dst_inter);  // Create a window for display.

	waitKey(0);  // Wait for a keystroke in the window
	/*src.release();
	dst_inter.release();
	dst.release();
	rightDown.release();
	rightUp.release();*/
 	return 0;
}

