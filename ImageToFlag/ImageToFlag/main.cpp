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
int newRound(double num) {
	if (abs((num - (int) num)) > 0.5)
		return (int) num + 1;
	else
		return (int) num;
}
double uFunc(double d) {
	if (0 <= d && d < 1)
		return (3 / 2) * (pow(d, 3)) - (5 / 2) * (pow(d, 2)) + 1;
	if (1 <= d && d < 2)
		return -(3 / 2) * (pow(d, 3)) + (5 / 2) * (pow(d, 2)) - 4 * d + 2;
	return 0;
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

	double sumForNormal = 0;
	for (int i = 0; i < MAT_SIZE; i++) {
		for (int j = 0; j < MAT_SIZE; j++) {
			//double uFuncAns = uFunc(rightUpXdouble[i][j]) * uFunc(rightUpYdouble[i][j]);
			double uFuncAns = sqrt(pow(rightUpXdouble[i][j],2) + pow(rightUpYdouble[i][j],2));
			sumForNormal += uFuncAns;
			rightUp.at<Vec3b>(i, j) = Vec3b(uFuncAns,uFuncAns,uFuncAns);
		}
	}
	/*
	for (int i = 0; i < MAT_SIZE; i++) {
			for (int j = 0; j < MAT_SIZE; j++) {
				for (int k = 0; k < 3; k++)
					rightUp.at<Vec3b>(i, j)(k) = rightUp.at<Vec3b>(i, j)(k)
							/ sumForNormal;
			}
		}*/
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

	double sumForNormal = 0;
	for (int i = 0; i < MAT_SIZE; i++) {
		for (int j = 0; j < MAT_SIZE; j++) {
			//double uFuncAns = uFunc(rightDownXdouble[i][j]) * uFunc(rightDownYdouble[i][j]);
			double uFuncAns = sqrt(pow(rightDownXdouble[i][j],2) + pow(rightDownYdouble[i][j],2));
			sumForNormal += uFuncAns;
			rightDown.at<Vec3b>(i, j) = Vec3b(uFuncAns,uFuncAns,uFuncAns);
		}
	}/*
	for (int i = 0; i < MAT_SIZE; i++) {
		for (int j = 0; j < MAT_SIZE; j++) {
			for (int k = 0; k < 3; k++)
				rightDown.at<Vec3b>(i, j)(k) = rightDown.at<Vec3b>(i, j)(k)
						/ sumForNormal;
		}
	}*/
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
	cv::copyMakeBorder(src, srcWithMirror, 2, 2, 2, 2, cv::BORDER_REFLECT, 0);
	calcMatrices(src);
	//Distort done here using forward scanning with no interpolation.
	for (int x = 0; x < src.cols; x++) {
		for (int y = 0; y < src.rows; y++) {
			int new_y = (int) (y
					+ amplitude
							* (1 + sin(wave_frequency * MY_PI * x / src.cols)));
			dst.at<Vec3b>(new_y, x) = src.at<Vec3b>(y, x);
		}
	}
	cout << "done sin func\n";

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
				src_y = (int) round(y);
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
									(int) src_y1, x)(i) * (src_y2 - y)
									+ src.at<Vec3b>((int) src_y2, x)(i)
											* (y - src_y1);
						}
					} else {
						// 1 in range
						dst_inter.at<Vec3b>(dst_y, x) = src.at<Vec3b>(
								(int) src_y1, x);
					}
				} else if (in_Range(src_y2, 0, src.rows)) {
					// 2 in range
					dst_inter.at<Vec3b>(dst_y, x) = src.at<Vec3b>((int) src_y2,x);
				}                              //else None in range
				break;
			case 'c': {
				//Cubic
				if (in_Range(y, 0, src.rows)) {
					double distFromSrcY = abs(y - (int) y);
					int mirrX = x + 2;
					int mirrY = ((int) newRound(y)) + 2;
					Mat toUse;
					Point p1;
					if (distFromSrcY > 0.5) { //Use bottomRight
						toUse = rightDown;
						p1 = Point(mirrX - 2, mirrY - 2);
					} else {  //Use topRight
						toUse = rightUp;
						p1 = Point(mirrX - 1, mirrY - 1);
					}
					Rect rect(p1, Size(4, 4));
					Mat cropped = srcWithMirror(rect);
					Vec3b newVec = Vec3b(0,0,0);
					for (int cubic_i = 0; cubic_i < MAT_SIZE; cubic_i++) {
						for (int cubic_j = 0; cubic_j < MAT_SIZE; cubic_j++) {
							for (int cubic_k = 0; cubic_k < 3; cubic_k++) {
								newVec(cubic_k) += cropped.at<Vec3b>(cubic_i,cubic_j)(cubic_k)
										* toUse.at<Vec3b>(cubic_i, cubic_j)(cubic_k);
							}
						}
					}
					dst_inter.at<Vec3b>(dst_y, x) = newVec;
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
	imshow("Before", src);  // Show Before Image
	imshow("No Interpolation", dst);  // Show After  Image
	imshow("With Interpolation", dst_inter);  // Create a window for display.

	waitKey(0);  // Wait for a keystroke in the window
	/*src.release();
	 dst_inter.release();
	 dst.release();
	 rightDown.release();
	 rightUp.release();*/
	return 0;
}

